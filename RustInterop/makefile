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
# Python make variables
# ##########################

pythonProjectDir = src/Rust/python_hello_from_rust/

pythonCargoMannifest = src/Rust/python_hello_from_rust/Cargo.toml
pythonCargoSrc = src/Rust/python_hello_from_rust/src/python_hello_from_rust.rs

pythonLibName = libpython_hello_from_rust.so

pythonScriptFile = src/python/helloPython.py

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

hello : ${cHelloSrc} rustHello luaHello pythonHello
	gcc -o ${finalApp} ${cHelloSrc} -L lib1 -L libs -lrust_hello_main_component -llua_hello_from_rust -lpython_hello_from_rust -lpthread -ldl -Wall
# linker prefers dynamic libraries, if `-static` is not given. it might not be needed now.
# $$(pkg-config --cflags python3) double dollar signs are used to escape pkg-config expression, which should find correct flags

rustHello : ${cargoMannifest} ${cargoSrc}
	cd ${rustProjectDir}
	@printf "\nEntered Rust project directory: ${PWD}\n"
	cargo build ${cargoFlags}
	cd ../../..
	@printf "\nReturning to project main directory: ${PWD}\n"
	@printf "\nCopying Rust library to lib1/ folder\n."
	${makeLibDirectories}
	scp ${rustProjectDir}${cargoReleasePath}${rustLibName} lib1/${rustLibName}

luaHello : ${luaCargoMannifest} ${luaCargoSrc} ${luaScriptFile}
	cd ${luaProjectDir}
	@printf "\nEntered lua project directory: ${PWD}\n"
	cargo build ${cargoFlags}
	cd ../../..
	@printf "\nReturning to project main directory: ${PWD}\n"
	@printf "\nCopying lua library to libs/ folder\n"
	${makeLibDirectories}
	scp ${luaProjectDir}${cargoReleasePath}${luaLibName} libs/${luaLibName}
	@printf "\nCopying lua script to scripts/ directory\n"
	${makeScriptDirectory}
	scp ${luaScriptFile} ${scriptDir}/helloLuajit.lua

pythonHello : ${pythonCargoMannifest} ${pythonCargoSrc} ${pythonScriptFile}
	cd ${pythonProjectDir}
	@printf "\nEntered python project directory: ${PWD}\n"
	cargo build ${cargoFlags}
	cd ../../..
	@printf "\nReturning to project main directory: ${PWD}\n"
	@printf "\nCopying python library to libs/ folder\n"
	${makeLibDirectories}
	scp ${pythonProjectDir}${cargoReleasePath}${pythonLibName} libs/${pythonLibName}
	@printf "\nCopying python script to scripts/ directory\n"
	${makeScriptDirectory}
	scp ${pythonScriptFile} ${scriptDir}/helloPython.py

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
	rm -rf ${pythonProjectDir}target/rls
	rm -rf ${pythonProjectDir}${cargoReleasePath}deps ${pythonProjectDir}${cargoReleasePath}build
	rm -rf ${helloOutputFile}

.PHONY : purge
purge : clean
	rm -rf lib1 libs ${finalApp}
