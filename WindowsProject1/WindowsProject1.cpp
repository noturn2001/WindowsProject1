// WindowsProject1.cpp: 응용 프로그램의 진입점을 정의합니다.
//
//숙제 간단히 핑퐁게임 입사각 반사각 사칙연산으로 구현해보기
//타이머 점수 카운팅 
// api로 구현 
//define으로 구현된 삼각함수를 찾아보고 해보기
//공이 화면밖으로 나갔을때 어떤식으로 처리될지
//튕겨나가는거 계산하는것


#include "stdafx.h"

#include <Windows.h>
#include <objIdl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#include "WindowsProject1.h"
#include "resource.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.



// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 기본 메시지 루프입니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
WORD x = 0;
WORD y = 0;
BOOL isRnder = FALSE;
int frame = 0;
BOOL isMove = FALSE;
WORD DIR = 0; // 0 : NONE , 1: RIGHT, 2 : LEFT, 3: DOWN, 4 : UP

void OnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Image image(L"resoucePng.png");
	if (!isMove)
	{
		frame %= 3;
		if(frame == 0)
			graphics.DrawImage(&image, x, y, 0, 0, 34, 40, Gdiplus::UnitPixel);
		else if (frame == 1)
			graphics.DrawImage(&image, x+3, y, 34, 0, 34, 40, Gdiplus::UnitPixel);
		else if (frame == 2)
			graphics.DrawImage(&image, x+4, y, 64, 0, 34, 40, Gdiplus::UnitPixel);

	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_KEYDOWN:
	{
		// 눌렸다는거 인지
		if (wParam == VK_LEFT || wParam == VK_UP || wParam == VK_DOWN || wParam == VK_RIGHT)
		{
			switch (wParam)
			{
			case VK_LEFT:	DIR = 2;	break;
			case VK_RIGHT:	DIR = 1;	break;
			case VK_UP:		DIR = 4;	break;
			case VK_DOWN:	DIR = 3;	break;
			}

			isMove = TRUE;
		}
	}
	break;
	case WM_KEYUP:
	{
		//풀렸다는 것 인지
		DIR = 0;
		isMove = FALSE;
	}
	break;
	case WM_CREATE:
	{
		static HANDLE hTimer = (HANDLE)SetTimer(hWnd, 1, 100, NULL);
	}
	break;
	case WM_TIMER:
	{
		frame += 1;
		switch (DIR)
		{
		case 1:	x += 10; break;
		case 2:	x -= 10; break;
		case 3:	y += 10; break;
		case 4: y -= 10; break;
		}
		InvalidateRect(hWnd, NULL, true);
	}
	break;
		case WM_COMMAND:
		    {
		        int wmId = LOWORD(wParam);
		        // 메뉴 선택을 구문 분석합니다.
		        switch (wmId)
		        {
		        case IDM_ABOUT:
		            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		            break;
		        case IDM_EXIT:
		            DestroyWindow(hWnd);
		            break;
		        default:
		            return DefWindowProc(hWnd, message, wParam, lParam);
		        }
		    }
		    break;
		case WM_PAINT:
		    {

			//펜
		        PAINTSTRUCT ps;
		        HDC hdc = BeginPaint(hWnd, &ps);
		        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

				//HPEN pen=CreatePen(PS_SOLID, 5, RGB(255, 0, 0));//팬을 추가하는 작업 ps_solid는 팬 스타일 5는 선 굵기, rgb는 알지?
				//HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));

				//SelectObject(hdc, pen);//펜을 선택한뒤
				//SelectObject(hdc, brush);//브러쉬를 선택
				//Rectangle(hdc,x,y,x+50,y+50);
				////사각형에 팬을  불러온다. xy 시작하는 좌표 100,100 좌상단에서 시작하는게 포인트, 높이와 너비 200,200


				//DeleteObject(pen); //팬을 모두 사용하고 초기화 하는 작업
				//DeleteObject(brush);

				////HPEN pen2 = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));//팬을 추가하는 작업 ps_solid는 팬 스타일 5는 선 굵기, rgb는 알지?
				////SelectObject(hdc, pen2);//펜을 선택한뒤
				////

				////Rectangle(hdc, 10, 10, 200, 200);
				////RoundRect(hdc, 150,200,50,100,1000,200);//라운드 렉탱글
				////RoundRect(hdc, 400, 100, 500, 200, 1000, 200);//라운드 렉탱글

				////RoundRect(hdc, 500, 500, 200, 200, 60, 60);//라운드 렉탱글

				OnPaint(hdc);
				
				////비트맵 삽입
				//HBITMAP newBitmap, preBitmap;
				//HDC DC = CreateCompatibleDC(hdc);//가상으로 dc를 하나 더 만드는것 모든 이미지를 가져온 뒤 출력할수 있게 만드는 가상dc
				////부분적으로 나오면 한줄씩 출력이 됨으로 한번에 하는걸 api가 지원 그래서 dc를 지원
				//newBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));// 비트맵을 실제로 읽어온다
				//preBitmap = (HBITMAP)SelectObject(DC, (HGDIOBJ)newBitmap);  // 새로만든 dc에 읽어온 비트맵을 장착
				//if (!isMove)
				//{
				//		frame %= 3;
				//	if (frame == 0) {
				//		BitBlt(hdc, x, y, 34, 40, DC, 0, 0, SRCCOPY);
				//	}
				//	else if (frame == 1) {
				//		BitBlt(hdc, x+3, y, 30, 40, DC, 34, 0, SRCCOPY);
				//	}
				//	else if (frame == 2) {
				//		BitBlt(hdc, x+4, y, 32, 40, DC, 64, 0, SRCCOPY);
				//	}
				//}
				//else
				//{
				//	frame %= 9;
				//	switch (frame)
				//		{
				//		case 0:BitBlt(hdc, x , y, 36, 43, DC, 102, 0, SRCCOPY); break;
				//		case 1:BitBlt(hdc, x , y, 31, 43, DC, 137, 0, SRCCOPY); break;
				//		case 2:BitBlt(hdc, x , y, 34, 43, DC, 167, 0, SRCCOPY); break;
				//		case 3:BitBlt(hdc, x , y, 34, 43, DC, 201, 0, SRCCOPY); break;
				//		case 4:BitBlt(hdc, x , y, 32, 43, DC, 234, 0, SRCCOPY); break;
				//		case 5:BitBlt(hdc, x , y, 32, 43, DC, 265, 0, SRCCOPY); break;
				//		case 6:BitBlt(hdc, x , y, 33, 43, DC, 297, 0, SRCCOPY); break;
				//		case 7:BitBlt(hdc, x , y, 36, 43, DC, 330, 0, SRCCOPY); break;
				//		case 8:BitBlt(hdc, x , y, 37, 43, DC, 366, 0, SRCCOPY); break;

				//		}
				//}

				//SelectObject(DC, preBitmap);
				//DeleteObject(newBitmap);
				//DeleteObject(DC);


		        EndPaint(hWnd, &ps);
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

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
