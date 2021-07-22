#include <Windows.h>
#include <Psapi.h>
#include <wchar.h>
#include <tchar.h>
#include <iostream>

using namespace std;

//function declaration before main fn;
void processDetails(DWORD dwprocessID);


int main() {

	//DWORD processIdentifiers[100] = { 0 };
	
	DWORD lengthOfArray = 300;//in bytes
	DWORD* processIdentifiers;
	processIdentifiers = (DWORD*)malloc(lengthOfArray * sizeof(DWORD));//holds address of first place in the dynamically created array
	if (processIdentifiers == NULL)
	{
		cout << "Memory Allocation Failed";
		exit(1);
	}
	else {
		cout << "Memory is now allocated" << endl;
	}

	cout << "process identifiers allocated : " << lengthOfArray / sizeof(DWORD)  << endl;

	DWORD bytesNeededForStoring = 0;
	BOOL bEnumProcess = EnumProcesses(processIdentifiers, lengthOfArray, &bytesNeededForStoring);
	if (bEnumProcess == FALSE) {
		cout << "ENUM Process identifier fetching function failed " << endl << endl;
		cout << "Error code: " << GetLastError() << endl;
		return 0;
	}
	cout << "ENUM Process identifier fetching function succeeded" << endl << endl;

	//when bytesneededforstoring == length of process identifiers array

	while (bytesNeededForStoring == lengthOfArray) { 

		lengthOfArray = lengthOfArray + 100;
		processIdentifiers = (DWORD*)realloc(processIdentifiers, lengthOfArray * sizeof(DWORD));
		if (processIdentifiers == NULL)
		{
			cout << "Memory ReAllocation Failed";
			exit(1);
		}
		else {
			cout << "Memory is now re-allocated" << endl;
		}

		BOOL bEnumProcess = EnumProcesses(processIdentifiers, lengthOfArray, &bytesNeededForStoring);
		cout << lengthOfArray / sizeof(DWORD) << " : These many processes can fit in the process identifier array now" << endl; 

	}

	DWORD totalNoOfProcesses = bytesNeededForStoring / sizeof(DWORD);

	for (DWORD l_proc_index = 0; l_proc_index < totalNoOfProcesses; l_proc_index++) {

		processDetails(processIdentifiers[l_proc_index]);

	}

	cout << "Total number of processes : " << totalNoOfProcesses << endl;

	free(processIdentifiers);

	return 0;
}


void processDetails(DWORD dwprocessID) {

	HANDLE hProcess;
	DWORD bytesNeededForStoring = 0;
	DWORD dwDesiredAccess = PROCESS_ALL_ACCESS;
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

/*

if (y == bytesNeededForStoring) {
		//we dont know if processes still exist
		int	x = sizeof(processIdentifiersInitially) + 1;
		cout << "sizeof(processIdentifiers)" << sizeof(processIdentifiersInitially) << endl;
		cout << "x=" << x << endl;
	}


*/