// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <cmath>
#include <string>

#define MAX_LOADSTRING 100
#define TMR_1 1
#define TMR_2 309
#define TMR_3 999

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;

// buttons
HWND hwndButton;
int speed = 1;
const int Length =100;
int which_sq;
int which_sq2;
static int how_many_sq = 6;
// sent data
bool info = false;
struct coordinates {
		float x;
		float y;
		float Xx;
		float Yy;
		bool block;
};
coordinates first{0,0,400,500};
coordinates sec{ 0, 200,400,300};
coordinates third{100, 300,500,200};

coordinates square[6][4] = { 
						{100,0,500,500,true,
						 150,0,550,500,true,
						 150,50,550,450,true,
						 100,50,500,450,true},
						
						 {200,0,600,500,NULL,
						 250,0,650,500,NULL,
						 250,50,650,450,NULL,
						 200,50,600,450,NULL},

						  {260,0,660,500,NULL,
						 310,0,710,500,NULL,
						 310,50,710,450,NULL,
						 260,50,660,450,NULL},
						  
						{110,50,510,450,NULL,
						 160,50,560,450,NULL,
						 160,100,560,400,NULL,
						 110,100,510,400,NULL},

						 {20,0,420,500,NULL,
						 70,0,470,500,NULL,
						 70,50,470,450,NULL,
						 20,50,420,450,NULL},

						 {260,50,660,450,NULL,
						 310,50,710,450,NULL,
						 310,100,710,400,NULL,
						 260,100,660,400,NULL},

						 
};
 int mid_Ax=400;
 int mid_Ay=500;
 float midX, midY;
 int side;
std::vector<Point> data;
//RECT drawArea1 = { 0, 0, 150, 200 };
//RECT drawArea2 = { 50, 400, 650, 422};

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);


void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen2(Color(255, 700, 0, 255));

	
	graphics.DrawLine(&pen, 0, 500, 1000, 500);
	graphics.DrawLine(&pen2, first.Xx, first.Yy, sec.Xx, sec.Yy);
	graphics.DrawLine(&pen2, sec.Xx, sec.Yy, third.Xx,third.Yy);
	
	
	for (int i = 0; i < how_many_sq; i++)
	{
		graphics.DrawLine(&pen2, square[i][0].Xx, square[i][0].Yy, square[i][1].Xx, square[i][1].Yy);
		graphics.DrawLine(&pen2, square[i][1].Xx, square[i][1].Yy, square[i][2].Xx, square[i][2].Yy);
		graphics.DrawLine(&pen2, square[i][2].Xx, square[i][2].Yy, square[i][3].Xx, square[i][3].Yy);
		graphics.DrawLine(&pen2, square[i][3].Xx, square[i][3].Yy, square[i][0].Xx, square[i][0].Yy);
	}
}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	if (drawArea==NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}

bool square_touchingX(coordinates& G,coordinates tab[])
{
	if (G.x <= tab[2].x && G.x >= tab[3].x)
		return 1;
	else if (G.x <= tab[1].x && G.x >= tab[2].x)
		return 1;
	else if (G.x <= tab[0].x && G.x >= tab[1].x)
		return 1;
	else if (G.x <= tab[1].x && G.x >= tab[2].x)
		return 1;
	else return 0;
}

void move(coordinates &G,bool b)
{
	
	
	if (b == 0)
	{
		int buff = G.x;
		float x = G.x * cos( speed*PI / 180) - G.y * sin(speed * PI / 180);
		float y = G.y * cos(speed * PI / 180) + buff * sin(speed * PI / 180);
		G.x = x;
		G.y = y;
	}
	
	else
	{
		int buff = G.x;
		float x = G.x * cos(-speed * PI / 180) - G.y * sin(-speed * PI / 180);
		float y = G.y * cos(-speed * PI / 180) + buff * sin(-speed * PI / 180);
		G.x = x;
		G.y = y;
	}
	G.Xx = G.x + mid_Ax;
	G.Yy = mid_Ay -G.y;
}

void move2(coordinates& G, bool b)
{
	
		G.x = G.x - sec.x;
		G.y = G.y-sec.y;
	
	if (b == 0)
	{
		int buff = G.x;
		float x = G.x * cos(speed * PI / 180) - G.y * sin(speed * PI / 180);
		float y = G.y * cos(speed * PI / 180) + buff * sin(speed * PI / 180);
		G.x = x;
		G.y = y;
	}

	else
	{
		int buff = G.x;
		float x = G.x * cos(-speed * PI / 180) - G.y * sin(-speed * PI / 180);
		float y = G.y * cos(-speed * PI / 180) + buff * sin(-speed * PI / 180);
		G.x = x;
		G.y = y;
	}
	
	G.x = G.x + sec.x;
	G.y = sec.y + G.y;
	
	G.Xx = G.x + mid_Ax;
	G.Yy = mid_Ay - G.y;
	
}

