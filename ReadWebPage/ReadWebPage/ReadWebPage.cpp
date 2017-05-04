// ReadWebPage.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "Winhttp.h"
#include <stdio.h>
#include <string>
#include <fstream>

#pragma comment(lib, "winhttp.lib")

using namespace std;

BOOL ReadWebPage(string &source, bool secure, const wchar_t *url, const wchar_t *verb)
{
	source = "error";
	BOOL  bResults = FALSE;
	HINTERNET hsession = NULL;
	HINTERNET hconnect = NULL;
	HINTERNET hrequest = NULL;

	hsession = WinHttpOpen(L"Example", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	if (!hsession) goto error;

	hconnect = WinHttpConnect(hsession, url, secure ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT, 0);
	if (!hconnect) goto error;

	hrequest = WinHttpOpenRequest(hconnect, L"GET", verb, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, secure ? WINHTTP_FLAG_SECURE : 0);
	if (!hrequest) goto error;

	if (!WinHttpSendRequest(hrequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0))
		goto error;

	if (!WinHttpReceiveResponse(hrequest, NULL))
		goto error;

	source = "";
	for (DWORD size = 1, downloaded = 1; downloaded > 0;)
	{
		WinHttpQueryDataAvailable(hrequest, &size);
		if (!size) break;
		string buf(size + 1, 0);
		WinHttpReadData(hrequest, (LPVOID)&buf[0], size, &downloaded);
		buf.resize(downloaded);
		source += buf;
	}

error:
	if (hrequest) WinHttpCloseHandle(hrequest);
	if (hconnect) WinHttpCloseHandle(hconnect);
	if (hsession) WinHttpCloseHandle(hsession);

	return bResults;
}

int main()
{
	string src;

	//false indicates not-secure website (http), true is for secure (https)
	ReadWebPage(src, false, L"www.cnn.com", L"2017/05/02/politics/republican-health-care-bill");

	printf("%s\n", src); 
	//ofstream f("C:\\Users\\elliot\\Documents\\test.html");
	//f << src;

	return 0;
}