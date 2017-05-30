// GameForMan.cpp : ����Ӧ�ó������ڵ㡣
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

// ȫ�ֱ�����
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
BOOL notDone=FALSE;


// �˴���ģ���а����ĺ�����ǰ��������
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	//������ܼ�ʱ��
	LONGLONG cur_time;
	DWORD time_count;
	LONGLONG perf_cnt;
	BOOL pert_flag=FALSE;
	LONGLONG next_time=0;
	LONGLONG last_time=0;
	LONGLONG begin_time=0;
	double time_elapsed;
	double time_scale;

	MessageBox(NULL,TEXT("�����ˣ���ͼ��20��"),TEXT("׼����ʼ"),NULL);
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

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GAMEFORMAN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ����
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_GAMEFORMAN);

	// ����Ϣѭ����
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
//  ������MyRegisterClass()
//
//  Ŀ�ģ�ע�ᴰ���ࡣ
//
//  ע�ͣ�
//
//    ����ϣ��������ӵ� Windows 95 ��
//    ��RegisterClassEx������֮ǰ�˴����� Win32 ϵͳ����ʱ��
//    ����Ҫ�˺��������÷������ô˺���
//    ʮ����Ҫ������Ӧ�ó���Ϳ��Ի�ù�����
//   ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
//   ������InitInstance(HANDLE, int)
//
//   Ŀ�ģ�����ʵ�����������������
//
//   ע�ͣ�
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ������WndProc(HWND, unsigned, WORD, LONG)
//
//  Ŀ�ģ����������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
			MessageBox(hWnd, TEXT("DirectX�ӿ�ʧ��"), TEXT("ERROR"), NULL);
			CleanUp();
			SendMessage( hWnd, WM_DESTROY, 0, 0 );
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// �����˵�ѡ��
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
		// TODO: �ڴ���������ͼ����...
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

// �����ڡ������Ϣ�������
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
