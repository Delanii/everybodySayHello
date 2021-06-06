#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "luajit.h"

#define LUA_OK 0

int hello_from_lua(int argc, char ** argv) {

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Our Lua code, it simply prints a Hello, World message
    char * code = "print('Hello from luaJIT! As simple function.')";

    char * filename = "src/lua/helloLuajit.lua";

    // Here we load the string and use lua_pcall for run the code
    if (luaL_loadstring(L, code) == LUA_OK) {
        if (lua_pcall(L, 0, 0, 0) == LUA_OK) {
            // If it was executed successfuly we
            // remove the code from the stack
            lua_pop(L, lua_gettop(L));
        }
    }

    if (luaL_loadfile(L, filename) == LUA_OK) {
        if (lua_pcall(L, 0, 0, 0) == LUA_OK) {
           lua_pop(L, lua_gettop(L));
        }
    }

    lua_close(L);
    return 0;
}
