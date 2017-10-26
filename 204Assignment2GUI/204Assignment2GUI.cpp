// 204Assignment2GUI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "204Assignment2GUI.h"
#include "Time.h"
#include <string>
#include <exception>
using namespace std;
#define MAX_LOADSTRING 100


bool createTime(HWND);
void updateTime();
void updateAorP(HWND);

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND lblHours;
HWND lblHoursCol; 
HWND lblMins; 
HWND lblMinsCol;
HWND lblSecs;
HWND lblSecsCol;
HWND tbHours; 
HWND tbMins; 
HWND tbSecs;
HWND btnPlus; 
HWND btnMinus; 
HWND btnFormat;
HWND radioAM;
HWND radioPM; 
HWND dropDown; 
Time myTime;
int h, m, s;
// action commands
const int i_text = 1, cmndBtnPlus = 6, cmndBtnMinus = 2, cmndBtnFormat = 3, cmndRadioam = 4, cmndRadiopm = 5;


// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY204ASSIGNMENT2GUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY204ASSIGNMENT2GUI));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY204ASSIGNMENT2GUI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY204ASSIGNMENT2GUI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	

	// Send the CB_SETCURSEL message to display an initial item 
	//  in the selection field  
	SendMessage(dropDown, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);
	
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			string h, m, s;
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

			case cmndBtnPlus:

				if (createTime(hWnd) == true) {
					myTime++;
					updateTime();
				}

				updateAorP(hWnd);
				
				
				break;

			case cmndBtnMinus: 
				if (createTime(hWnd) == true) {
					myTime--;
					updateTime();
				}

				updateAorP(hWnd);
				break; 

			case cmndBtnFormat:
				
				if (createTime(hWnd)) {
					if (myTime._12OR24) {
						myTime.to24();
					}
					else {
						myTime.to12();
					}
					updateTime();
					myTime._12OR24 ^= 1;
					if (myTime._12OR24 == true) {
						SetWindowText(btnFormat, TEXT("24 Hour Format"));
						ShowWindow(radioAM, SW_SHOW);
						ShowWindow(radioPM, SW_SHOW);
					}
					else {
						SetWindowText(btnFormat, TEXT("12 Hour Format"));
						ShowWindow(radioAM, SW_HIDE);
						ShowWindow(radioPM, SW_HIDE);
					}

					updateAorP(hWnd);
				}
				break;

			case cmndRadioam:
				switch (HIWORD(wParam)) {
				case BN_CLICKED:
					if (SendDlgItemMessage(hWnd, cmndRadioam, BM_GETCHECK, 0, 0) == 0) {
						SendDlgItemMessage(hWnd, cmndRadioam, BM_SETCHECK, 1, 0);
						SendDlgItemMessage(hWnd, cmndRadiopm, BM_SETCHECK, 0, 0);
					}
					break;
				}

				myTime.aORp = true;
				break;

			case cmndRadiopm:
				switch (HIWORD(wParam)) {
				case BN_CLICKED:
					if (SendDlgItemMessage(hWnd, cmndRadiopm, BM_GETCHECK, 0, 0) == 0) {
						SendDlgItemMessage(hWnd, cmndRadiopm, BM_SETCHECK, 1, 0);
						SendDlgItemMessage(hWnd, cmndRadioam, BM_SETCHECK, 0, 0);
					}
					break;
				}

				myTime.aORp = false;
				break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;

	case WM_CREATE:

		// GUI LAYOUT
		lblHours = CreateWindow(TEXT("STATIC"), TEXT("Hours"), WS_VISIBLE | WS_CHILD, 10, 10, 60, 20, hWnd, NULL, NULL, NULL);
		lblMins = CreateWindow(TEXT("STATIC"), TEXT("Minutes"), WS_VISIBLE | WS_CHILD, 110, 10, 60, 20, hWnd, NULL, NULL, NULL);
		lblSecs = CreateWindow(TEXT("STATIC"), TEXT("Seconds"), WS_VISIBLE | WS_CHILD, 210, 10, 60, 20, hWnd, NULL, NULL, NULL);
		tbHours = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_BORDER | WS_CHILD | ES_AUTOHSCROLL, 10, 30, 60, 25, hWnd, (HMENU)i_text, NULL, NULL);
		lblHoursCol = CreateWindow(TEXT("STATIC"), TEXT(":"), WS_VISIBLE  | WS_CHILD, 85, 30, 5, 25, hWnd, (HMENU)i_text, NULL, NULL);
		tbMins = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_BORDER | WS_CHILD | ES_AUTOHSCROLL, 110, 30, 60, 25, hWnd, (HMENU)i_text, NULL, NULL);
		lblMinsCol = CreateWindow(TEXT("STATIC"), TEXT(":"), WS_VISIBLE | WS_CHILD, 185, 30, 5, 25, hWnd, (HMENU)i_text, NULL, NULL);
		tbSecs = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_BORDER | WS_CHILD | ES_AUTOHSCROLL, 210, 30, 60, 25, hWnd, (HMENU)i_text, NULL, NULL);
		radioAM = CreateWindowEx(0, TEXT("BUTTON"), TEXT("AM"), WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 280, 30, 45, 10, hWnd, (HMENU)cmndRadioam, NULL, NULL);
		radioPM = CreateWindowEx(0, TEXT("BUTTON"), TEXT("PM"), WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 280, 45, 45, 10, hWnd, (HMENU)cmndRadiopm, NULL, NULL);
		btnPlus = CreateWindow(TEXT("button"), TEXT("+"), WS_VISIBLE | WS_CHILD, 10, 100, 50, 25, hWnd, (HMENU)cmndBtnPlus, NULL, NULL);
		btnMinus = CreateWindow(TEXT("button"), TEXT("-"), WS_VISIBLE | WS_CHILD, 70, 100, 50, 25, hWnd, (HMENU)cmndBtnMinus, NULL, NULL);
		btnFormat = CreateWindow(TEXT("button"), TEXT("24 hour format"), WS_VISIBLE | WS_CHILD, 150, 100, 150, 25, hWnd, (HMENU)cmndBtnFormat, NULL, NULL);

		// Set am as initial state
		if (SendDlgItemMessage(hWnd, cmndRadioam, BM_GETCHECK, 0, 0) == 0) {
			SendDlgItemMessage(hWnd, cmndRadioam, BM_SETCHECK, 1, 0);
		}

		// Create time object
		myTime = Time();
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Updates am or pm raio button with current state
void updateAorP(HWND hWnd) {
	if (myTime.aORp == true) {
		if (SendDlgItemMessage(hWnd, cmndRadioam, BM_GETCHECK, 0, 0) == 0) {
			SendDlgItemMessage(hWnd, cmndRadioam, BM_SETCHECK, 1, 0);
			SendDlgItemMessage(hWnd, cmndRadiopm, BM_SETCHECK, 0, 0);
		}
	}
	else {
		if (SendDlgItemMessage(hWnd, cmndRadiopm, BM_GETCHECK, 0, 0) == 0) {
			SendDlgItemMessage(hWnd, cmndRadiopm, BM_SETCHECK, 1, 0);
			SendDlgItemMessage(hWnd, cmndRadioam, BM_SETCHECK, 0, 0);
		}
	}
}

