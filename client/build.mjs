import esbuild from "esbuild";
import Fs from "node:fs/promises";
import Path from "node:path";
import { execSync } from "node:child_process";

async function generateBootstrapFile (output, content) {
	let previousContent = undefined;
	try {
		previousContent = await Fs.readFile(output, "utf8");
	} catch (e) {
		if (e.code !== "ENOENT") {
			throw e;
		}
	}
	const contentHasChanged = previousContent !== content;
	if (contentHasChanged) {
		await Fs.writeFile(output, content, "utf8");
	}
};

function extractClientComponentsPlugin(config) {
	return {
		name: "extract-client-components",
		setup(build) {
			if (config.output && typeof config.output !== "string") {
				console.error("output must be a string");
				return;
			}
			const output = config.output || "./bootstrap.js";

			build.onStart(async () => {
				if (!config.target) {
					console.error("target is required");
					return;
				}
				if (typeof config.target !== "string") {
					console.error("target must be a string");
					return;
				}

				const target = config.target;
				try {
					const bootstrapContent = execSync(
						`opam exec -- server_reason_react.extract_client_components ${target}`,
						{ encoding: "utf8" },
					);
					await generateBootstrapFile(output, bootstrapContent);
				} catch (e) {
					console.log("Extraction of client components failed:");
					console.error(e);
					return;
				}
			});

			build.onResolve({ filter: /.*/ }, (args) => {
				const isEntryPoint = args.kind === "entry-point";

				if (isEntryPoint) {
					return {
						path: args.path,
						namespace: "entrypoint",
					};
				}
				return null;
			});

			let webpackRequireMock = `
window.__webpack_require__ = window.__webpack_require__ || ((id) => {
  const component = window.__client_manifest_map[id];
  if (!component) {
    throw new Error(\`Could not find client component with id: \${id}\`);
  }
  return { __esModule: true, default: component };
});
window.__client_manifest_map = window.__client_manifest_map || {};`;

			build.initialOptions.banner = {
				js: webpackRequireMock,
			};

			build.onLoad({ filter: /.*/, namespace: "entrypoint" }, async (args) => {
				const filePath = args.path.replace(/^entrypoint:/, "");
				const entryPointContents = await Fs.readFile(filePath, "utf8");

				const contents = `
require("${output}");
${entryPointContents}`;

				return {
					loader: "jsx",
					contents,
					resolveDir: Path.dirname(Path.resolve(process.cwd(), filePath)),
				};
			});
		},
	};
}

async function build(input, output, extract) {
	let outdir = output;
	let splitting = true;

	let plugins = [];
	if (extract) {
		plugins.push(extractClientComponentsPlugin({ target: "app" }));
	}

	try {
		const result = await esbuild.build({
			entryPoints: [input],
			bundle: true,
			logLevel: "debug",
			platform: "browser",
			format: "esm",
			splitting,
			outdir,
			plugins,
			write: true,
		});

		console.log('Build completed successfully for "' + input + '"');
		return result;
	} catch (error) {
		console.error("\nBuild failed:", error);
		process.exit(1);
	}
}

const input = process.argv[2];
const output = process.argv[3];

let parseExtract = (arg) => {
	if (typeof arg == "string") {
		if (arg.startsWith("--extract=")) {
			return arg.split("--extract=")[1] === "true";
		}
	}

	return false;
};

const extract = parseExtract(process.argv[4]);

if (!input) {
	console.error("Please provide an input file path");
	process.exit(1);
}

build(input, output, extract);
