# Overview

This is very small, beginner level project to familiarize with techniques to embed programming languages in an C application, just printing message in terminal and exiting.

# Project layout

This project is split into three directories:

- `RustInterop`: binds Rust directly to C code as dynamically loaded library, then this rust binding is used to connect more languages, currently:

  - luajit: with `mlua` crate
  - python: with `py3o` crate

- `DirectInterop`: all language interpreters are directly bound to C app via C API. All interpreters are also compiled from source

  - luajit
  - python

- CLuaInterop: specific project to showcase embedding lua 5.4 into C app. System lua libraries are used (requires lua 5.4 preinstalled).

# Planned languages

- perl
- java
- clojure
- guile
- raku
- cpp
- haskell
- ocaml

# Building

How to build this repository:

