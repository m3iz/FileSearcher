#include <Windows.h> 
#include <stdlib.h> 
#include <iostream> 
#include <math.h> 

int main()
{
	Sleep(5000);
	float x;
	//HDC hDC = GetDC(GetConsoleWindow()); 
	HDC hDC = GetDC(FindWindow(NULL, "ыы"));//если не нашлось окно, рисует медленно и поверх всех окон
	std::cout << hDC;
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hDC, Pen);
	MoveToEx(hDC, 10, 85, NULL);
	LineTo(hDC, 200, 85);
	MoveToEx(hDC, 100, 0, NULL);
	LineTo(hDC, 100, 170);
	for (x = -80.0f; x <= 80.0f; x += 0.01f) // O(100,85) - center 
	{
		MoveToEx(hDC, 10 * x + 100, -10 * sin(x) + 85, NULL);//10 - scale 
		LineTo(hDC, 10 * x + 100, -10 * sin(x) + 85);
	}
	system("pause");
}
