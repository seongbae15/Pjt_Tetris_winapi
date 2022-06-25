#include <windows.h>
#include "resource.h"
#include "GameManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("PjtTetris");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	WndClass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	while (true)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			//Work if no message.

		}
	}
	
	GameManager::GetInstance()->DestroyInstance();

	return (int)Message.wParam;
}


//const int iBrickPixelSize = 24;
const int g_iAddWindowWidth = 12;
const int g_iAddWindowHeight = 2;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//나중에 수정할 부분.
	RECT rectWindow;
	int iTransformRot;
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		hWndMain = hWnd;

		srand(GetTickCount());
		//Init GameManager.
		GameManager::GetInstance()->Init(hWndMain, g_hInst);

		//Init Window.
		SIZE sizePixel = GameManager::GetInstance()->GetImgSize();
		SetRect(&rectWindow, 0, 0, (MAP_WIDTH + g_iAddWindowWidth) * sizePixel.cx, (MAP_HEIGHT + g_iAddWindowHeight) * sizePixel.cy);
		AdjustWindowRect(&rectWindow, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, TRUE);
		SetWindowPos(hWndMain, NULL, 0, 0, rectWindow.right - rectWindow.left, rectWindow.bottom - rectWindow.top,SWP_NOMOVE|SWP_NOZORDER);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_GAME_START:
			//Start game.
			if (GAMEOVER != GameManager::GetInstance()->GetGameStatus())
				break;
			GameManager::GetInstance()->GameStart(hWndMain);
			SetTimer(hWndMain, 1, GameManager::GetInstance()->GetIntervalTime(), NULL);
			break;
		case IDM_GAME_PAUSE:
			switch (GameManager::GetInstance()->GetGameStatus())
			{
			case RUNNING:
				GameManager::GetInstance()->ChangeGameStatus(PAUSE);
				KillTimer(hWndMain, 1);
				break;
			case PAUSE:
				GameManager::GetInstance()->ChangeGameStatus(RUNNING);
				SetTimer(hWndMain, 1, GameManager::GetInstance()->GetIntervalTime(), NULL);
				break;
			default:
				break;
			}
			break;
		case IDM_GAME_END:
			DestroyWindow(hWnd);
			break;
		}
		return 0;
	case WM_TIMER:
		GameManager::GetInstance()->Update(hWndMain);
		return 0;
	case WM_KEYDOWN:
		GameManager::GetInstance()->InputGameKey(hWndMain, wParam);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWndMain, &ps);
		GameManager::GetInstance()->Draw(hWndMain, hdc);
		EndPaint(hWndMain, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWndMain, 1);
		//메모리 해제.
		GameManager::GetInstance()->Release();

		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

