#include <Windows.h>
#include <Psapi.h>
#include <wchar.h>
#include <tchar.h>
#include <iostream>

using namespace std;

//function declaration before main fn;
void processDetails(DWORD dwprocessID);


int main() {
	
	DWORD proc_array_len = 400;//in bytes (each dword is of 4 bytes)
	DWORD* ptr_proc_identifiers;// pointer to proc_identifiers
	ptr_proc_identifiers = (DWORD*)malloc(proc_array_len * sizeof(DWORD));//holds address of first place in the dynamically created array
	if (ptr_proc_identifiers == NULL)
	{
		cout << "Memory Allocation Failed";
		exit(1);
	}
	else {
		cout << "Memory is now allocated to store " << proc_array_len / sizeof(DWORD) << " process identifiers." << endl;
	}

	DWORD bytesNeededForStoring = 0;
	BOOL bEnumProcess = EnumProcesses(ptr_proc_identifiers, proc_array_len, &bytesNeededForStoring);
	if (bEnumProcess == FALSE) {
		cout << "ENUM Process identifier fetching function failed " << endl << endl;
		cout << "Error code: " << GetLastError() << endl;
		return 0;
	}
	//cout << "ENUMProcesses function fetched" << proc_array_len / sizeof(DWORD) << "process identifiers" << endl << endl;

	//when bytesneededforstoring == length of process identifiers array

	while (bytesNeededForStoring == proc_array_len) {

		proc_array_len = proc_array_len + 100;// 100 bytes means 25 new processes can be stored (size of each dword is 4 bytes)
		ptr_proc_identifiers = (DWORD*)realloc(ptr_proc_identifiers, proc_array_len * sizeof(DWORD));
		if (ptr_proc_identifiers == NULL)
		{
			cout << "Memory Re-allocation failed";
			exit(1);
		}
		else {
			cout << "Memory is now re-allocated to store " << proc_array_len / sizeof(DWORD) << " process identifiers." << endl;
		}

		BOOL bEnumProcess = EnumProcesses(ptr_proc_identifiers, proc_array_len, &bytesNeededForStoring);

	}

	DWORD totalNoOfProcesses = bytesNeededForStoring / sizeof(DWORD);

	for (DWORD l_proc_index = 1; l_proc_index <= totalNoOfProcesses; l_proc_index++) {

		cout << "Process " << l_proc_index << ": " << endl;
		processDetails(ptr_proc_identifiers[l_proc_index]);

	}

	cout << "Total number of processes : " << totalNoOfProcesses << endl;

	free(ptr_proc_identifiers);

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

	_tprintf(TEXT("Process name : %s \n"), ProcessName);
	_tprintf(TEXT("Process path : %s \n"), ProcessPath);
	wcout << "Process identifier : " << dwprocessID << endl << endl;
	cout << "---------------------------------------" << endl;

	if (hProcess) {

		CloseHandle(hProcess);

	}

}
