Reference:

https://wiki.haskell.org/Calling_Haskell_from_C
https://downloads.haskell.org/~ghc/latest/docs/html/users_guide/exts/ffi.html#ffi-library

Reference:
https://downloads.haskell.org/~ghc/latest/docs/html/users_guide/shared_libs.html
ghc v. 9.0.0:

ghc --make -dynamic -shared -fPIC -flink-rts Foo.hs -o libfoo.so

Dynamic linking reference:

https://www.vex.net/~trebla/haskell/so.xhtml

https://stackoverflow.com/questions/3859340/calling-haskell-from-c-code

Building with Cabal:

https://cabal.readthedocs.io/en/latest/cabal-package.html (vyhledat foreign-libraries)
