// Шумицкая_3.cpp : Определяет точку входа для приложения.
//
#include <windows.h>
#include "framework.h"
#include "Шумицкая_3.h"
#include "math.h"

#define TIMER_1 1
#define TIMER_2 2


#define IDB_BITMAP_2 146
#define IDS_KITTENS 104


#define Stop1 32775
#define Resume1 32776
#define Programm1 32773
#define Exit1 32774

#define IDR_MENU2 138

#define Increase 32796
#define reduce 32797
#define common 32798
#define increase_speed 32801
#define reduce_speed 32802
#define Exit2 32803
#define Font 32790


#define IDI_ICON1 142
#define IDI_ICON2 143


#define cursor1 144
#define cursor2 145
// --- Прототип оконной функции главного окна
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK PopupWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst;

TCHAR ClassName1[] = "Windows Class";
TCHAR AppTitle1[] = "Главное окно группа АСУ-19 \n Шумицкая";

TCHAR ClassName2[] = "PopupWindow Class";
TCHAR AppTitle2[] = " Временное окно";








// --- Главная функция приложения WinMain
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	HWND hMainWnd, hWndPopup, hWndChild;


	HBRUSH FIRST_BRUSH, SECOND_BRUSH, THIRD_BRUSH;
	FIRST_BRUSH = CreateSolidBrush(RGB(255, 255, 255));
	SECOND_BRUSH = CreateSolidBrush(RGB(255, 255, 255));
	THIRD_BRUSH = CreateSolidBrush(RGB(255, 255, 255));


	UINT TimerId1, TimerId2;

	WNDCLASS wc_main, wc_popup, wchild;
	MSG msg;
	RECT main_rect;



	int m_width, m_height;
	m_width = GetSystemMetrics(SM_CXFULLSCREEN);
	m_height = GetSystemMetrics(SM_CYFULLSCREEN);


	HMENU hMenu1 = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
	// Главное окно

	if ((hMainWnd = FindWindow(ClassName1, NULL)) != NULL)
	{

		// Если прилож. было запущено ранее, активизировать
		// и выдвинуть на передний план его главное окно
		int msgID1 = MessageBox(hMainWnd, "Приложение уже запущено хотите продолжить?", "Информация", MB_OKCANCEL);
		switch (msgID1)
		{
		case IDOK:

			if (IsIconic(hMainWnd))
			{
				ShowWindow(hMainWnd, SW_RESTORE);
			}
			break;

		case IDCANCEL:
			PostQuitMessage(0);
			DestroyWindow(hMainWnd);
			break;
		}
		
		return FALSE;
	}



	hInst = hInstance; // Сохран. дескриптора экз. прилож.
	
	/*HCURSOR	hCursor = LoadCursor(hInst, MAKEINTRESOURCE(cursor1));*/
	ZeroMemory(&wc_main, sizeof(wc_main)); // Очистка полей структуры
	// Заполнение полей стр-ры WNDCLASS
	wc_main.lpszClassName = ClassName1; // Имя класса окон
	//Адрес оконной ф-ции
	wc_main.lpfnWndProc = (WNDPROC)MainWndProc;
	wc_main.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // Стиль класса окон
	wc_main.hInstance = hInstance; // Экземпляр приложения
	// Пиктограмма для окон
	wc_main.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	// Курсор мыши для окон
	wc_main.hCursor = LoadCursor(hInst, MAKEINTRESOURCE(cursor1));
	// Кисть для окон
	wc_main.hbrBackground = FIRST_BRUSH;
	wc_main.lpszMenuName = NULL; // Ресурс меню окон
	wc_main.cbClsExtra = 0; // Дополнительная память класса
	wc_main.cbWndExtra = 0; // Дополнительная память окна
	// Pегистрация класса окна.
	RegisterClass(&wc_main);
	// Создание главного окна приложения.
	hMainWnd = CreateWindow(
		ClassName1, // Имя класса окон
		AppTitle1, // Заголовок окна
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, // Стиль окна
		0, // X-координата
		0, // Y-координата
		m_width, // Ширина окна
		m_height, // Высота окна
		NULL, // Дескриптор окна-родителя
		NULL, // Дескриптор меню окна
		hInst, // Дескриптор экз. приложения
		NULL); // Дополнительная информация




	if (!hMainWnd)
	{
		// Окно не создано, выдается сообщение.
		MessageBox(NULL, "Window create error", AppTitle1, MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	// Отображение окна и обновление его
	ShowWindow(hMainWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hMainWnd);

	TimerId1 = SetTimer(hMainWnd, TIMER_1, 400, NULL);


	SetMenu(hMainWnd, hMenu1);


	hInst = hInstance; // Сохран. дескриптора экз. прилож.

	HMENU hMenu2 = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU2));

	
	ZeroMemory(&wc_popup, sizeof(wc_popup)); // Очистка полей структуры
	// Заполнение полей стр-ры WNDCLASS
	wc_popup.lpszClassName = ClassName2; // Имя класса окон
	//Адрес оконной ф-ции
	wc_popup.lpfnWndProc = (WNDPROC)PopupWndProc;
	wc_popup.style = CS_HREDRAW | CS_VREDRAW; // Стиль класса окон
	wc_popup.hInstance = hInstance; // Экземпляр приложения
	// Пиктограмма для окон
	wc_popup.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON2));
	// Курсор мыши для окон
	wc_popup.hCursor = LoadCursor(hInst, MAKEINTRESOURCE(cursor2));
	// Кисть для окон
	wc_popup.hbrBackground = SECOND_BRUSH;
	wc_popup.lpszMenuName = NULL; // Ресурс меню окон
	wc_popup.cbClsExtra = 0; // Дополнительная память класса
	wc_popup.cbWndExtra = 0; // Дополнительная память окна
	// Pегистрация класса окна.
	RegisterClass(&wc_popup);



	hWndPopup = CreateWindow(ClassName2,
		AppTitle2, WS_POPUPWINDOW |
		WS_CAPTION | WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX | WS_BORDER, 0, 0, 600, 600,
		hMainWnd, NULL, hInstance, NULL);

	if (hWndPopup == NULL)
	{ // Уничтожение главного окна при неудаче
		DestroyWindow(hMainWnd);
		return FALSE;
	}

	ShowWindow(hWndPopup, SW_RESTORE);

	UpdateWindow(hWndPopup);


	TimerId2 = SetTimer(hWndPopup, TIMER_2, 700, NULL);

	SetMenu(hWndPopup, hMenu2);



	// Запуск цикла обработки очереди сообщений.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Преобразов. сообщений клавиатуры в символьные
		TranslateMessage(&msg);
		// Отправление сообщения оконной функции
		DispatchMessage(&msg);
	}
	return msg.wParam; // Завершение работы приложения
}