void move3(coordinates& G, bool b)
{

	G.x = G.x - midX;
	G.y = G.y - midY;

	if (b == 0)
	{
		int buff = G.x;
		float x = G.x * cos(PI / 180) - G.y * sin(PI / 180);
		float y = G.y * cos(PI / 180) + buff * sin(PI / 180);
		G.x = x;
		G.y = y;
	}

	else
	{
		int buff = G.x;
		float x = G.x * cos(-PI / 180) - G.y * sin(-PI / 180);
		float y = G.y * cos(-PI / 180) + buff * sin(-PI / 180);
		G.x = x;
		G.y = y;
	}

	G.x = G.x + midX;
	G.y = midY + G.y;

	G.Xx = G.x + mid_Ax;
	G.Yy = mid_Ay - G.y;

} 

bool check_touch(coordinates& G, coordinates tab[], int w)
{
	int bcountx = 2;
	int bcounty = 2;
	float MAX_x=tab[0].Xx, MAX_y=tab[0].Yy;
	for (int i = 1;i<4;i++ )
	{
		if (tab[i].Xx > MAX_x)
		{
			MAX_x = tab[i].Xx;
			if(i==1)
				bcountx=3;
			else if (i==2)
				bcountx = 0;
			else
				bcountx = 1;
		}
		if (tab[i].Yy > MAX_y)
		{
			MAX_y = tab[i].Yy;
			if (i == 1)
				bcounty = 3;
			else if (i ==2)
				bcounty = 0;
			else
				bcounty = 1;

		}
		
	}
		//if ((G.Yy - tab[i - 1].Yy) * (tab[i].Xx - tab[i - 1].Xx) - (tab[i].Yy - tab[i - 1].Yy) * (G.Xx - tab[i - 1].Xx) == 0)
	if (G.Xx <= MAX_x && G.Xx >= tab[bcountx].Xx && G.Yy <= MAX_y && G.Yy >= tab[bcounty].Yy)
	{
		if (tab[0].block == 0)
			return 1;
	}
	return 0;
}

int fall_info(coordinates tab[],int main)
{
	for (int s = 0; s < how_many_sq; s++)
	{
		if (s == main)
			continue;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0;j < 4; j++)
			{
				if ((int(tab[i].y) == int(square[s][j].y)) && square_touchingX(tab[i], square[s]) == 1)
				{
					which_sq2 = s;
					return 1;
				}
			}
			
		}
	}
	if (info == 0 && int(tab[0].y) != 0 && int(tab[1].y) != 0 && int(tab[2].y) != 0 && int(tab[3].y) != 0)
		return 0;
	else return 2;
}

bool fall_info2(coordinates tab[], int main)
{
	int ver=-1,ver2;
	
	for (int i = 0; i < 4; i++)
	{
		if (int(tab[i].y) == 0)
			ver = i;
	}
	if (ver == -1)
	{
		for (int s = 0; s < how_many_sq; s++)
		{
			if (s == main)
				continue;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if ((int(tab[i].y) == int(square[s][j].y)) && square_touchingX(tab[i], square[s]) == 1)
						ver = i;
				}

			}
		}
	}
		 if (ver == 0)
		{
			if (tab[1].y < tab[3].y)
			{ 
				ver2 = 1;
				side = 1;
			}
			else
			{
				ver2 = 3;
				side = 0;
			}
		}
		else if (ver == 1)
		{
			if (tab[0].y < tab[2].y)
			{
				ver2 = 0;
				side = 0;
			}
			else
			{
				ver2 = 2;
				side = 1;
			}
		}
		else if (ver == 2)
		{
			if (tab[1].y < tab[3].y)
			{
				ver2 = 1;
				side = 0;
			}
			else
			{
				ver2 = 3;
				side = 1;
			}
		}
		else if (ver == 3)
		{
			if (tab[2].y < tab[0].y)
			{
				ver2 = 2;
				side = 0;
			}
			else
			{
				ver2 = 0;
				side = 1;
			}
		}
		 midX = tab[ver].x;
		 midY = tab[ver].y;
		 if (int(tab[ver2].y) == 0)
			 return 1;
		 for (int s = 0; s < how_many_sq; s++)
		 {
			 if (s == which_sq)
				 continue;
			 for (int i = 0; i < 4; i++)
			 {
				 for (int j = 0; j < 4; j++)
				 {
					 if (int(tab[ver2].y) == int(square[s][j].y))
						 return 1;
				 }

			 }
		 }
		 return 0;
}

