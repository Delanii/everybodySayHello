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

CFLAGS = -Llibs -Wall -Werror -O3
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
# Python make variables
# ##########################

pythonEmbeddingSrc = src/C/libpythonhello.c

pythonHelloLib = libpythonhello.so

pythonSrc = src/python
pythonScript = helloPython.py

#############################
# Guile make variables
# ##########################

guileEmbeddingSrc = src/C/libguilehello.c

guileHelloLib = libguilehello.so

guileSrc = src/guile
guileScript = helloGuile.scm

##############################
# Perl make variables
# ##########################

perlEmbeddingSrc = src/C/libperlhello.c

perlHelloLib = libperlhello.so

perlSrc = src/perl
perlScript = helloPerl.pl

##############################
# C++ make variables
# ##########################

cppEmbeddingSrc = src/Cpp/libcpphello.cpp

cppHelloLib = libcpphello.so

##############################
# Haskell make variables
# ##########################

haskellProjectDir = src/Haskell

haskellEmbeddingSrc = src/Haskell/src/HaskellHello.hs
haskellEmbeddingWrapper = src/Haskell/src/wrapper.c

cabalSettings = src/Haskell/HaskellHello.cabal
cabalTargetDir = src/Haskell/dist-newstyle/build/x86_64-linux/ghc-8.10.5/HaskellHello-0.1.0.0/f/haskellhello/build/haskellhello
haskellTargetLib = libhaskellhello.so.0.0.1

haskellHelloLib = libhaskellhello.so.0

##############################
# Java make variables
# ##########################

openjdkFolder = /usr/lib/jvm/java-15-openjdk

javaProjectDir = src/Java

javaHelloClass = helloJava.java
javaVMInit = hello_from_java.c

javaHelloLib = libjavahello.so

############################
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

hello : ${cSrcDir}/${cHello} rustHello luaHello pythonHello guileHello perlHello cppHello haskellHello javaHello
	gcc ${CFLAGS} -lrust_hello -lluajithello -lpythonhello -lguilehello -lperlhello -lcpphello -lstdc++ -l:libhaskellhello.so.0 -ljavahello -L${openjdkFolder}/lib/server/ -ljvm -o ${finalApp} ${cSrcDir}/${cHello}
# linker prefers dynamic libraries, if `-static` is not given. it might not be needed now.

rustHello : ${cargoMannifest} ${cargoSrc}
	cd ${rustProjectDir}
	@printf "\nEntered Rust project directory: ${PWD}\n"
	cargo build ${cargoFlags}
	cd ../../..
	@printf "\nEntering project root directory: ${PWD}\n"
	@printf "\nCopying Rust library to libs/ folder\n."
	${makeLibDir}
	scp ${rustProjectDir}${cargoReleasePath}${rustLibName} ${libDir}/${rustLibName}

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

pythonHello : ${pythonScriptFile} ${pythonEmbeddingSrc}
	@printf "\nBuilding pythonHello shared library.\n"
	gcc -Iheaders ${CDYNLIBFLAGS} ${CFLAGS} $$(python3.9-config --cflags) ${CLIBS} -lm $$(python3.9-config --embed --ldflags) -o ${pythonHelloLib} ${pythonEmbeddingSrc} # --embed also adds -lpython3.9
	@printf "\nCopying python hello library to libs/ folder\n"
	${makeLibDir}
	mv ${pythonHelloLib} ${libDir}/${pythonHelloLib}
	@printf "\nCopying python script to scripts/ directory\n"
	${makeScriptDir}
	scp ${pythonSrc}/${pythonScript} ${scriptDir}/${pythonScript}

guileHello : ${guileScriptFile} ${guileEmbeddingSrc}
	@printf "\nBuilding guilehello shared library.\n"
	gcc -Iheaders ${CDYNLIBFLAGS} ${CFLAGS} $$(pkg-config guile-2.2 --cflags) ${CLIBS} -lm $$(pkg-config guile-2.2 --libs) -o ${guileHelloLib} ${guileEmbeddingSrc}
	@printf "\nCopying guile hello library to libs/ folder\n"
	${makeLibDir}
	mv ${guileHelloLib} ${libDir}/${guileHelloLib}
	@printf "\nCopying guile script to scripts/ directory\n"
	${makeScriptDir}
	scp ${guileSrc}/${guileScript} ${scriptDir}/${guileScript}

perlHello : ${perlScriptFile} ${perlEmbeddingSrc}
	@printf "\nBuilding perlhello shared library.\n"
	gcc ${CDYNLIBFLAGS} ${CFLAGS} ${CLIBS} -lm -o ${perlHelloLib} ${perlEmbeddingSrc} $$(perl -MExtUtils::Embed -e ccopts -e ldopts) # This is the only correct sequence of compilation flags, otherwise references are not found ...
	@printf "\nCopying perl hello library to libs/ folder\n"
	${makeLibDir}
	mv ${perlHelloLib} ${libDir}/${perlHelloLib}
	@printf "\nCopying perl script to scripts/ directory\n"
	${makeScriptDir}
	scp ${perlSrc}/${perlScript} ${scriptDir}/${perlScript}

cppHello : ${cppEmbeddingSrc}
	@printf "\nBuilding cpphello shared library.\n"
	g++ ${CDYNLIBFLAGS} -o ${cppHelloLib} ${cppEmbeddingSrc}
	@printf "\nCopying cpp hello library to libs/ folder\n"
	${makeLibDir}
	mv ${cppHelloLib} ${libDir}/${cppHelloLib}

haskellHello : ${haskellEmbeddingSrc} ${haskellEmbeddingWrapper} ${cabalSettings}
	cd ${haskellProjectDir}
	@printf "\nEntered HaskellHello project directory ${PWD}"
	cabal build
	@printf "\nReturning to project root directory ${PWD}"
	cd ../..
	@printf "\nCopying haskell hello library to libs/ folder\n"
	${makeLibDir}
	scp ${cabalTargetDir}/${haskellTargetLib} ${libDir}/${haskellHelloLib}

javaHello : ${javaProjectDir}/${javaHelloClass} ${javaProjectDir}/${javaVMInit}
	@printf "\nEntering Java project directory ${PWD}\n"
	cd ${javaProjectDir}
	javac ${javaHelloClass}
	gcc -o ${javaHelloLib} -I${openjdkFolder}/include/ -I${openjdkFolder}/include/linux -L${openjdkFolder}/lib/server/ -ljvm ${CDYNLIBFLAGS} ${javaVMInit}
	cd ../..
	@printf "\nReturned to project root directory ${PWD}\n"
	@printf "\nMoving Java hello lib to libs/ folder\n"
	mv ${javaProjectDir}/${javaHelloLib} ${libDir}/${javaHelloLib}
	@printf "\nMoving java hello class to libs/ directory\n"
	mv ${javaProjectDir}/helloJava.class ${libDir}/helloJava.class

.PHONY : test
test : hello
	@printf "\nRunning tests\n\n"
	LD_LIBRARY_PATH=libs:${openjdkFolder}/lib/server ./everybodySayHello | tee ${helloOutputFile}
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
	rm -rf ${haskellProjectDir}/dist-newstyle
	rm -rf ${helloOutputFile}
	rm -f ${javaProjectDir}/helloJava.class

.PHONY : purge
purge : clean
	rm -rf ${libDir} ${headerDir} ${scriptDir} ${finalApp}
