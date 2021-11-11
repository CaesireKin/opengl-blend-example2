#include "assist.h"

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR szCmdLine,int iCmdShow)
{
	MSG msg;
	HWND hwnd;
	WNDCLASSEX wndex;

	wndex.cbSize = sizeof(WNDCLASSEX);
	wndex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndex.cbClsExtra = 0;
	wndex.cbWndExtra = 0;
	wndex.lpfnWndProc = WndProc;
	wndex.hInstance = hInstance;
	wndex.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndex.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndex.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wndex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndex.lpszClassName = TEXT("GLView");
	wndex.lpszMenuName = NULL;

	if(!RegisterClassEx(&wndex))
	{
		MessageBox(NULL,TEXT("Application Initiallizing Failed , Please Contact Your Manual For Advanced Help"),TEXT("Initial Fatol"),MB_OK);
		return 0;
	}

	hwnd = CreateWindow(TEXT("GLView"),TEXT("BlendTest2"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);

	ShowWindow(hwnd,SW_MAXIMIZE);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,NULL,NULL,NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	static HGLRC hRC;
	static HDC hDC;

	switch(message)
	{
	case WM_CREATE:

		hDC = GetDC(hwnd);

		SetDCPixelFormat(hDC);

		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC,hRC);

		Configure();

		break;
	case WM_SIZE:

		Resize(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));

		break;
	case WM_COMMAND:

		switch(wParam)
		{
		case VK_ESCAPE:

			break;
		}

		break;
	case WM_PAINT:

		Render();
		SwapBuffers(hDC);

		break;
	case WM_DESTROY:

		wglMakeCurrent(hDC,hRC);
		wglDeleteContext(hRC);

		break;
	default:
		return DefWindowProc(hwnd,message,wParam,lParam);
	}

	return 0;
}