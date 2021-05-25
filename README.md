# Overview

This is very small, beginner level project to familiarize with techniques to embed programming languages in an C application, just printing message in terminal and exiting.

# Planned laguages

- C : as a base for application runtime
- Rust : as first guess language and also platform to embed more languages:

  - lua with `mlua`
  
- lua : embedded directly in C runtime and with Rust via `mlua` crate

# Building

How to build this repository:

1. `make hello` builds binary `everybodySayHello`
2. depending to type of linking binary has to be executed:

   - dynamic linking (in `src/Rust/rust_hello_main_component/Cargo.toml` is `crate-type` specified as `cdylib`):
   
     ```shell
     LD_LIBRARY_PATH=/path/to/output/library/in/target/folder ./everybodySayHello
     ```
     
   - static linking (in `src/Rust/rust_hello_main_component/Cargo.toml` is `crate-type` specified as `staticlib`)
   
     ```shell
   ./everybodySayHello
     ```
