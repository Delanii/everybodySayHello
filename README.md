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
