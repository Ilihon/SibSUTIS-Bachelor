#include <windows.h>
#include <string>

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static HWND hBtn;
static HWND hStat;
HDC hdc;
RECT rt;

int WINAPI WinMain(HINSTANCE hInstanse, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	MSG msg;
	BOOL ret;
	WNDCLASS wc;
	LPCSTR lpszAppName = "DialogTwo";
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

	hWnd = CreateWindow(lpszAppName, lpszAppName, WS_OVERLAPPED | WS_SYSMENU, 100, 100, 200, 150, NULL, NULL, hInstanse, NULL);
	hBtn = CreateWindow("button", "Send", WS_CHILD | WS_VISIBLE | WS_BORDER, 5, 70, 175, 35, hWnd, 0, hInstanse, NULL);
	hStat = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 5, 25, 175, 40, hWnd, 0, hInstanse, NULL);
	ShowWindow(hStat, SW_SHOWNORMAL);
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

char s[100];


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		if (lParam == (LPARAM)hBtn) {
			GetWindowText(hStat, s, 100);
			COPYDATASTRUCT data;
			hWnd = FindWindow("DialogOne", "DialogOne");
			data.cbData = strlen(s);
			data.lpData = s;
			SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetFocus(), (LPARAM)&data);
		}
		break;
	case WM_COPYDATA:
		GetClientRect(hWnd, &rt);
		hdc = GetDC(hWnd);
		DrawText(hdc, (char*)(((COPYDATASTRUCT*)lParam)->lpData), ((COPYDATASTRUCT*)lParam)->cbData, &rt, DT_LEFT);
		ReleaseDC(hWnd, hdc);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
