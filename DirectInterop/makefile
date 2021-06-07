.ONESHELL:

#############################
# General make variables
# ##########################

sourceDir = src

headerDir = headers
libDir = libs
scriptDir = scripts

makeHeaderDir = mkdir -p headers
makeLibDir = mkdir -p libs
makeScriptDir = mkdir -p scripts

#############################
# C make variables
# ##########################

cSrcDir = src/C

cHello = everybodySayHello.c

CFLAGS = -Llibs -Wall -Werror -pedantic
CDYNLIBFLAGS = -shared -fpic
CLIBS = -ldl -lpthread

#############################
# Rust make variables
# ##########################

rustProjectDir = src/Rust/rust_hello/
cargoMannifest = src/Rust/rust_hello/Cargo.toml

cargoSrc = src/Rust/rust_hello/src/rust_hello.rs

cargoFlags = --lib --release

cargoReleasePath = /target/release/

rustLibName = librust_hello.so

#############################
# Lua make variables
# ##########################

luajitEmbeddingSrc = src/C/libluajithello.c

luajitSrc = src/lua/luajit
luajitHeader = luajit.h
luajitLib = libluajit.so

luajitHelloLib = libluajithello.so

luaSrc = src/lua
luaScript = helloLuajit.lua

#############################
# Variables for tests
# ##########################

helloOutputFile = helloOutput.txt
expectedOutputFile = src/expectedOutput.txt

#############################
# Final App
# ##########################

finalApp = everybodySayHello
# execution: LD_LIBRARY_PATH=libs ./everybodySayHello

.PHONY : release
release : test clean
	@printf "\n\nRelease finished!\n"

hello : ${cSrcDir}/${cHello} rustHello luaHello
	gcc ${CFLAGS} -lrust_hello -lluajithello -o ${finalApp} ${cSrcDir}/${cHello}
# linker prefers dynamic libraries, if `-static` is not given. it might not be needed now.

rustHello : ${cargoMannifest} ${cargoSrc}
	cd ${rustProjectDir}
	@printf "\nEntered Rust project directory: ${PWD}\n"
	cargo build ${cargoFlags}
	cd ../../..
	@printf "\nEntering project root directory: ${PWD}\n"
	@printf "\nCopying Rust library to libs/ folder\n."
	${makeLibDir}
	scp ${rustProjectDir}${cargoReleasePath}${rustLibName} libs/${rustLibName}

luaHello : ${luaScriptFile} ${luajitEmbeddingSrc}
	@printf "\nBuilding luaJIT"
	cd ${luajitSrc}
	@printf "Entered luaJIT source folder: ${PWD}\n"
	make
	cd ../../..
	@printf "Entered project root folder: ${PWD}\n"
	${makeHeaderDir}
	${makeLibDir}
	scp ${luajitSrc}/src/${luajitHeader} ${headerDir}/${luajitHeader}
	scp ${luajitSrc}/src/${luajitLib} ${libDir}/${luajitLib}
	@printf "\nBuilding luaHello shared library.\n"
	gcc -Iheaders ${CDYNLIBFLAGS} ${CFLAGS} ${CLIBS} -llua -lluajit -lm -o ${luajitHelloLib} ${luajitEmbeddingSrc}
	@printf "\nCopying lua hello library to libs/ folder\n"
	mv ${luajitHelloLib} libs/${luajitHelloLib}
	@printf "\nCopying lua script to scripts/ directory\n"
	${makeScriptDir}
	scp ${luaSrc}/${luaScript} ${scriptDir}/${luaScript}

# Záolžka
.PHONY : test
test : hello
	@printf "\nRunning tests\n\n"
	LD_LIBRARY_PATH=libs ./everybodySayHello | tee ${helloOutputFile}
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
	rm -rf libs headers scripts ${finalApp}