void fall(coordinates tab[])
{
	for (int i = 0; i < 4; i++)
	{
		tab[i].y -= 1;
		tab[i].Yy += 1;
	}
}

void change_block(int wh,int b )
{
	for (int i = 0; i < 4; i++)
	{
		square[wh][i].block =b ;
	}
}

void unlock(coordinates tab[],int main)
{
	for (int s = 0; s < how_many_sq; s++)
	{
		if (s == main)
			continue;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if ((int(tab[i].y) == int(square[s][j].y)) && square_touchingX(tab[i], square[s]) == 1)
				{
					change_block(s, 0);
				}
			}

		}
	}
}

void inputData()
{	
	data.push_back(Point(0, 0));
	for (int i = 1; i < 100; i++){
		data.push_back(Point(2*i+1, 200 * rand()/RAND_MAX));
	}
}


int OnCreate(HWND window)
{
	inputData();
	return 0;
}


// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
	HWND hWnd;


	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	// create button and store the handle                                                       
	


	// create button and store the handle                                                       
/*
	hwndButton = CreateWindow(TEXT("button"), TEXT("Timer ON"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		300, 155, 100, 30, hWnd, (HMENU)ID_RBUTTON1, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Timer OFF"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		300, 200, 100, 30, hWnd, (HMENU)ID_RBUTTON2, GetModuleHandle(NULL), NULL);
		*/
	OnCreate(hWnd);

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
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON1 :
			wchar_t buffer[256];
			wsprintfW(buffer, L"%d",int(square[0][2].Xx) );
			MessageBox(hWnd, buffer, L"Caption", MB_OKCANCEL);
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON2 :
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_RBUTTON1:
			SetTimer(hWnd, TMR_1, 25, 0);
			break;
		case ID_RBUTTON2:
			KillTimer(hWnd, TMR_1);
			break;
		
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
	{
		switch (wParam) {
		case VK_LEFT:
		{
			move(third, 0);
			if (info == 1)
			{
				for (int i = 0; i < 4; i++)
					move(square[which_sq][i], 0);
			}
			
			move(sec, 0);

	

			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		}
		case VK_RIGHT:
		{
			move(third, 1);
			if (info == 1)
			{
				for(int i=0;i<4;i++)
				move(square[which_sq][i], 1);
				
			}
			move(sec, 1);



			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		}
		case 'A':
		{
			move2(third, 0);
			if (info == 1)
			{
				for (int i = 0; i < 4; i++)
					move2(square[which_sq][i], 0);
			}
			


			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		}
		case 'D':
		{
			move2(third, 1);
			if (info == 1)
			{
				for (int i = 0; i < 4; i++)
					move2(square[which_sq][i], 1);
			}
			



			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		}
		}
		break;
	}
	case WM_CHAR:
	{
		switch (wParam) {
		case _T('f'):
		case _T('F'):
		{
			for (int w = 0; w < how_many_sq; w++)
			{
				if (check_touch(third, square[w], w))
				{
					info = !info;
					which_sq = w;
					unlock(square[which_sq], which_sq);
				}
			if (fall_info(square[which_sq],which_sq)==0)
				SetTimer(hWnd, TMR_1, 1, 0);
			}
			
			break;
		}
		case _T('q'):
		case _T('Q'):
		{
			speed = 1;
			break;
		}
		case _T('e'):
		case _T('E'):
		{
			speed = 2;
			break;
		}
		}
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here (not depend on timer, buttons)
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			fall(square[which_sq]);
			if (fall_info(square[which_sq], which_sq) != 0)
			{
				if (fall_info(square[which_sq], which_sq) == 1)
				{
					change_block(which_sq2,1);
				}
				KillTimer(hWnd, TMR_1);
				if(fall_info2(square[which_sq], which_sq)==0)
					SetTimer(hWnd, TMR_2, 1, 0);
			}
			repaintWindow(hWnd, hdc, ps,NULL);
			break;
		case TMR_2:
				//force window to repaint
				for (int i = 0; i < 4; i++)
					move3(square[which_sq][i], side);
				if (fall_info2(square[which_sq], which_sq) == 1)
					KillTimer(hWnd, TMR_2);
				repaintWindow(hWnd, hdc, ps, NULL);
			break;
		
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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