// --- Оконная функция главного окна


LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT MR;
	static HBITMAP hBitmap, hOldBitmap;
	static BITMAP bm;
	HDC hDC, BitmapDC;

	static int  width, height;
	int iVerSize, iHorSize;
	int cx, cy;

	static double i = 6.28, x, y;
	double R = 180;

	GetClientRect(hWnd,&MR);
	
	switch (uMsg)
	{


	case WM_CREATE:



		hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_2));
		GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
		cx = GetSystemMetrics(SM_CXSCREEN);
		cy = GetSystemMetrics(SM_CYSCREEN);
		x = ((MR.right - MR.left) / 2 - bm.bmWidth / 2 + 180);
		y = ((MR.bottom - MR.top) / 2 - bm.bmHeight / 2);


		break;
	case WM_SIZE:

		width = LOWORD(lParam);
		height = HIWORD(lParam);

		break;


	case WM_TIMER:

		i -= 0.1744;
		x = R * cos(0 + i) + ((MR.right - MR.left) / 2 - bm.bmWidth / 2);
		y = R * sin(0 + i) + ((MR.bottom - MR.top) / 2 - bm.bmHeight / 2);

		if (i == 0)
		{
			i = 6.28;
		}

		InvalidateRect(hWnd, NULL, true);
		break;



	case WM_PAINT:


		hDC = BeginPaint(hWnd, &ps);

		BitmapDC = CreateCompatibleDC(hDC);
		hOldBitmap = (HBITMAP)SelectObject(BitmapDC, hBitmap);
		iHorSize = GetDeviceCaps(BitmapDC, HORZSIZE);
		iVerSize = GetDeviceCaps(BitmapDC, VERTSIZE);
		BitBlt(hDC, x, y, iHorSize, iVerSize, BitmapDC, 0, 0, SRCCOPY);
		SelectObject(BitmapDC, hOldBitmap);
		DeleteDC(BitmapDC);
		EndPaint(hWnd, &ps);


		break;

	case WM_COMMAND:
	{
		UINT idItem = LOWORD(wParam);
		switch (idItem)
		{
		case Stop1:
			KillTimer(hWnd, TIMER_1);
			break;
		case Resume1:
			SetTimer(hWnd, TIMER_1, 400, NULL);
			break;
		case Programm1:
			MessageBox(hWnd, "Данная программа предназначена для вывода ресурсов в главное и врменное окно", "О программе", MB_OK);
			break;
		case Exit1:
			DestroyWindow(hWnd);
			break;

		}
		break;
	}

	case WM_DESTROY:

		PostQuitMessage(0);
		KillTimer(hWnd, 1);

		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	
	}
	return 0;
}



