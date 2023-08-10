#include <windows.h>
#include <string>
#include <vector>

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#if !(defined(_UNICODE) | defined(UNICODE))
#error no Unicode!
#endif

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static HWND hBtn[16];
static HWND hStat, hStat1;
string s;

void Split(int *sign, double *num, int *cs, int *cn)
{
	string allSign = "+-*/";
	for (int i = 0; i < s.size(); ++i)
	{
		double c = 0;
		int fl = 0;
		while (s[i] >= '0' && s[i] <= '9')
			fl = 1, c = c * 10 + (s[i++] - '0');
		if (fl)
			num[(*cn)++] = c;
		fl = allSign.find(s[i]);
		if (fl != -1)
			sign[(*cs)++] = fl;
	}
}

double changeValue(double a, double b, int sign)
{
	double result;
	if (sign == 0)
		result = a + b;
	else if (sign == 1)
		result = a - b;
	else if (sign == 2)
		result = a * b;
	else if (sign == 3)
		result = a / b;
	return result;
}

void GetDesktopResolution(int &horizontal, int &vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

int WINAPI WinMain(HINSTANCE hInstanse, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	BOOL ret;
	WNDCLASS wc;
	LPCSTR lpszAppName = "Calc";
	wc.lpszClassName = lpszAppName;
	wc.hInstance = hInstanse;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = 0;
	wc.lpszMenuName = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	if (!RegisterClass(&wc)) 
		return 0;
	int horizontal = 0;
	int vertical = 0;
	int winHeight = 218, winWidth = 340;
	GetDesktopResolution(horizontal, vertical);
	hWnd = CreateWindow(lpszAppName, lpszAppName, WS_OVERLAPPED | WS_SYSMENU, horizontal / 2 - winHeight / 2, vertical / 2 - winWidth / 2, winHeight, winWidth, NULL, NULL, hInstanse, NULL);

	char sybms[4][5]{
		"123/",
		"456*",
		"789-",
		"C0=+"};
	int nums[4][4] =
		{
			{1, 2, 3, 11},
			{4, 5, 6, 12},
			{7, 8, 9, 13},
			{10, 0, 15, 14},
		};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			string str;
			str.push_back(sybms[i][j]);
			hBtn[nums[i][j]] = CreateWindow("button", str.c_str(), WS_CHILD | WS_VISIBLE, 50 * j + 5, 50 * i + 105, 50, 50, hWnd, 0, hInstanse, NULL);
		}
	}

	hStat = CreateWindow("static", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 5, 2, 198, 40, hWnd, 0, hInstanse, NULL);
	hStat1 = CreateWindow("static", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 5, 44, 198, 54, hWnd, 0, hInstanse, NULL);
	ShowWindow(hStat, SW_SHOWNORMAL);
	ShowWindow(hStat1, SW_SHOWNORMAL);

	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		if (lParam == (LPARAM)hBtn[0])
			s += '0';
		if (lParam == (LPARAM)hBtn[1])
			s += '1';
		if (lParam == (LPARAM)hBtn[2])
			s += '2';
		if (lParam == (LPARAM)hBtn[3])
			s += '3';
		if (lParam == (LPARAM)hBtn[4])
			s += '4';
		if (lParam == (LPARAM)hBtn[5])
			s += '5';
		if (lParam == (LPARAM)hBtn[6])
			s += '6';
		if (lParam == (LPARAM)hBtn[7])
			s += '7';
		if (lParam == (LPARAM)hBtn[8])
			s += '8';
		if (lParam == (LPARAM)hBtn[9])
			s += '9';
		if (lParam == (LPARAM)hBtn[10]){
			if (s.size() == 0){
				s.clear();
			}
			if (s.size() != 0)
				s.erase(s.size() - 1);
		}
		if (lParam == (LPARAM)hBtn[11])
			s += "/";
		if (lParam == (LPARAM)hBtn[12])
			s += "*";
		if (lParam == (LPARAM)hBtn[13])
			s += "-";
		if (lParam == (LPARAM)hBtn[14])
			s += "+";
		if(lParam != (LPARAM)hBtn[15] && s.size() >= 0)
			SetWindowText(hStat, s.c_str());
		if (lParam == (LPARAM)hBtn[15] && s.size() != 0)
		{
			s += ' ';
			int sign[127];
			double num[127];
			int countSign = 0, countNum = 0;

			Split(sign, num, &countSign, &countNum);
			while (countNum > 1)
			{
				int numOper = 0;
				for (int i = 0; i < countSign; ++i)
					if (sign[i] > 1)
					{
						numOper = i;
						break;
					}
				num[numOper] = changeValue(num[numOper],
										   num[numOper + 1], sign[numOper]);
				for (int i = numOper + 1; i < countNum; i++)
					num[i] = num[i + 1];
				for (int i = numOper; i < countSign; i++)
					sign[i] = sign[i + 1];
				countNum--, countSign--;
			}
			s.clear();
			string ans;
			if (num[0] == (int)num[0])
			{
				ans = to_string((int)num[0]);
			}
			else
			{
				ans = to_string(num[0]);
				int size = ans.size() - 1;
				for (int i = size; i > 0; i--)
				{
					if (ans[i] == '0')
						s.erase(ans.size() - 1, 1);
					else
						break;
				}
			}
			SetWindowText(hStat1, ans.c_str());
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
