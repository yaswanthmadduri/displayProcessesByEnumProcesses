/* https://docs.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-enumprocesses */

#include <Windows.h>
#include <Psapi.h>
#include <wchar.h>
#include <tchar.h>
#include <iostream>

using namespace std;

void processDetails(DWORD dwprocessID) {

	HANDLE hProcess;
	DWORD bytesNeededForStoring = 0;
	DWORD dwDesiredAccess = PROCESS_ALL_ACCESS;
	cout << "checking if gits working" << endl;
	BOOL bInheritHandle = FALSE;
	BOOL bEnumProcessModule = FALSE;
	TCHAR ProcessName[] = TEXT("Unknown/ hidden");
	TCHAR ProcessPath[] = TEXT("Unknown/ hidden Process Path");

	hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwprocessID);

	if (hProcess != NULL) {
		GetModuleBaseName(hProcess, NULL, ProcessName, sizeof(ProcessName) / sizeof(TCHAR));

		GetModuleFileNameEx(hProcess, NULL, ProcessPath, sizeof(ProcessPath) / sizeof(TCHAR));

	}

	_tprintf(TEXT("Module base name : %s \n"), ProcessName);
	_tprintf(TEXT("Process path : %s \n"), ProcessPath);
	wcout << "Process identifier : " << dwprocessID << endl << endl;
	cout << "---------------------------------------" << endl;

	if (hProcess) {

		CloseHandle(hProcess);

	}

}


int main() {



	DWORD* ptr;
	ptr = (DWORD*)malloc(5 * sizeof(DWORD));
	if (ptr == NULL)
	{
		cout << "Memory Allocation Failed";
		exit(1);
	}

	/* Initializing memory block */
	for (int i = 0; i < 5; i++)
	{
		ptr[i] = i * 1.5;
	}

	/* reallocating memory */
	ptr = (DWORD*)realloc(ptr, 10 * sizeof(DWORD));
	if (ptr == NULL)
	{
		cout << "Memory Re-allocation Failed";
		exit(1);
	}

	/* Initializing re-allocated memory block */
	for (int i = 5; i < 10; i++)
	{
		ptr[i] = i * 2.5;
	}
	cout << "Printing Values" << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << ptr[i] << endl;
	}
	free(ptr);































	//DWORD processIdentifiers[100] = { 0 };
	
	DWORD* processIdentifiers;
	processIdentifiers = (DWORD*)malloc(5 * sizeof(DWORD));
	if (processIdentifiers == NULL)
	{
		cout << "Memory Allocation Failed";
		exit(1);
	}
	else {
		cout << "allocated re : " << sizeof(processIdentifiers) << endl;
	}


	/* reallocating memory */
	processIdentifiers = (DWORD*)realloc(processIdentifiers, 10 * sizeof(DWORD));
	if (processIdentifiers == NULL)
	{
		cout << "Memory Re-allocation Failed";
		exit(1);
	}

	else {
		cout << "reallocated rey" << endl;
	}

	DWORD bytesNeededForStoring = 0;
	BOOL bEnumProcess = EnumProcesses(processIdentifiers, sizeof(processIdentifiers), &bytesNeededForStoring);
	if (bEnumProcess == FALSE) {
		cout << "ENUM Process identifier fetching function failed " << endl << endl;
		cout << "Error code: " << GetLastError() << endl;
		return 0;
	}
	DWORD totalNoOfProcesses = bytesNeededForStoring / sizeof(DWORD);
	cout << "ENUM Process identifier fetching function succeeded"<< totalNoOfProcesses << endl << endl;


	if (bytesNeededForStoring == sizeof(processIdentifiers)) {

		//DWORD size;
		//cin >> size;
		//DWORD* processIdentifiers = new DWORD[size];

		DWORD processIdentifiers[300];
		DWORD bytesNeededForStoring = 0;
		int size = sizeof(processIdentifiers);
		cout << "size of processIdentifiers : " << size << endl;
		BOOL bProcessEnum = EnumProcesses(processIdentifiers, sizeof(processIdentifiers), &bytesNeededForStoring);
		if (bEnumProcess == FALSE) {
			cout << "ENUM Process identifier fetching function failed " << endl << endl;
			cout << "Error code: " << GetLastError() << endl;
			return 0;
		}
		DWORD totalNoOfProcesses = bytesNeededForStoring / sizeof(DWORD);
		cout << "size of processIdentifiers : " << size << endl;
		cout << "ENUM Process identifier fetching function succeeded inside if " << endl << endl;



		for (DWORD l_proc_index = 0; l_proc_index < totalNoOfProcesses; l_proc_index++) {

			processDetails(processIdentifiers[l_proc_index]);

		}

		wcout << "Total number of processes running : " << totalNoOfProcesses << endl;
	}



	return 0;
}

/*

if (y == bytesNeededForStoring) {
		//we dont know if processes still exist
		int	x = sizeof(processIdentifiersInitially) + 1;
		cout << "sizeof(processIdentifiers)" << sizeof(processIdentifiersInitially) << endl;
		cout << "x=" << x << endl;
	}


*/