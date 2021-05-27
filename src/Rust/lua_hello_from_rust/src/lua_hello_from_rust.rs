use mlua::prelude::*;

use mlua::{Function, Lua, Result};

#[no_mangle]
pub unsafe extern "C" fn hello_from_lua_through_rust() -> Result<()> {
    let lua = Lua::new();   // Build new Lua state

    let globals = lua.globals(); // namespace assignment

    // Loading lua `print` function to get the lua greeting

    let print: Function = globals.get("print")?;
    print.call::<_, ()>("Hello from lua (through Rust)! As a simple function.\n")?;

    Ok(())
}
