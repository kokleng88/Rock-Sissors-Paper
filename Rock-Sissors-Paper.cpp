// Rock-Paper-Sissors Game
// Windowed C++ program for the above approach

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#include <gdiplus.h>
#pragma comment(lib, "gdi32.lib")

#define ID_ROCK 1
#define ID_SISSORS 2
#define ID_PAPER 3
#define ID_STATUS 4
#define ID_TEXT1 5
#define ID_TEXT2 6
#define IDI_ICON1 102

char you;

// Function to implement the game
int game(char you, char computer)
{
	// If both the user and computer
	// has chose the same thing
	if (you == computer)
		return (int) -1;

	// If user's choice is stone and
	// computer's choice is paper
	if (you == 's' && computer == 'p')
		return (int) 0;

	// If user's choice is paper and
	// computer's choice is stone
	else if (you == 'p' && computer == 's') return (int) 1;

	// If user's choice is stone and
	// computer's choice is scissor
	if (you == 's' && computer == 'z')
		return (int) 1;

	// If user's choice is scissor and
	// computer's choice is stone
	else if (you == 'z' && computer == 's')
		return (int) 0;

	// If user's choice is paper and
	// computer's choice is scissor
	if (you == 'p' && computer == 'z')
		return (int) 0;

	// If user's choice is scissor and
	// computer's choice is paper
	else if (you == 'z' && computer == 'p')
		return (int) 1;

    // draw situation by default for any other situation
    return (int) -1;
}

void HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
    return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

const wchar_t *title = L"Rock-Sissors-Paper";
const wchar_t *result_win = L"You Win!\n";
const wchar_t *result_loose = L"You Loose!\n";
const wchar_t *result_draw = L"It's a draw!\n";

