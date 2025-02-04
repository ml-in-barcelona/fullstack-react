(lang dune 3.17)
(using melange 0.1)

(cram enable)

(name fullstack-reason-react-demo)

(license MIT)

(maintainers "David Sancho <dsnxmoreno@gmail.com>")

(authors "David Sancho <dsnxmoreno@gmail.com>")

(source
 (github ml-in-barcelona/fullstack-reason-react-demo))

(generate_opam_files true)

(implicit_transitive_deps false)

(package
 (name fullstack-reason-react-demo)
 (synopsis "A demo application that showcases fullstack reason react")
 (depends
  (ocaml (>= 5.1.1))
  (reason (>= 3.14.0))
  (melange (and (>= 3.0.0) (< 4.0.0)))

  (lwt (>= 5.6.0))
  (lwt_ppx (>= 2.1.0))
  (yojson (>= 2.2.0))
  (melange-json (>= 1.3.0))
  (melange-json-native (>= 1.3.0))
  (dream (= dream.1.0.0~alpha7))
  melange-webapi
  reason-react
  reason-react-ppx
  ; local deps
  ocamlformat
  ocaml-lsp-server
))
