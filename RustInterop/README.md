# Rust Interop

This part of the project is to explore options of embedding other programming languages, be it interpreters or just source from other compiled language, through Rust into a C application. It is just to find out the correct packages/crates and compilation flags. Code itself are just simple print statements.

Currently, there are two languages added:

- lua with `mlua` crate in form of luaJIT interpreter
- python with `py3o` crate in form of standard Cpython. Pypy is not really supported (should test that nonetheless) (WIP)

# How to build

