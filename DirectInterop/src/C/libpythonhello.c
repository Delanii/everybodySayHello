#include <stdio.h>
#include <Python.h>

int hello_from_python(int argc, char ** argv) {

    char * code = "print('Hello from Python! As simple function.')";

	char * filename = "scripts/helloPython.py";
	FILE* fp;

	Py_Initialize();

	PyRun_SimpleString(code);

	fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();

	return 0;
}
