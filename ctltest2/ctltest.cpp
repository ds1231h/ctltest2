/*******************************************************************
����EasyEdit
�ļ���EasyEdit.c
���ܣ���׼�ؼ���ʾ�����ı��༭��
********************************************************************/
#include <windows.h>
#include <windowsx.h>

BOOL InitWindow (HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK MainWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	MSG msg;

	if (!InitWindow (hInstance, iCmdShow))
		return FALSE;

	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}

	return msg.wParam;
}

static BOOL InitWindow (HINSTANCE hInstance, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("EasyEdit");
	HWND hwnd;   
	WNDCLASS wc; 

	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon (hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	if (!RegisterClass (&wc))
	{
		MessageBox (NULL, TEXT ("ע�ᴰ����ʧ�ܣ�"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow (szAppName, 
		TEXT ("�ؼ�ѧϰ"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, 
		NULL,
		hInstance, 
		NULL); 

	if( !hwnd ) return FALSE;

	ShowWindow ( hwnd, iCmdShow );
	UpdateWindow ( hwnd );
	return TRUE;
}

LRESULT CALLBACK MainWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND  hWndEdit, hWndstatic, hWndlistbox, hWndcombobox, hWndbutton, hWndsrcollbar;

	switch (message)
	{
	case WM_CREATE:
		hWndstatic=CreateWindow (
			TEXT ("static"),			        //��������
			TEXT("�ؼ�ѧϰ����"),  //�ؼ����ı�			                    //�ޱ���
			WS_CHILD| WS_VISIBLE| WS_BORDER,	//�༭�ؼ����,
			30, 60, 150, 30,	
			hWnd,		                        //�����ھ��
			(HMENU)2,		                        //�༭�ؼ��Ӵ��ڱ�ʶ
			(HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);

		hWndbutton = CreateWindow(
			TEXT("button"),  
			TEXT("�������"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,// ��ƽ��ʽ
			30 , 100 , 150 , 50,
			hWnd, (HMENU)3, 
			(HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);

		hWndlistbox = CreateWindow(
			TEXT("listbox"),  
			TEXT("�������"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_STANDARD,
			30 , 160 , 150 , 50,
			hWnd, (HMENU)4 , 
			(HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);

		SendMessage(hWndlistbox, LB_ADDSTRING, 0, (LPARAM)TEXT("list str1"));
		SendMessage(hWndlistbox, LB_ADDSTRING, 0, (LPARAM)TEXT("list str2"));
		SendMessage(hWndlistbox, LB_ADDSTRING, 0, (LPARAM)TEXT("list str3"));
		SendMessage(hWndlistbox, LB_ADDSTRING, 0, (LPARAM)TEXT("list str4"));

		hWndcombobox = CreateWindow(TEXT("COMBOBOX"), NULL, WS_CHILD|WS_VISIBLE|WS_VSCROLL|
			CBS_AUTOHSCROLL|CBS_DROPDOWNLIST |CBS_SIMPLE, 30, 220, 150, 50, hWnd, (HMENU)5, NULL, NULL);

		SendMessage(hWndcombobox, CB_ADDSTRING, 0, (LPARAM)TEXT("comb str1"));
		SendMessage(hWndcombobox, CB_ADDSTRING, 0, (LPARAM)TEXT("comb str2"));
		SendMessage(hWndcombobox, CB_ADDSTRING, 0, (LPARAM)TEXT("comb str3"));
		SendMessage(hWndcombobox, CB_ADDSTRING, 0, (LPARAM)TEXT("comb str4"));
		SendMessage(hWndcombobox, CB_SETCURSEL, 1, 0);



		return 0;

	case WM_SETFOCUS:
		SetFocus (hWndEdit);
		return 0;

	case WM_SIZE:
		MoveWindow (hWndEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		return 0;

	case WM_COMMAND:        	// ��Ӧ�༭�ؼ�֪ͨ��Ϣ
		if (lParam)
		{
			if ((LOWORD (wParam) == 1) &&
				(HIWORD(wParam) == EN_ERRSPACE || HIWORD (wParam) == EN_MAXTEXT))
				MessageBox (hWnd,TEXT ("�༭�ؼ��ڴ����"), 
				TEXT ("�ؼ�����"), MB_OK|MB_ICONSTOP);	

			HWND hwndTmp;
			if(lParam != 1) // ���ǲ˵�
			{
				switch (LOWORD(wParam))
				{
				case (HMENU)3:
					hwndTmp = GetDlgItem(hWnd, 2);
					SetWindowText(hwndTmp, TEXT("�ؼ�ѧ����"));
					MessageBox(hWnd, TEXT("Text Changed!"), TEXT("info"), MB_OK);
					break;
				}
			}
		}
		return 0;

	case WM_DESTROY: 
		PostQuitMessage (0);
		return 0;
	}

	return DefWindowProc (hWnd, message, wParam, lParam);

} //���� MainWndProc ����

