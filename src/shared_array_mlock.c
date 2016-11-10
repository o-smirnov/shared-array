/* 
 * This file is part of SharedArray.
 * Copyright (C) 2014-2016 Mathieu Mirmont <mat@parad0x.org>
 * 
 * SharedArray is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * SharedArray is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with SharedArray.  If not, see <http://www.gnu.org/licenses/>.
 */

#define NPY_NO_DEPRECATED_API	NPY_1_8_API_VERSION
#define PY_ARRAY_UNIQUE_SYMBOL	SHARED_ARRAY_ARRAY_API
#define NO_IMPORT_ARRAY

#include <Python.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "shared_array.h"

/*
 * Lock the data of an array into memory
 */
static PyObject *do_mlock(PyArrayObject *array)
{

	if( mlock(PyArray_BYTES(array), PyArray_NBYTES(array)) )
		return PyErr_SetFromErrno(PyExc_OSError);


	Py_RETURN_NONE;
}


/*
 * Method: SharedArray.mlock()
 */
PyObject *shared_array_mlock(PyObject *self, PyObject *args)
{
	PyArrayObject *array;


	/* Parse the arguments */
	if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &array))
		return NULL;

	/* Now do the real thing */
	return do_mlock(array);
}