// --- Оконная функция временное окно 
LRESULT CALLBACK PopupWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hDC;
	static int len;
	int cx, cy;
	static int  width, height;
	static RECT PR;
	static PAINTSTRUCT ps;
	static CHOOSEFONT cf;
	static LOGFONT lf;
	static int s, f;
	static int dx = 1;
	static int dy = 1;
	static bool up = true;
	char szBuffer[20];

	
	static 	double time = 700;
	static DWORD rgbCurrent;
	static DWORD rgbPrev;

	static	HFONT oldhfont, hfont, hfontPrev;

	switch (uMsg)
	{



	case WM_CREATE:
		cx = GetSystemMetrics(SM_CXSCREEN);
		cy = GetSystemMetrics(SM_CYSCREEN);

		hDC = GetDC(hWnd);

		/*создаём экземпляр LOGFONT*/
		lf.lfCharSet = DEFAULT_CHARSET; //значение по умолчанию
		lf.lfPitchAndFamily = DEFAULT_PITCH; //значения по умолчанию
		strcpy_s(lf.lfFaceName, "Times New Roman"); //копируем в строку название шрифта
		lf.lfHeight = 14; //высота
		lf.lfWidth = 14; //ширина
		lf.lfWeight = 40; //толщина
		lf.lfEscapement = 0; //шрифт без поворота
		
		GetClientRect(hWnd, &PR);
		static int x = PR.left, y = (PR.bottom - lf.lfHeight)-20;
		
		break;

	case WM_SIZE:
		width = LOWORD(lParam);
		height = HIWORD(lParam);


		break;

	case WM_PAINT:
	{

		
		

		LoadString(hInst,IDS_KITTENS , szBuffer, 20);

		len = strlen(szBuffer);

		hDC = BeginPaint(hWnd, &ps);
		rgbPrev = SetTextColor(hDC, rgbCurrent);
		hfont = CreateFontIndirect(&lf);
		SelectObject(hDC, hfont);

		TextOut(hDC,x, y, szBuffer, len);

		EndPaint(hWnd, &ps);
		SelectObject(hDC, hfont);
		DeleteObject(hfont);


	}
	break;

	case WM_TIMER:

		if (up == true)
		{
			x = x + 10;
			y = y - 10;
			if (y <= 0||x>=PR.right-lf.lfWidth*len)
			{
				up = false;
			}
		}
		else {
			x = x - 10;
			y = y + 10;
			if (x <= 0)
			{
				up = true;
			}
		}
		InvalidateRect(hWnd, NULL, true);
		break;

	case WM_COMMAND:
	{
		UINT idItem = LOWORD(wParam);
		switch (idItem)
		{


		case Increase:

			lf.lfHeight = lf.lfHeight * 2;
			lf.lfWidth *= 2;

			InvalidateRect(hWnd, NULL, true);
			break;
			
		case reduce:

			lf.lfHeight = lf.lfHeight / 2;
			lf.lfWidth /= 2;

			InvalidateRect(hWnd, NULL, true);
			break;

		case common:
			lf.lfHeight = 14; //высота
			lf.lfWidth = 14; 
			break;

		case increase_speed:
			time = time / 2;
			KillTimer(hWnd, TIMER_2);
			SetTimer(hWnd, TIMER_2, time, NULL);
			InvalidateRect(hWnd, NULL, true);
			break;

		case reduce_speed:
			time = time * 2;
			KillTimer(hWnd, TIMER_2);
			SetTimer(hWnd, TIMER_2, time, NULL);
			InvalidateRect(hWnd, NULL, true);
			break;

		case Exit2:
			DestroyWindow(hWnd);
			break;
		case Font:

				
				
				
				ZeroMemory(&cf, sizeof(CHOOSEFONT));
				cf.lStructSize = sizeof(CHOOSEFONT);
				cf.hwndOwner = hWnd;
				cf.lpLogFont = &lf;
				cf.rgbColors = rgbCurrent;

				cf.Flags = CF_SCREENFONTS | CF_EFFECTS;

				if (ChooseFont(&cf) == TRUE)
				{
					hfont = CreateFontIndirect(cf.lpLogFont);
					hfontPrev = (HFONT)SelectObject(hDC, hfont);
					rgbCurrent = cf.rgbColors;
					rgbPrev = SetTextColor(hDC, rgbCurrent);

					
				}
				InvalidateRect(hWnd, NULL, true);
				break;
		}
	}
	break;

	case WM_DESTROY:

			KillTimer(hWnd, TIMER_2);
		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}






