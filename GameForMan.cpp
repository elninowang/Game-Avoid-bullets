// GameForMan.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "GameForMan.h"
#include "ddraw.h"
#include "mmsystem.h"
#include "object.h"
#include "Var.h"
#include "draw.h"
#include "DirectX.h"
#include "function.h"
#include "Frenquency.h"
#define MAX_LOADSTRING 100

// 全局变量：
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
BOOL notDone=FALSE;


// 此代码模块中包含的函数的前向声明：
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	//检测性能计时器
	LONGLONG cur_time;
	DWORD time_count;
	LONGLONG perf_cnt;
	BOOL pert_flag=FALSE;
	LONGLONG next_time=0;
	LONGLONG last_time=0;
	LONGLONG begin_time=0;
	double time_elapsed;
	double time_scale;

	MessageBox(NULL,TEXT("是男人，你就坚持20秒"),TEXT("准备开始"),NULL);
	if( QueryPerformanceFrequency( (LARGE_INTEGER *) &perf_cnt ) )
	{
		pert_flag = TRUE;
		time_count = perf_cnt/30;
		QueryPerformanceCounter( (LARGE_INTEGER *) &next_time );
		time_scale = 1.0/perf_cnt;
	}
	else
	{
		next_time = timeGetTime();
		time_scale = 0.001;
		time_count = 33;
	}
	begin_time=last_time = next_time;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GAMEFORMAN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化：
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_GAMEFORMAN);

	// 主消息循环：
	while( notDone == TRUE )
	{
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE )) 
		{
			if ( msg.message == WM_QUIT ) 
				notDone = FALSE;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if( pert_flag )
			{
				QueryPerformanceCounter( (LARGE_INTEGER *) &cur_time );
			}
			else 
				cur_time = timeGetTime();
			
			if( cur_time>next_time )
			{
				RealTime = (cur_time-begin_time)*time_scale;
				time_elapsed = (cur_time-last_time)*time_scale;
				last_time = cur_time;
				if( !TimeFunction() )
					pert_flag?QueryPerformanceCounter( (LARGE_INTEGER *) &begin_time ):begin_time=timeGetTime();
				next_time = cur_time + time_count;
			}
		}
	}
	return (int) msg.wParam;
}



//
//  函数：MyRegisterClass()
//
//  目的：注册窗口类。
//
//  注释：
//
//    仅当希望在已添加到 Windows 95 的
//    “RegisterClassEx”函数之前此代码与 Win32 系统兼容时，
//    才需要此函数及其用法。调用此函数
//    十分重要，这样应用程序就可以获得关联的
//   “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_GAMEFORMAN);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_GAMEFORMAN;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   函数：InitInstance(HANDLE, int)
//
//   目的：保存实例句柄并创建主窗口
//
//   注释：
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
	   200, 100, cxSurface+8, cySurface+46, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数：WndProc(HWND, unsigned, WORD, LONG)
//
//  目的：处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
	case WM_CREATE:
		RealTime = 0;
		notDone = TRUE;
		if( !InitDirectX(hWnd ) )
		{
			MessageBox(hWnd, TEXT("DirectX接口失败"), TEXT("ERROR"), NULL);
			CleanUp();
			SendMessage( hWnd, WM_DESTROY, 0, 0 );
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// 分析菜单选择：
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_RESTART:
			Restart();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_SIZE:
		cxClient = LOWORD( lParam );
		cyClient = HIWORD( lParam );
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetMapMode(hdc,MM_TEXT);
		// TODO: 在此添加任意绘图代码...
		DrawDirectX(hWnd);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_LEFT:
			pl.UpVLeft();
			//pl.Next();
			//DrawDirectX( hWnd );
			break;
		case VK_RIGHT:
			pl.UpVRight();
			//pl.Next();
			//DrawDirectX( hWnd );
			break;
		case VK_UP:
			pl.UpVUp();
			//pl.Next();
			//DrawDirectX( hWnd );
			break;
		case VK_DOWN:
			pl.UpVDown();
			//pl.Next();
			//DrawDirectX( hWnd );
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