HINSTANCE g_hinst = GetModuleHandle(0);
//char textSaved[20];
HWND status;
LPCWSTR winloosedraw;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) 
{
    HWND hwnd;

    MSG  msg ;    
    WNDCLASSW wc = {0};
    wc.lpszClassName = title;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(0, (LPCWSTR) IDI_ICON1);
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);

    g_hinst = hInstance;
  
    RegisterClassW(&wc);

    //if (!RegisterClassW(&wc)) {
    //    MessageBox(NULL, TEXT("Could not register window class"), 
    //              NULL, MB_ICONERROR);
    //    return 0;
    //}

    hwnd = CreateWindowW(wc.lpszClassName, title,
            WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
                  100, 100, 500, 220, 0, 0, hInstance, 0);  

    if (!hwnd) {
        MessageBox(NULL, TEXT("Could not create window"), NULL, MB_ICONERROR);
        return 0;
    }


    HICON hicon = (HICON) LoadImageW(GetModuleHandleW(NULL), MAKEINTRESOURCEW(IDI_ICON1), 
        IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
    SendMessageW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM) hicon);

    // Simple game instructions in status bar
    status = CreateStatusWindow(WS_CHILD | WS_VISIBLE, TEXT("Choose your fist!"), hwnd, 0);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    
    int n, result;
    static char you;
    char computer;

    HWND radiogroup;
	HWND radiobutton_handle_1;
    HWND radiobutton_handle_2;
    HWND radiobutton_handle_3;
    
    HWND textfield_1;
    HWND textfield_2;
  
    HDC hdc;
    PAINTSTRUCT ps;
    static HBITMAP hBitmap;
    static HBITMAP hBitmap2;
    BITMAP bitmap;
    BITMAP bitmap2;
    HDC hdcMem;
    HGDIOBJ oldBitmap;
    HGDIOBJ oldBitmap2;

    HideConsole();
    
    switch(msg) {

        case WM_CREATE:

            textfield_1 = CreateWindowExW(0, L"Static", L"You",
                WS_VISIBLE | WS_CHILD,
                200, 10, 100, 15, hwnd, (HMENU) ID_TEXT1, g_hinst, NULL);
            textfield_2 = CreateWindowExW(0, L"Static", L"Computer",
                WS_VISIBLE | WS_CHILD,
                340, 10, 100, 15, hwnd, (HMENU) ID_TEXT2, g_hinst, NULL);

            InitCommonControls();

            radiogroup = CreateWindowExW(0,L"Button", L"Choose:", 
                  WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                  10, 20, 120, 110, hwnd, NULL, g_hinst, NULL);
                           
            radiobutton_handle_1 = CreateWindowExW(0,L"Button", L"Rock",
                  WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP | WS_TABSTOP,
                  20, 40, 100, 30, hwnd, (HMENU) ID_ROCK , g_hinst, NULL);
            radiobutton_handle_2 = CreateWindowExW(0,L"Button", L"Sissors",
                  WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                  20, 65, 100, 30, hwnd, (HMENU) ID_SISSORS , g_hinst, NULL);
            radiobutton_handle_3 = CreateWindowExW(0,L"Button", L"Paper",
                  WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                  20, 90, 100, 30, hwnd, (HMENU) ID_PAPER , g_hinst, NULL);      

            break;

        case WM_COMMAND:

            // Your turn: choose a fist
            switch (LOWORD(wParam)) {
                
                case ID_ROCK:
                    you = 's';
                    hBitmap = (HBITMAP) LoadImageW(NULL, L".\\pics\\Left_Rock.bmp", 
                    IMAGE_BITMAP, 100, 110, LR_LOADFROMFILE);
                    break;
                case ID_SISSORS:
                    you = 'z';
                    hBitmap = (HBITMAP) LoadImageW(NULL, L".\\pics\\Left_Sissors.bmp", 
                    IMAGE_BITMAP, 100, 110, LR_LOADFROMFILE);
                    break;
                case ID_PAPER:
                    you = 'p';
                    hBitmap = (HBITMAP) LoadImageW(NULL, L".\\pics\\Left_Paper.bmp", 
                    IMAGE_BITMAP, 100, 110, LR_LOADFROMFILE);
                    break;
            }
            if (hBitmap == NULL) {
                MessageBoxW(hwnd, L"Failed to load image", L"Error", MB_OK);
            }

            // Show the fist
            InvalidateRect(hwnd, NULL, TRUE);     

            // start computer turn
            hBitmap2 = NULL;

            srand((unsigned)time(NULL));
            n = rand() % 10;
            //printf("WM_COMMAND: n = %d\n",n);
            if (n < 3) {
		        // s is denoting Stone
		        computer = 's';
                hBitmap2 = (HBITMAP) LoadImageW(NULL, L".\\pics\\Right_Rock.bmp", 
                    IMAGE_BITMAP, 100, 110, LR_LOADFROMFILE);
            }
	        else if (n > 3 && n < 6) {
                // p is denoting Paper
		        computer = 'p';
                hBitmap2 = (HBITMAP) LoadImageW(NULL, L".\\pics\\Right_Paper.bmp", 
                    IMAGE_BITMAP, 100, 110, LR_LOADFROMFILE);
            }
            else {
		        // z is denoting Sissors
		        computer = 'z';
                hBitmap2 = (HBITMAP) LoadImageW(NULL, L".\\pics\\Right_Sissors.bmp", 
                    IMAGE_BITMAP, 100, 110, LR_LOADFROMFILE);
            }

            if (hBitmap2 == NULL) {
                MessageBoxW(hwnd, L"Failed to load image", L"Error", MB_OK); 
            }

            // Show the fist
            InvalidateRect(hwnd, NULL, TRUE);
 
            // Find out who won
            result = game(you, computer);
                
            switch (result) {
                // you loose
                case 0: 
                // printf("You Loose!\n");
                // MessageBoxW(NULL, (LPCWSTR) result_loose, L"Result", MB_OK);
                    winloosedraw = result_loose;
                    break;
                // you win
                case 1: 
                // printf("You Win!\n");
                // MessageBoxW(NULL, (LPCWSTR) result_win, L"Result", MB_OK);
                    winloosedraw = result_win;
                    break;
                // it's a draw
                case -1: 
                // printf("It's a draw!\n");
                // MessageBoxW(NULL, (LPCWSTR) result_draw, L"Result", MB_OK);
                   winloosedraw = result_draw;
                   break;
            }

        case WM_PAINT:
            
            if(hBitmap==NULL || hBitmap2==NULL){
            //  printf("WM_PAINT: hBitmap is NULL or hBitmap2 is NULL\n");
                break;
            }

            hdc = BeginPaint(hwnd, &ps);
            hdcMem = CreateCompatibleDC(hdc);

            // Draw user selection
            oldBitmap = SelectObject(hdcMem, hBitmap);
            GetObject(hBitmap, sizeof(bitmap), &bitmap);
            BitBlt(hdc, 160, 30, bitmap.bmWidth, bitmap.bmHeight, 
            hdcMem, 0, 0, SRCCOPY);
            SelectObject(hdcMem, oldBitmap);

            // Draw computer selection
            oldBitmap2 = SelectObject(hdcMem, hBitmap2);
            GetObject(hBitmap2, sizeof(bitmap2), &bitmap2);
            BitBlt(hdc, 320, 30, bitmap2.bmWidth, bitmap2.bmHeight, 
            hdcMem, 0, 0, SRCCOPY);
            SelectObject(hdcMem, oldBitmap2);

            // Output result
            //MessageBoxW(NULL, winloosedraw, L"Result", MB_OK);
            SendMessage( status, SB_SETTEXT, 0, (LPARAM) winloosedraw);

            DeleteDC(hdcMem);
            EndPaint(hwnd, &ps);
            break;

         case WM_DESTROY:
            PostQuitMessage(0);
            break; 
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}