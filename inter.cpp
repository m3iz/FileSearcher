#include <windows.h> 
#include <wininet.h> 
#pragma comment(lib,"wininet") 
#include <stdlib.h> 
#include<fstream> 
#include<iostream> 
#include <string> 
using namespace std;


void getHTML(LPCTSTR url)
{
	cout << url << endl;
	bool ok = false;
	HINTERNET hInternet =
		::InternetOpen(
			TEXT("WinInet Test"),
			INTERNET_OPEN_TYPE_PRECONFIG,
			NULL, NULL,
			0);

	if (hInternet != NULL) {
		// открываем HTTP сессию 
		HINTERNET hConnect =
			::InternetConnect(
				hInternet,
				url,
				INTERNET_DEFAULT_HTTP_PORT,
				NULL, NULL,
				INTERNET_SERVICE_HTTP,
				0,
				1u);
		if (hConnect != NULL) {
			// открываем запрос 
			HINTERNET hRequest =
				::HttpOpenRequest(
					hConnect,
					TEXT("POST"),//поменять на пост так GET 
					TEXT("stats/Unique/Mann%20Co.%20Supply%20Crate%20Key/Tradable/Craftable"),//здесь написать запрос(страницу) или оставить пустое место 
					NULL,
					NULL,
					0,
					INTERNET_FLAG_KEEP_CONNECTION,
					1);
			if (hRequest != NULL) {
				BOOL bSend = ::HttpSendRequest(hRequest, NULL, 0, NULL, 0); //bSend : false 
				if (bSend) {
					ofstream fnews("news.html", ios::out | ios::binary);
					if (fnews.is_open()) for (;;) {
						char szData[1024];
						DWORD dwBytesRead;
						BOOL bRead =
							::InternetReadFile(
								hRequest,
								szData, sizeof(szData) - 1,
								&dwBytesRead);

						if (bRead == FALSE || dwBytesRead == 0)
							break;
						szData[dwBytesRead] = 0;
						fnews << szData;
						cout << szData;
						cout << "asd" << endl;
						ok = true;
					}
					else { cout << "Error occupied. File error\n"; }
				}
				else { cout << "Error occupied (0x0001d)\n"; }
				::InternetCloseHandle(hRequest);
			}
			else { cout << "Error occupied (0x0001c)\n"; }
			::InternetCloseHandle(hConnect);
		}
		else { cout << "Error occupied (0x0001b)\n"; }
		::InternetCloseHandle(hInternet);
	}
	else { cout << "Error occupied (0x0001a)\n"; }
	if (ok)
		system("start news.html");
}
int main(int argc, char* argv[])
{
	getHTML(TEXT("backpack.tf"));
	getchar();
	return 0;
}
