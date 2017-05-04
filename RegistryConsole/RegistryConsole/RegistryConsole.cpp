// RegistryConsole.cpp : Defines the entry point for the console application.
// Requires x64 compile
//

#include "stdafx.h"
#include <Windows.h>
#include <winreg.h>
#include <stdio.h>

using namespace std;
#define ACCESS  (KEY_WRITE | KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS)

int main()
{
	HKEY key;
	LPCTSTR subkey = L"Software\\ActiveState\\ActivePython\\2.7.13.2714";
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, ACCESS, &key) != ERROR_SUCCESS) {
		printf("Unable to open registry key!\n");
		printf("Be sure to run cmd prompt as admin\n");
	}
	else {
		printf("Opened key\n");
	}
	return 0;
}