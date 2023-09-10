#include "manage.h"
#include "tank.h"
#include "collide.h"
//#include "map.h"

//HBITMAP hBitmap;
//int width = WindowWidth;
//int height = WindowHeight;
AllObjects All_Ob;

int mapIndex[rows][cols] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2,
						   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2,
						   2, 3, 3, 3, 2, 3, 1, 3, 2, 3, 3, 3, 2, 3, 2, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2,
						   2, 3, 3, 3, 2, 3, 1, 3, 2, 3, 3, 3, 2, 3, 2, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2,
						   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2,
						   1, 2, 2, 2, 2, 3, 2, 3, 2, 2, 2, 2, 1, 3, 2, 2,
						   2, 3, 2, 3, 2, 3, 3, 3, 2, 3, 2, 3, 2, 3, 2, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2,
						   2, 3, 3, 3, 2, 2, 2, 2, 2, 3, 3, 3, 2, 3, 2, 2,
						   2, 3, 2, 3, 2, 3, 3, 3, 2, 3, 2, 3, 2, 3, 2, 2,
						   2, 2, 2, 2, 2, 3, 0, 3, 2, 2, 2, 2, 2, 3, 2, 2
};


Draw::Draw(HBITMAP hBit, HWND hw)
{
	hBitmap = hBit;
	hwnd = hw;
}
Draw::Draw(HBITMAP hBit, HWND hw, HDC  hdc, int width, int height)
{
	hBitmap = hBit;
	hwnd = hw;
	NowWidth = width;
	NowHeight = height;
	this->hdc = hdc;
}
Draw::Draw(const Draw& draw)
{
	hBitmap = draw.hBitmap;
	hwnd = draw.hwnd;
	NowWidth = draw.NowWidth;
	NowHeight = draw.NowHeight;
	hdc = draw.hdc;
	ImageWidth = draw.ImageWidth;
	ImageHeight = draw.ImageHeight;
}

BOOL CALLBACK Draw::EnumChildProc(HWND hwndChild, LPARAM lParam)
{
	if (IsWindow(hwndChild) && (GetWindowLong(hwndChild, GWL_STYLE) & BS_PUSHBUTTON)) {
		// �ҵ�һ����ť�����Ӽ���
		ButtonCount++;
	}
	return TRUE;
}

void Draw::DrawBackground()
{
	//�����ڴ��豸������
	hdc2 = CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdc2, hBitmap);

	// ���ư�ť
	cout << "���ư�ť" << endl;
	for (int i = 1; i <= ButtonCount; i++)
	{
		int buttonx = NowWidth / 2 - 50;
		int buttony = NowHeight * 0.8 - 15 + (30 * (i - 1));
		SetWindowPos(GetDlgItem(hwnd, i), NULL, buttonx, buttony, 100, 30, SWP_SHOWWINDOW);
	}

	//��ȡͼ��
	if (GetImage())
	{
		cout << "��ȡͼ��ɹ�" << endl;
		StretchBlt(hdc, 0, 0, NowWidth, NowHeight, hdc2, 0, 0, ImageWidth, ImageHeight, SRCCOPY);
	}
	//����ͼ��
	//������Դ
	SelectObject(hdc2, hOldBitmap);
	DeleteDC(hdc2);
}

