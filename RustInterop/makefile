.ONESHELL:

#############################
# General make variables
# ##########################

sourceDir = src

scriptDir = scripts

makeLibDirectories = mkdir -p lib1 libs
makeScriptDirectory = mkdir -p scripts

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

cargoFlags = --lib --release

cargoReleasePath = /target/release/

rustLibName = librust_hello_main_component.so

#############################
# Lua make variables
# ##########################

luaProjectDir = src/Rust/lua_hello_from_rust/

luaCargoMannifest = src/Rust/lua_hello_from_rust/Cargo.toml
luaCargoSrc = src/Rust/lua_hello_from_rust/src/lua_hello_from_rust.rs

luaLibName = liblua_hello_from_rust.so

luaScriptFile = src/lua/helloLuajit.lua

#############################
# Variables for tests
# ##########################

helloOutputFile = helloOutput.txt
expectedOutputFile = src/expectedOutput.txt

#############################
# Final App
# ##########################

finalApp = everybodySayHello
# execution: LD_LIBRARY_PATH=lib1:libs ./everybodySayHello
# `LD_LIBRARY_PATH` can point to multiple directories

.PHONY : release
release : test clean
	@printf "\n\nRelease finished!\n"

hello : ${cHelloSrc} rustHello luaHello
	gcc -o ${finalApp} ${cHelloSrc} -L lib1 -L libs -lrust_hello_main_component -llua_hello_from_rust -lpthread -ldl -Wall
# linker prefers dynamic libraries, if `-static` is not given. it might not be needed now.

rustHello : ${cargoMannifest} ${cargoSrc}
	@printf "\nEntering Rust project directory\n"
	cd ${rustProjectDir}
	cargo build ${cargoFlags}
	@printf "\nLeaving Rust project directory\n"
	cd ../../..
	@printf "\nCopying Rust library to lib1/ folder\n."
	${makeLibDirectories}
	scp ${rustProjectDir}${cargoReleasePath}${rustLibName} lib1/${rustLibName}

luaHello : ${luaCargoMannifest} ${luaCargoSrc} ${luaScriptFile}
	@printf "\nEntering lua project directory\n"
	cd ${luaProjectDir}
	cargo build ${cargoFlags}
	@printf "\nLeaving lua project directory\n"
	cd ../../..
	@printf "\nCopying lua library to libs/ folder\n"
	${makeLibDirectories}
	scp ${luaProjectDir}${cargoReleasePath}${luaLibName} libs/${luaLibName}
	@printf "\nCopying lua script to scripts/ directory\n"
	${makeScriptDirectory}
	scp ${luaScriptFile} ${scriptDir}/helloLuajit.lua

.PHONY : test
test : hello
	@printf "\nRunning tests\n\n"
	LD_LIBRARY_PATH=lib1:libs ./everybodySayHello | tee ${helloOutputFile}
	diff ${helloOutputFile} ${expectedOutputFile}
	@printf "\nTests succesfull\n"

.PHONY : clean
clean :
	@printf "\nCleaning build artifacts\n"
	rm -rf *.o
	rm -rf ${rustProjectDir}target/rls
	rm -rf ${rustProjectDir}${cargoReleasePath}deps ${rustProjectDir}${cargoReleasePath}build
	rm -rf ${luaProjectDir}target/rls
	rm -rf ${luaProjectDir}${cargoReleasePath}deps ${luaProjectDir}${cargoReleasePath}build
	rm -rf ${helloOutputFile}

.PHONY : purge
purge : clean
	rm -rf lib1 libs ${finalApp}
