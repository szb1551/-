#include "bin/manage.h"
#include "bin/tank.h"
#include "bin/collide.h"
#include "bin/include.h"
//#include "map.h"

//HBITMAP hBitmap;
//int width = WindowWidth;
//int height = WindowHeight;
AllObjects All_Ob;
//extern Enemy EM[ENEMY_NUM];
extern vector<TANK*> EM;
HBITMAP map[4]; //��ŵ�ͼ��Դ

int mapIndex[rows][cols] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2,
						   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 1, 2, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 1, 2, 2,
						   2, 3, 3, 3, 2, 3, 1, 3, 2, 3, 3, 3, 2, 1, 2, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 1, 2, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 1, 2, 2,
						   2, 3, 3, 3, 2, 3, 1, 3, 2, 3, 3, 3, 2, 1, 2, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 1, 2, 2,
						   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2,
						   1, 2, 2, 2, 2, 3, 2, 3, 2, 2, 2, 2, 1, 1, 2, 2,
						   2, 3, 2, 3, 2, 3, 3, 3, 2, 3, 2, 3, 2, 1, 2, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 1, 2, 2,
						   2, 3, 3, 3, 2, 2, 2, 2, 2, 3, 3, 3, 2, 1, 2, 2,
						   2, 3, 2, 3, 2, 3, 3, 3, 2, 3, 2, 3, 2, 1, 2, 2,
						   2, 2, 2, 2, 2, 3, 0, 3, 2, 2, 2, 2, 2, 1, 2, 2
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
	DeleteObject(hOldBitmap);
}

void Draw::InitBackGround()
{
	//���ذ�ť
	for (int i = 1; i <= ButtonCount; i++)
	{
		ShowWindow(GetDlgItem(hwnd, i), SW_HIDE);
	}
	// ������ɫ��ˢ
	HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	// ���ô��ڱ�����ˢ
	RECT rect = { 0, 0, NowWidth, NowHeight };
	FillRect(hdc2, &rect, hBlackBrush);
	DeleteObject(hBlackBrush);
}

void Draw::ClearTank()
{

}

void Draw::DrawTank(TANK*tank)
{
	double xlength = (double)NowWidth / (rows);
	double ylength = (double)NowHeight / (cols+1);
	tank->SetHDC(hdc2);
	tank->Update(xlength, ylength);
	tank->DRAWONE();
	tank->Fire();
}

void Draw::DrawBullet(Bullet* bullet)
{
	bullet->Move();
}

void Draw::InitWorld() {
	//GetClientRect(hh, &worldre);
	All_Ob.clear();
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
		for (int colNum = 0; colNum < cols; colNum++) {
			x = (colNum) * xlength;//��ͼ���ں�����			
			y = (rowNum) * ylength;//��ͼ����������	
			Subject thing = (Subject)mapIndex[rowNum][colNum];
			if (thing == iron) {
				ob.life = 4;
 			}
			else if (thing == wall) {
				ob.life = 1;
			}
			else if (thing == eagle) {
				ob.life = 1;
			}
			Point point(rowNum, colNum);
			Rect rect(x,y,xlength,ylength);
			ob.subject = thing;
			ob.rect = rect;
			ob.point = point;
			if (thing != sail)
			{
				All_Ob.Insert(ob);
				Rectangle(hdc2, x, y, x + xlength, y + ylength);
				//Drawob(&ob, hdc2, map[thing], xlength, ylength);
			}	
		}
	}
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		Enemy* temp = new Enemy(0, 0, down);
		HBITMAP hBlt = (HBITMAP)LoadImage(NULL, L"image/enemytank_66.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (i % 3 == 0)
		{
			temp->mapcol = 0;
		}
		else if (i % 3 == 1)
		{
			temp->mapcol = 6;
		}
		else if (i % 3 == 2)
		{
			temp->mapcol = 12;
		}
		temp->UpdatePosition();
		temp->SetBlt(hBlt);
		temp->life = 1;
		temp->SetOwner(1);
		temp->SetID(i);
		EM.push_back(temp);
	}
}

void Draw::ChangeWorld() {
	//GetClientRect(hh, &worldre);
	double xlength = (double)NowWidth / (rows);
	double ylength = (double)NowHeight / (cols+1);
	double x, y;
	Object ob;
	for (int i = 0; i < All_Ob.object_num; i++)
	{
		Point point = All_Ob.Objects[i].point;
		Rect rect = All_Ob.Objects[i].rect;
		int thing = mapIndex[point.maprow][point.mapcol];
		Drawob(&All_Ob.Objects[i], hdc2, map[thing], xlength, ylength);
	}
}