void Draw::InitBackGround()
{
	//InvalidateRect(hwnd, NULL, TRUE);
	//���ذ�ť
	for (int i = 1; i <= ButtonCount; i++)
	{
		ShowWindow(GetDlgItem(hwnd, i), SW_HIDE);
	}
	//HDC hdc = GetDC(hwnd);
	/*PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);*/
	//hdc2 = CreateCompatibleDC(hdc);
	// ������ɫ��ˢ
	HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	// ���ô��ڱ�����ˢ
	RECT rect = { 0, 0, NowWidth, NowHeight };
	FillRect(hdc2, &rect, hBlackBrush);
	//Rectangle(hdcmem, 0, 0, NowWidth, NowHeight);
	//BitBlt(hdc, 0, 0, NowWidth, NowHeight, hdc2, 0, 0, SRCCOPY);
	//swap(hdc, hdcmem);
	//swap(hdc, hdc2);
	//ReleaseDC(hwnd, hdc);
	//EndPaint(hwnd, &ps);

	//���ر����Ļ���ʹ����������
	/*PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);
	HBITMAP BackGround = (HBITMAP)LoadImage(NULL, L"image/dark.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, BackGround);
	if (GetImage(BackGround))
	{
		StretchBlt(hdc, 0, 0, NowWidth, NowHeight, hdcMem, 0, 0, ImageWidth, ImageHeight, SRCCOPY);
	}
	SelectObject(hdcMem, hOldBitmap);
	DeleteDC(hdcMem);
	EndPaint(hwnd, &ps);*/
}

void Draw::ClearTank()
{

}

void Draw::DrawTank(TANK*tank)
{
	//hdc = GetDC(hwnd);
	/*HBITMAP Friend = (HBITMAP)LoadImage(NULL, L"image/mytank_66.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HBITMAP Enemy = (HBITMAP)LoadImage(NULL, L"image/ememytank_66.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);*/
	double xlength = (double)NowWidth / (rows);
	double ylength = (double)NowHeight / (cols+1);
	//TANK player(rows - 1, 4, up);
	tank->Update(xlength, ylength);
	tank->DRAWONE(hdc2);
	//ReleaseDC(hwnd, hdc);
}

