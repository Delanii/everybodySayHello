#include <stdio.h>
#include <Python.h>

int hello_from_python(int argc, char ** argv) {

    char * code = "print('Hello from Python! As simple function.')";

	Py_Initialize();

	PyRun_SimpleString(code);

	Py_Finalize();

	return 0;
}
