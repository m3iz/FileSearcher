#include <windows.h>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

bool checkstr(string str, string temp) {
	//cout << str<<endl;
	//int len = str.length()-1;
	//if ((str[len] == 't') && (str[len - 1] == 'x') && (str[len - 2] == 't'))return true; //проверка на расширение
	if (str == temp)return true; //проверка на имя файла
	return false;
}

void ff(const TCHAR *curDir, string temp)
{
	Sleep(1);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR cd[MAX_PATH], res[MAX_PATH];
	strcpy_s(cd, MAX_PATH, curDir);
	strcat_s(cd, MAX_PATH, "\\*.*");
	hFind = FindFirstFile(cd, &FindFileData);
	BOOL r = hFind != INVALID_HANDLE_VALUE;
	while (r)
	{
		Sleep(1);
		r = FindNextFile(hFind, &FindFileData);
		if (FindFileData.cFileName[0] != '.')
			try
		{
			string filename = FindFileData.cFileName;
			strcpy_s(cd, MAX_PATH, curDir);
			strcat_s(cd, MAX_PATH, "\\");
			strcat_s(cd, MAX_PATH, FindFileData.cFileName);
			CharToOem(cd, res);
		if (checkstr(filename,temp)) { ///проверяет в функции только конкретное расширение
				cout << "Файл найден! Его путь: " << res << endl;
				if (remove(res) == 0)cout << "File deleted!\n";
				else RemoveDirectory(res);
				r = false;
				break;
			}
			if (FindFileData.dwFileAttributes&&FILE_ATTRIBUTE_DIRECTORY)
				ff(cd,temp);
		}
		catch (...)
		{
			cout << "Can not display file name" << endl;
		}
	}
}


int main()
{
	string temp;
	string temp1;
	setlocale(LC_ALL, "rus");
	//t1.detach();
	cout << "Введите название файла, который нужно найти и удалить\n";
	cin >> temp;
	cout << "Searching file..\n";
	std::thread t1(ff, "C:", temp);
	cout << "Введите название файла, который нужно найти и удалить #2\n";
	cin >> temp1;
	cout << "Searching file #2..\n";
	std::thread t2(ff, "C:", temp1);
	t1.join();
	//t1.join();
	t2.join();
	//ff("C:"); 
	cout << "END";
	system("pause");
	return 0;
}
