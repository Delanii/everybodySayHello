module HaskellHello where

import HaskellSay (haskellSay)
import Foreign.C
import Foreign

foreign export ccall hello_from_haskell :: IO()

hello_from_haskell :: IO()
hello_from_haskell = do 
    let greeting = "Hello from Haskell! As a simple function."
    haskellSay greeting
