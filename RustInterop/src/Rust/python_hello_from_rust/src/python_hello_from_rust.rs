use std::fs;

use pyo3::prelude::*;

#[no_mangle]
pub unsafe extern "C" fn hello_from_python_through_rust() -> Result<(), ()> {

Python::with_gil(|py| {
    my_hello(py).map_err(|e| {
        e.print_and_set_sys_last_vars(py);
    })
  })
}

fn my_hello(py:Python) -> PyResult<()> {
   let code = "print('Hello from Python (through Rust)! As a simple function.')";
   let _message = py.eval(code, None, None)?;
   let my_file_name = "scripts/helloPython.py";
   let contents = fs::read_to_string(my_file_name)
        .expect("Error readig file");
   let _script = PyModule::from_code(py, &contents, "", "")?;
   Ok(())
}
