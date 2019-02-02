#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <cstdio>

using namespace std;

int op = 0;
int API = 0;
char newfile[100];
bool checkstr(string str, string temp, int wtd=0) {
	//cout << str<<endl;
	//int len = str.length()-1;
	//if ((str[len] == 't') && (str[len - 1] == 'x') && (str[len - 2] == 't'))return true; //проверка на расширение
	if (str == temp)return true; //проверка на имя файла
	return false;
}

bool ff(const TCHAR *curDir, string temp)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR cd[MAX_PATH], res[MAX_PATH]; 
	char filen[MAX_PATH];
	strcpy_s(cd, MAX_PATH, curDir);
	strcat_s(cd, MAX_PATH, "\\*.*");
	hFind = FindFirstFile(cd, &FindFileData);
	BOOL r = hFind != INVALID_HANDLE_VALUE;
	while (r)
	{
		r = FindNextFile(hFind, &FindFileData);
		if (FindFileData.cFileName[0] != '.')
			try
		{
			string filename = FindFileData.cFileName;
			strcpy_s(cd, MAX_PATH, curDir);
			strcat_s(cd, MAX_PATH, "\\");
			strcpy_s(filen, MAX_PATH, cd);
			strcat_s(cd, MAX_PATH, FindFileData.cFileName);
			CharToOem(cd, res);
			if (checkstr(filename, temp)) { ///проверяет в функции только конкретное расширение
				cout << "Файл найден! Его путь: " << res << endl;

				if (op == 1) {
					if (remove(res) == 0)cout << "File deleted!\n";
					else RemoveDirectory(res);
				}
				else if (op==2) {
					char path[100] = "";
					if (API == 1) strcpy_s(path, "/select, ");
					strcat_s(path, res);
					ShellExecute(NULL, "open", "explorer.exe", path, NULL, SW_SHOWNORMAL);
				}
				else if (op==3) {
					strcat_s(filen,newfile);
					rename(res, filen);
				}
				return true;
			}
			if (FindFileData.dwFileAttributes&&FILE_ATTRIBUTE_DIRECTORY)
				ff(cd, temp);
		}
		catch (...)
		{
			cout << "Can not display file name" << endl;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "rus");

	string temp;
	cout << "Введите название файла\n";
	cin >> temp;

	cout << "Введите номер операции (1-удалить; 2-найти или открыть; 3-переименовать; )\n";
	cin >> op;
	if (op == 2) { cout << "Введите 1, если хотите выделить файл без его запуска\n"; cin >> API; }
	if (op == 3){
		cout << "Введите новое название\n";
		cin >> newfile;
}
	cout << "Searching file..\n";
	if (ff("C:", temp))cout << "Succsess\n";
	else { cout << "ERROR\n"; }
	system("pause");
	return 0;
}