// Updates the text boxes with current time values
void updateTime() {
	string h, m, s; 
	h = to_string(myTime.getHour());
	m = to_string(myTime.getMin());
	s = to_string(myTime.getSec());
	SetWindowText(tbHours, h.c_str());
	SetWindowText(tbMins, m.c_str());
	SetWindowText(tbSecs, s.c_str());
} 
 
// Takes values from user inputs, does validation and populates time object
bool createTime(HWND hWnd) {
	
	string hString;
	string mString;
	string sString;
	int tbStatus;
	
	try {
		if (GetWindowTextLength(tbHours) == 0) {
			h = 1;
		}
		else {
			hString.resize(GetWindowTextLength(tbHours) + 1, '\0'); // resize the string so iit can contain the text stored in the edit-control.
			tbStatus = GetWindowText(tbHours, LPSTR(hString.c_str()), GetWindowTextLength(tbHours) + 1); // Getting the data the user type
			if (tbStatus != 0) {
				h = stoi(hString);
			}
			else {
				throw exception("Invalid Input!");
			}
		}

		if (GetWindowTextLength(tbMins) == 0) {
			m = 0; 
		}
		else {
			mString.resize(GetWindowTextLength(tbMins) + 1, '\0'); // resize the string so iit can contain the text stored in the edit-control.
			tbStatus = GetWindowText(tbMins, LPSTR(mString.c_str()), GetWindowTextLength(tbMins) + 1); // Getting the data the user typed
			if (tbStatus != 0) {
				m = stoi(mString);
			}
			else {
				throw exception("Invalid Input!");
			}
		}

		if (GetWindowTextLength(tbSecs) == 0) {
			s = 0; 
		}
		else {
			// resize the string so iit can contain the text stored in the edit-control.
			sString.resize(GetWindowTextLength(tbSecs) + 1, '\0'); 
			tbStatus = GetWindowText(tbSecs, LPSTR(sString.c_str()), GetWindowTextLength(tbSecs) + 1); // Getting the data the user typed
			if (tbStatus != 0) {
				s = stoi(sString);
			}
			else {
				throw exception("Invalid Input!");
			}
		}

		myTime.setTime(h,m,s);
		
		if (myTime.getMin() >= 60) { throw exception("Minutes has to be less than 60"); }

		if (myTime.getSec() >= 60) { throw exception("Seconds has to be less than 60"); }

		if (myTime._12OR24 == true && ( myTime.getHour() > 12 || myTime.getHour() < 1)) {
			throw exception("12 Hour Format : Hour has to be between 1-12 inclusive");
		} else if (myTime._12OR24 == false && ( myTime.getHour() > 23 || myTime.getHour() < 0)) {
			throw exception("24 Hour Format : Hour has to be between 0-23 inclusive");
		}

	} catch (exception e) {
		::MessageBox(hWnd, TEXT(e.what()), TEXT("Error!"), MB_OK);
		return false;
	}

	return true;
}

// Message handler for about box.
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
