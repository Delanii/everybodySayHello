use std::fs;

use pyo3::prelude::*;

#[no_mangle]
pub unsafe extern "C" fn hello_from_python_through_rust() -> Result<(), ()> {

Python::with_gil(|py| {
    hello_code(py).map_err(|e| {
        e.print_and_set_sys_last_vars(py);
    })
  })

}

fn hello_code(py:Python) -> PyResult<()> {
   let code = "print('Hello from Python (through Rust)! As Python a siple function.')";
   let message = py.eval(code, None, None)?;
   Ok(())
}
