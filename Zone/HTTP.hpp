#pragma once
#include "pch.h"
#include <winhttp.h>

#pragma comment(lib, "winhttp.lib")

class HTTP
{
	HOOK_PUB_S std::string DownloadString(std::string domain, std::string getreq)
	{
		DWORD dwSize = 0;
		DWORD dwDownloaded = 0;
		LPSTR pszOutBuffer;
		BOOL  bResults = FALSE;
		HINTERNET  hSession = NULL,
			hConnect = NULL,
			hRequest = NULL;

		getreq += "\0";

		wchar_t* l_domain = new wchar_t[domain.length() + 1];
		std::copy(domain.begin(), domain.end(), l_domain);
		l_domain[domain.length()] = 0;

		wchar_t* l_request = new wchar_t[getreq.length() + 1];
		std::copy(getreq.begin(), getreq.end(), l_request);
		l_request[getreq.length()] = 0;

		// Use WinHttpOpen to obtain a session handle.
		hSession = WinHttpOpen(L"SZCS HOOK/2.0", WINHTTP_ACCESS_TYPE_NO_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
		// Specify an HTTP server.
		if (hSession)
			hConnect = WinHttpConnect(hSession, l_domain, INTERNET_DEFAULT_HTTPS_PORT, 0);
		// Create an HTTP request handle.
		if (hConnect)
			hRequest = WinHttpOpenRequest(hConnect, L"GET", l_request, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
		// Send a request.
		if (hRequest)
			bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
		// End the request.
		if (bResults)
			bResults = WinHttpReceiveResponse(hRequest, NULL);
		// Keep checking for data until there is nothing left.
		if (bResults)
		{
			do
			{
				// Check for available data.
				dwSize = 0;
				if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
				{
					continue;
				}

				// Allocate space for the buffer.
				pszOutBuffer = new char[dwSize + 1];
				if (!pszOutBuffer)
				{
					dwSize = 0;
				}
				else
				{
					// Read the data.
					ZeroMemory(pszOutBuffer, dwSize + 1);

					if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
						continue;

					return pszOutBuffer;
				}
			} while (dwSize > 0);
		}

		// Report any errors.
		if (!bResults)
			return "ERR_1";

		// Close any open handles.
		if (hRequest) WinHttpCloseHandle(hRequest);
		if (hConnect) WinHttpCloseHandle(hConnect);
		if (hSession) WinHttpCloseHandle(hSession);

		return "ERR_2";
	}
};