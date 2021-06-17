#include <stdlib.h>
#include "HsFFI.h"

HsBool haskellHelloLibInit(void){
  int argc = 2;
  char *argv[] = { "+RTS", "-A32m", NULL };
  char **pargv = argv;

  // Initialize Haskell runtime
  hs_init(&argc, &pargv);

  // do any other initialization here and
  // return false if there was a problem
  return HS_BOOL_TRUE;
}

void haskellHelloLibExit(void){
  hs_exit();
}
