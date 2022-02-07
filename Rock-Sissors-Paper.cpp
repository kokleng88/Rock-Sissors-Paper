// Rock-Paper-Sissors Game
// Windowed C++ program for the above approach

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#include <gdiplus.h>
#pragma comment(lib, "gdi32.lib")

#define ID_ROCK 1
#define ID_SISSORS 2
#define ID_PAPER 3

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

const wchar_t *result_win = L"You Win!\n";
const wchar_t *result_loose = L"You Loose!\n";
const wchar_t *result_draw = L"It's a draw!\n";
HINSTANCE g_hinst = GetModuleHandle(0);
HBITMAP hBitmap;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR lpCmdLine, int nCmdShow) {

    HWND hwnd;

    MSG  msg ;    
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"Rock-Sissors-Paper";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);

    g_hinst = hInstance;
  
    RegisterClassW(&wc);
    hwnd = CreateWindowW(wc.lpszClassName, L"Rock-Sissors-Paper",
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE | SS_BITMAP,
                  100, 100, 500, 220, 0, 0, hInstance, 0);  
    
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, 
    WPARAM wParam, LPARAM lParam) {
    
    int n, i, result;
    char you, computer;

    HWND radiogroup;
	HWND radiobutton_handle_1;
    HWND radiobutton_handle_2;
    HWND radiobutton_handle_3;

    HDC hdc;
    PAINTSTRUCT ps;
    static HBITMAP hBitmap;
    static HBITMAP hBitmap2;
    BITMAP bitmap;
    BITMAP bitmap2;
    HDC hdcMem;
    HGDIOBJ oldBitmap;
    HGDIOBJ oldBitmap2;

    //HMENU ghMenu;
    //POINT point;

    //const char* status = "Show status of statusbar\n";

    HideConsole();
    
    switch(msg) {

        case WM_CREATE:

            InitCommonControls();

            radiogroup = CreateWindowExW(0,L"Button", L"Choose:", 
                  WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                  10, 10, 120, 110, hwnd, NULL, g_hinst, NULL);
                           
            radiobutton_handle_1 = CreateWindowExW(0,L"Button", L"Rock",
                  WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP | WS_TABSTOP,
                  20, 30, 100, 30, hwnd, (HMENU) ID_ROCK , g_hinst, NULL);
            radiobutton_handle_2 = CreateWindowExW(0,L"Button", L"Sissors",
                  WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                  20, 55, 100, 30, hwnd, (HMENU) ID_SISSORS , g_hinst, NULL);
            radiobutton_handle_3 = CreateWindowExW(0,L"Button", L"Paper",
                  WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                  20, 80, 100, 30, hwnd, (HMENU) ID_PAPER , g_hinst, NULL);      
            break;

        case WM_COMMAND:

            // when user selection is already done
            if(hBitmap!=NULL) {
                EnableWindow(radiogroup, FALSE); //disable radio group;
                EnableWindow(radiobutton_handle_1, FALSE); // disable radio selection
                EnableWindow(radiobutton_handle_2, FALSE); // disable radio selection
                EnableWindow(radiobutton_handle_3, FALSE); // disable radio selection           
                InvalidateRect(hwnd, NULL, TRUE);  // show the images
                break;
            }

            // when user selected 1st time
            if (HIWORD(wParam) == BN_CLICKED) {
                switch (LOWORD(wParam)) {
                
                    case ID_ROCK:
                        you = 's';
                        hBitmap = (HBITMAP) LoadImageW(NULL, L".\\pics\\Left_Rock.bmp", 
                        IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

                        if (hBitmap == NULL) {
                            MessageBoxW(hwnd, L"Failed to load image", L"Error", MB_OK); 
                        }
                        break;
                    case ID_SISSORS:
                        you = 'z';
                        hBitmap = (HBITMAP) LoadImageW(NULL, L".\\pics\\Left_Sissors.bmp", 
                        IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

                        if (hBitmap == NULL) {
                            MessageBoxW(hwnd, L"Failed to load image", L"Error", MB_OK); 
                        }
                        break;
                    case ID_PAPER:
                        you = 'p';
                        hBitmap = (HBITMAP) LoadImageW(NULL, L".\\pics\\Left_Paper.bmp", 
                        IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

                        if (hBitmap == NULL) {
                            MessageBoxW(hwnd, L"Failed to load image", L"Error", MB_OK); 
                        }
                        break; 
                }
                InvalidateRect(hwnd, NULL, TRUE);  // show the images    
            }

            // start computer turn
            if (hBitmap!=NULL && hBitmap2==NULL) {
                //printf("WM_COMMAND: you = %c\n",you);
                //printf("WM_COMMAND: computer = %c\n",computer);
                //printf("WM_COMMAND: hBitmap2 is null\n");

                // Computer Selection
                srand(time(NULL));
                n = rand() % 100;
                //printf("WM_COMMAND: n = %d\n",n);
                if (n < 33) {

		            // s is denoting Stone
		            computer = 's';
                    hBitmap2 = (HBITMAP) LoadImageW(NULL, L".\\pics\\Right_Rock.bmp", 
                        IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
                }
	            else if (n > 33 && n < 66) {

		            // p is denoting Paper
		            computer = 'p';
                    hBitmap2 = (HBITMAP) LoadImageW(NULL, L".\\pics\\Right_Paper.bmp", 
                        IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
                }
                else {

		            // z is denoting Sissors
		            computer = 'z';
                    hBitmap2 = (HBITMAP) LoadImageW(NULL, L".\\pics\\Right_Sissors.bmp", 
                        IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
                }

                if (hBitmap2 == NULL) {
                    MessageBoxW(hwnd, L"Failed to load image", L"Error", MB_OK); 
                }
                //InvalidateRect(hwnd, NULL, TRUE);
                //printf("WM_COMMAND: computer = %c\n",computer);
                //printf("WM_COMMAND: hBitmap2 is set\n");
                            
                if(hBitmap2!=NULL){
                    // start playing
                    //printf("WM_COMMAND: hBitmap2 != NULL\n");
                
                    result = game(you, computer);
                
                    switch (result) {
                        case 0: // you loose
                        //    printf("You Loose!\n");
                            MessageBoxW(NULL, (LPCWSTR) result_loose, L"Result", MB_OK);
                            break;
                        case 1: // you win
                        //    printf("You Win!\n");
                            MessageBoxW(NULL, (LPCWSTR) result_win, L"Result", MB_OK);
                            break;
                        case -1: // draw
                        //    printf("It's a draw!\n");
                            MessageBoxW(NULL, (LPCWSTR) result_draw, L"Result", MB_OK);
                            break;
                    }
                }
            }
            break;
            
        case WM_PAINT:
            
            if(hBitmap==NULL || hBitmap2==NULL){
            //  printf("WM_PAINT: hBitmap is NULL or hBitmap2 is NULL\n");
                break;
            }

            //printf("WM_PAINT: hBitmap != NULL\n");

            hdc = BeginPaint(hwnd, &ps);
            hdcMem = CreateCompatibleDC(hdc);

            // Draw user selection
            oldBitmap = SelectObject(hdcMem, hBitmap);
            GetObject(hBitmap, sizeof(bitmap), &bitmap);
            BitBlt(hdc, 160, 20, bitmap.bmWidth, bitmap.bmHeight, 
            hdcMem, 0, 0, SRCCOPY);
            SelectObject(hdcMem, oldBitmap);

            // Draw computer selection
            oldBitmap2 = SelectObject(hdcMem, hBitmap2);
            GetObject(hBitmap2, sizeof(bitmap2), &bitmap2);
            BitBlt(hdc, 320, 20, bitmap2.bmWidth, bitmap2.bmHeight, hdcMem
            , 0, 0, SRCCOPY);
            SelectObject(hdcMem, oldBitmap2);

            DeleteDC(hdcMem);
            EndPaint(hwnd, &ps);  
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break; 
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}