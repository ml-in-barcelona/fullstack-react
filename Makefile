.DEFAULT_GOAL := help

name = fullstack-reason-react-demo
current_hash = $(shell git rev-parse HEAD | cut -c1-7)

OPAM = opam
DUNE = opam exec -- dune
WEBPACK = npx webpack --progress

.PHONY: init
setup-githooks: ## Setup githooks
	git config core.hooksPath .githooks

.PHONY: create-switch
create-switch: ## Create opam switch
	opam switch create . 5.1.1 --deps-only --with-test -y

.PHONY: install
install:
	opam install . --deps-only --with-test --with-doc --with-dev-setup

.PHONY: pin
pin: ## Pin dependencies
	opam pin add styled-ppx "https://github.com/davesnx/styled-ppx.git#fix/upgrade-srr"
	opam pin add server-reason-react "https://github.com/ml-in-barcelona/server-reason-react.git#main"

.PHONY: init
init: setup-githooks create-switch pin install install-npm ## Create a local dev enviroment

.PHONY: build
build: ## Build
	@$(DUNE) build @server

.PHONY: build-watch
build-watch: ## Build
	@$(DUNE) build @server --watch

.PHONY: build-client
build-client: ## Build Reason code
	@$(DUNE) build @client

.PHONY: build-client-watch
build-client-watch: ## Watch reason code
	@$(DUNE) build -w @client

.PHONY: build-server-prod
build-server-prod: ## Build for production (--profile=prod)
	@$(DUNE) build --profile=prod @server

.PHONY: start-server
start-server: ## Start the server
	@$(DUNE) exec server/server.exe --watch

.PHONY: run
dev: ## Start the server in dev mode
	@watchexec --no-ignore -w .processes/last_built_at.txt -r -c \
	"clear; _build/default/server/server.exe"

.PHONY: watch
watch: ## Build in watch mode
	@$(DUNE) build -w @server

.PHONY: clean
clean: ## Clean artifacts
	@$(DUNE) clean

.PHONY: format
format: ## Format the codebase with ocamlformat/refmt
	@$(DUNE) build @fmt --auto-promote

.PHONY: format-check
format-check: ## Checks if format is correct
	@$(DUNE) build @fmt

.PHONY: help
help: ## Print this help message
	@echo "";
	@echo "List of available make commands:";
	@echo "";
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}';
	@echo "";

.PHONY: docker-build
docker-build: ## docker build
	@docker build . --tag "$(name):$(current_hash)" --platform linux/amd64 --progress=plain

.PHONY: docker-run
docker-run: ## docker run
	@docker run -d --platform linux/amd64 $(name):$(current_hash)