void Draw::InitWorld() {
	//GetClientRect(hh, &worldre);
	HBITMAP map[4];
	PAINTSTRUCT ps;
	for (int i = 0; i < 4; i++)
	{
		int filenamesize = swprintf(NULL, 0, L"image/myobject%d_66.bmp", i);
		WCHAR* filename = new WCHAR[filenamesize+1];
		//filename = L"image/myobject%d_66.bmp" % (i);
		wsprintf(filename, L"image/myobject%d_66.bmp", i);//��ʽ��д��map0/1/2/3.bmp
		map[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//����ͼƬ�ĺ���
		delete[]filename;
	}
	double xlength = (double)NowWidth/(cols);
	double ylength = (double)NowHeight/(rows+1);
	double x, y;
	Object ob;
	cout << "���봴��������" << endl;
	for (int rowNum = 0; rowNum < rows; rowNum++) {
		//MessageBox(hwnd,L"S",L"S",NULL);
		for (int colNum = 0; colNum < cols; colNum++) {
			x = (colNum) * xlength;//��ͼ���ں�����			
			y = (rowNum) * ylength;//��ͼ����������	
			int thing = mapIndex[rowNum][colNum];
			if (thing == wall) {
				ob.life = 4;
 			}
			else if (thing == food) {
				ob.life = 1;
			}
			else if (thing == eagle) {
				ob.life = 1;
			}
			Point point(rowNum, colNum);
			Rect rect(x,y,xlength,ylength);
			ob.rect = rect;
			ob.point = point;
			All_Ob.Insert(ob);
			if(thing!=sail)
				Rectangle(hdc2, x, y, x + xlength, y + ylength);
				//Drawob(&ob, hdc2, map[thing], xlength, ylength);
		}
	}
}

void Draw::ChangeWorld() {
	//GetClientRect(hh, &worldre);
	HBITMAP map[4];
	PAINTSTRUCT ps;
	for (int i = 0; i < 4; i++)
	{
		int filenamesize = swprintf(NULL, 0, L"image/myobject%d_66.bmp", i);
		WCHAR* filename = new WCHAR[filenamesize + 1];
		//filename = L"image/myobject%d_66.bmp" % (i);
		wsprintf(filename, L"image/myobject%d_66.bmp", i);//��ʽ��д��map0/1/2/3.bmp
		map[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//����ͼƬ�ĺ���
		delete[]filename;
	}
	double xlength = (double)NowWidth / (rows);
	double ylength = (double)NowHeight / (cols+1);
	double x, y;
	Object ob;
	cout << "������Ϸ������" << endl;
	for (int rowNum = 0; rowNum < rows; rowNum++) {
		//MessageBox(hwnd,L"S",L"S",NULL);
		for (int colNum = 0; colNum < cols; colNum++) {
			x = (colNum)*xlength;//��ͼ���ں�����			
			y = (rowNum)*ylength;//��ͼ����������	
			int thing = mapIndex[rowNum][colNum];
			if (thing == wall) {
				ob.life = 4;
			}
			else if (thing == food) {
				ob.life = 1;
			}
			else if (thing == eagle) {
				ob.life = 1;
			}
			Point point(rowNum, colNum);
			Rect rect(x, y, xlength, ylength);
			ob.rect = rect;
			ob.point = point;
			if (thing != sail)
				Drawob(&ob, hdc2, map[thing], xlength, ylength);
		}
	}
}

template<typename T1, typename T2> void Draw::Drawob(T1* b, HDC& hdc, HBITMAP h2, T2 xlength, T2 ylength, int x1, int y1, int w1, int h1) {
	HDC hmemdc = CreateCompatibleDC(hdc2);
	SelectObject(hmemdc, h2);
	StretchBlt(hdc2, b->rect.x, b->rect.y, xlength, ylength, hmemdc, x1, y1, w1, h1, SRCCOPY);
	DeleteObject(hmemdc);
}

void Draw::BeginBufferHdc()
{
	hdc = GetDC(hwnd);
	hdc2 = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, NowWidth, NowHeight);
	SelectObject(hdc2, hBitmap);
}

void Draw::EndBufferHdc()
{
	BitBlt(hdc, 0, 0, NowWidth, NowHeight, hdc2, 0, 0, SRCCOPY);
	DeleteDC(hdc2);
	ReleaseDC(hwnd, hdc);
}

bool Draw::GetImage() 
{
	BITMAP bmp;
	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	ImageWidth = bmp.bmWidth;
	ImageHeight = bmp.bmHeight;
	if (ImageWidth == 0 || ImageHeight == 0)
		return false;
	return true;
}

bool Draw::GetImage(HBITMAP hBitmap)
{
	BITMAP bmp;
	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	ImageWidth = bmp.bmWidth;
	ImageHeight = bmp.bmHeight;
	if (ImageWidth == 0 || ImageHeight == 0)
		return false;
	return true;
}

Draw::~Draw()
{
}



HWND set_window(HINSTANCE hInst)
{
	WNDCLASSEXW wc;
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"WindowClassName";
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassExW(&wc);
	HWND hwnd = CreateWindowW(L"WindowClassName", L"���", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 100, 100, WindowWidth, WindowHeight, NULL, NULL, hInst, NULL);
	if (hwnd == NULL) return (HWND) - 1;
	HWND hButton1 = CreateWindow(L"Button", L"��ʼ��Ϸ", WS_CHILD | WS_VISIBLE, WindowWidth *0.45, WindowHeight *0.8, 100, 30, hwnd, (HMENU)ID_BUTTON_START, NULL, NULL);
	HWND hButton2 = CreateWindow(L"Button", L"����", WS_CHILD | WS_VISIBLE, WindowWidth * 0.45, WindowHeight * 0.8+30, 100, 30, hwnd, (HMENU)ID_BUTTON_SETTING, NULL, NULL);
	HWND hButton3 = CreateWindow(L"Button", L"�˳���Ϸ", WS_CHILD | WS_VISIBLE, WindowWidth * 0.45, WindowHeight * 0.8+60, 100, 30, hwnd, (HMENU)ID_BUTTON_END, NULL, NULL);


	return hwnd;
}