template<typename T1, typename T2> void Draw::Drawob(T1* b, HDC& hdc, HBITMAP h2, T2 xlength, T2 ylength, int x1, int y1, int w1, int h1) {
	HDC hmemdc = CreateCompatibleDC(hdc2);
	SelectObject(hmemdc, h2);
	StretchBlt(hdc2, b->rect.x, b->rect.y, xlength, ylength, hmemdc, x1, y1, w1, h1, SRCCOPY);
	//DeleteObject(hmemdc);
	DeleteDC(hmemdc);
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
	DeleteObject(hBitmap);
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

bool Draw::GetImage(HBITMAP& hBitmap)
{
	BITMAP bmp;
	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	ImageWidth = bmp.bmWidth;
	ImageHeight = bmp.bmHeight;
	if (ImageWidth == 0 || ImageHeight == 0)
		return false;
	return true;
}

void Draw::DrawLoseGround()
{
	CImage img;
	WCHAR filename[] = L"image/lose.jpg";
	HRESULT ret = img.Load(filename); // filename ��Ҫ���ص��ļ���������·����
	HBITMAP bitmap = img.Detach();
	//�����ڴ��豸������
	hdc2 = CreateCompatibleDC(hdc);
	SelectObject(hdc2, bitmap);

	// ���ư�ť
	/*cout << "���ư�ť" << endl;
	for (int i = 1; i <= ButtonCount; i++)
	{
		int buttonx = NowWidth / 2 - 50;
		int buttony = NowHeight * 0.8 - 15 + (30 * (i - 1));
		SetWindowPos(GetDlgItem(hwnd, i), NULL, buttonx, buttony, 100, 30, SWP_SHOWWINDOW);
	}*/

	//��ȡͼ��
	if (GetImage(bitmap))
	{
		cout << "��ȡͼ��ɹ�" << endl;
		StretchBlt(hdc, 0, 0, NowWidth, NowHeight, hdc2, 0, 0, ImageWidth, ImageHeight, SRCCOPY);
	}
	//����ͼ��
	//������Դ
	DeleteDC(hdc2);
	DeleteObject(bitmap);
}

void Draw::DrawWinGround()
{
	CImage img;
	WCHAR filename[] = L"image/win.jpg";
	HRESULT ret = img.Load(filename); // filename ��Ҫ���ص��ļ���������·����
	HBITMAP bitmap = img.Detach();
	//�����ڴ��豸������
	hdc2 = CreateCompatibleDC(hdc);
	SelectObject(hdc2, bitmap);

	//��ȡͼ��
	if (GetImage(bitmap))
	{
		cout << "��ȡͼ��ɹ�" << endl;
		StretchBlt(hdc, 0, 0, NowWidth, NowHeight, hdc2, 0, 0, ImageWidth, ImageHeight, SRCCOPY);
	}
	//����ͼ��
	//������Դ
	DeleteDC(hdc2);
	DeleteObject(bitmap);
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
	wc.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	RegisterClassExW(&wc);
	HWND hwnd = CreateWindowW(L"WindowClassName", L"���", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 100, 100, WindowWidth, WindowHeight, NULL, NULL, hInst, NULL);
	if (hwnd == NULL) return (HWND) - 1;
	HWND hButton1 = CreateWindow(L"Button", L"��ʼ��Ϸ", WS_CHILD | WS_VISIBLE, WindowWidth *0.45, WindowHeight *0.8, 100, 30, hwnd, (HMENU)ID_BUTTON_START, NULL, NULL);
	HWND hButton2 = CreateWindow(L"Button", L"����", WS_CHILD | WS_VISIBLE, WindowWidth * 0.45, WindowHeight * 0.8+30, 100, 30, hwnd, (HMENU)ID_BUTTON_SETTING, NULL, NULL);
	HWND hButton3 = CreateWindow(L"Button", L"�˳���Ϸ", WS_CHILD | WS_VISIBLE, WindowWidth * 0.45, WindowHeight * 0.8+60, 100, 30, hwnd, (HMENU)ID_BUTTON_END, NULL, NULL);


	return hwnd;
}