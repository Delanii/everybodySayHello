.ONESHELL:

#############################
# General make variables
# ##########################

sourceDir = src

scriptDir = scripts

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

luaScriptFile = src/lua/hello.lua

#############################
# Final App
# ##########################

finalApp = everybodySayHello
# execution: LD_LIBRARY_PATH=lib1:libs ./everybodySayHello
# `LD_LIBRARY_PATH` can point to multiple directories

# Just a convinience rule to have cleanLibs rule -- more organized makefile (I hope)
.PHONY : release
release : prepareRelease cleanLibs
	echo "Release finished!"

.PHONY : prepareRelease
prepareRelease : hello clean
	mkdir -p lib1 libs
	scp ${rustProjectDir}/target/release/librust_hello_main_component.so lib1/librust_hello_main_component.so
	scp ${luaProjectDir}/target/release/liblua_hello_from_rust.so libs/liblua_hello_from_rust.so

hello : ${cHelloSrc} rustHello luaHello
	gcc -o ${finalApp} ${cHelloSrc} -L ${rustProjectDir}target/release -L ${luaProjectDir}target/release -lrust_hello_main_component -llua_hello_from_rust -lpthread -ldl -Wall
# linker prefers dynamic libraries, if `-static` is not given. it might not be needed now.

rustHello : ${cargoMannifest} ${cargoSrc}
	cd ${rustProjectDir}
	cargo build --lib --release
	cd ../../..

luaHello : ${luaCargoMannifest} ${luaCargoSrc} ${luaScriptFile}
	cd ${luaProjectDir}
	cargo build --lib --release
	cd ../../..
	mkdir -p scripts
	scp src/lua/hello.lua ${scriptDir}/hello.lua

.PHONY : clean
clean :
	rm -rf *.o

.PHONY : cleanLibs
cleanLibs : clean
	rm -rf ${rustProjectDir}/target ${luaProjectDir}/target

.PHONY : purge
purge : cleanLibs
	rm -rf lib1 libs ${finalApp}
