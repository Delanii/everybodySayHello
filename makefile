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
# Final App
# ##########################

finalApp = everybodySayHello

hello : ${cHelloSrc} rustHello
	gcc -o ${finalApp} ${cHelloSrc} -L ${rustProjectDir}target/release -lrust_hello_main_component -Wall
# linker prefers dynamic libraries, if `-static` is not given. it might not be needed now.

rustHello : ${cargoMannifest} ${cargoSrc}
	cd ${rustProjectDir}
	cargo build --lib --release

.PHONY : clean
clean :
	rm -rf *.o

.PHONY : purge
purge : clean
	rm -rf ${finalApp} ${rustProjectDir}/target
