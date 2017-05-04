// InternetCheckConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <WinInet.h>
#include <stdio.h>

#pragma comment(lib, "Wininet.lib")


int main()
{
	LPCTSTR url = L"http://www.google.com";
	if (InternetCheckConnection(url, FLAG_ICC_FORCE_CONNECTION, 0)) {
		printf("Connection successful\n");
	}
	else {
		printf("Connection failed\n");
	}

	return 0;
}