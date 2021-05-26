.ONESHELL:

#############################
# General make variables
# ##########################

sourceDir = src

#############################
# C make variables
# ##########################

cHelloSrc = src/C/everybodySayHello.c

#############################
# Rust make variables
# ##########################

rustProjectDir = src/Rust/rust_hello_main_component/
cargoMannifest = src/Rust/rust_hello_main_component/Cargo.toml

cargoSrc = src/Rust/rust_hello_main_component/src/rust_hello_main_component.rs

#############################
# Lua make variables
# ##########################

luaProjectDir = src/Rust/lua_hello_from_rust/
luaCargoMannifest = src/Rust/lua_hello_from_rust/Cargo.toml

luaCargoSrc = src/Rust/lua_hello_from_rust/src/lua_hello_from_rust.rs

#############################
# Final App
# ##########################

finalApp = everybodySayHello
# execution: LD_LIBRARY_PATH=src/Rust/lua_hello_from_rust/target/release:src/Rust/rust_hello_main_component/target/release ./everybodySayHello

hello : ${cHelloSrc} rustHello luaHello
	gcc -o ${finalApp} ${cHelloSrc} -L ${rustProjectDir}target/release -L ${luaProjectDir}target/release -lrust_hello_main_component -llua_hello_from_rust -lpthread -ldl -Wall
# linker prefers dynamic libraries, if `-static` is not given. it might not be needed now.

rustHello : ${cargoMannifest} ${cargoSrc}
	cd ${rustProjectDir}
	cargo build --lib --release
	cd ../../..

luaHello : ${luaCargoMannifest} ${luaCargoSrc}
	cd ${luaProjectDir}
	cargo build --lib --release
	cd ../../..

.PHONY : clean
clean :
	rm -rf *.o

.PHONY : purge
purge : clean
	rm -rf ${finalApp} ${rustProjectDir}/target
