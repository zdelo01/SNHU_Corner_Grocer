#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

/*
Zachary DeLong
CS-210
10/16/2022
*/

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
    char* procname = new char[pName.length() + 1];
    std::strcpy(procname, pName.c_str());

    Py_Initialize();
    PyObject* my_module = PyImport_ImportModule("PythonCode");
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, procname);
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();

    delete[] procname;
}

/*
Description: To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
	    pValue = Py_BuildValue("(z)", paramval);
	    PyErr_Print();
	    presult = PyObject_CallObject(pFunc, pValue);
	    PyErr_Print();
	}
	else
	{
	    PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonCode");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
	pValue = Py_BuildValue("(i)", param);
	PyErr_Print();
	presult = PyObject_CallObject(pFunc, pValue);
	PyErr_Print();
    }
    else
    {
	PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;

    return _PyLong_AsInt(presult);
}

/*
Description: prints asterisks equal to the value passed by param
Example: if freq = 3 -> execute 'cout << "*"' 3 times 
@param freq - frequency of a word passed while reading 'frequency.dat'
@return - N/A
*/

void printAsterisk(int freq)
{
	for (int i = 0; i < freq; i++)
	{
		cout << "*";
	}
}
/*
Description: Reads 'frequency.dat' and outputs the list of items with asterisks in the value's place.
             Output is similar to "determineInventory", however, the values are converted to asterisks
@param - N/A
@return - N/A  
*/
void printHistogram()
{
	ifstream readDat;
	string name = "";
	int frequency = 0;

	readDat.open("frequency.dat");
	// Open file check
	if (!(readDat.is_open()))   
	{
		cout << "Fatal Error: file not found.";
		exit (0);
	}

	cout << "-----------------------------" << endl;
	cout << "**Histogram**" << endl << endl;

	while (!(readDat.eof())) 
	{
		getline(readDat, name, ' ');
		readDat >> frequency;
		cout << name << ": ";
		printAsterisk(frequency);
	}
	cout << endl << "-----------------------------" << endl;
    // Close file
	readDat.close();
}

void main()
{

	int choice = 0;
	int value = 0;
	string item = "";
	// Loop runs until user enters '4' to quit
	while (true) 
	{
		// Display Menu
		cout << "1: Get groceries purchased\n";
		cout << "2: Get frequency for an item\n";
		cout << "3: Get text-Based histogram\n";
		cout << "4: Exit\n";
		cout << "Enter your selection as a number 1, 2, 3, or 4.\n";

		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "-----------------------------" << endl;
			cout << "**Inventory**" << endl << endl;
			CallProcedure("determineInventory");
			cout << "-----------------------------" << endl;
			break;
		case 2:
			cout << "Enter item: " << endl;
			cin >> item;
			cout << "-----------------------------" << endl;
		    cout << "**'" << item << "' Occurrence: " << callIntFunc("determineFrequency", item) << "**" << endl;
			cout << "-----------------------------" << endl;
			break;
		case 3:
			CallProcedure("output");
			printHistogram();	
			break;
		case 4:
			cout << "Goodbye.";
			exit(0);
			break;
		default:
			cout << "Error: Input is Invalid " << endl << endl;
			break;
		}
	}
}
