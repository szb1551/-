#pragma once
#include<Windows.h>
#include<WinUser.h>
#include"include.h"

const int WindowWidth = 640;
const int WindowHeight = 480;

//typedef struct tagWNDCLASSA {
//	UINT style;
//	WNDPROC lpfnWndProc;
//	int cbClsExtra;
//	int cbWndExtra;
//	HINSTANCE hInstance;
//	HICON hIcon;
//	HCURSOR hCursor;
//	HBRUSH hbrBackground;
//	LPCSTR lpszMenuName;
//	LPCSTR lpszClassName;
//}WNDCLASSA, *PWNDCLASSA, *NPWNDCLASSA, *LPWNDCLASSA;

HWND set_window(HINSTANCE hInst);
long long WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

class Draw {
private:
	HBITMAP hBitmap;
	HWND hwnd;
	HDC hdc;
	int ImageWidth;
	int ImageHeight;
public:
	Draw(HBITMAP hBit, HWND hw, char* ImageFile);
	Draw(HBITMAP hBit, HWND hw);
	void DrawBackground();
	bool GetImage();
	~Draw();
};

// BMP �ļ�ͷ�ṹ
struct BMPHeader {
    uint16_t fileType;       // �ļ����ͱ�ʶ��"BM"��
    uint32_t fileSize;       // �ļ���С
    uint16_t reserved1;      // �����ֶ�1
    uint16_t reserved2;      // �����ֶ�2
    uint32_t offset;         // λͼ���ݵ�ƫ����
    uint32_t headerSize;     // �ļ�ͷ��С
    int32_t width;           // ͼ����
    int32_t height;          // ͼ��߶�
    uint16_t planes;         // ��ɫƽ����
    uint16_t bitsPerPixel;   // ÿ����λ��
    uint32_t compression;    // ѹ����ʽ
    uint32_t imageSize;      // ͼ�����ݴ�С
    int32_t xPixelsPerMeter; // ˮƽ�ֱ���
    int32_t yPixelsPerMeter; // ��ֱ�ֱ���
    uint32_t colorsUsed;     // ʹ�õ���ɫ��
    uint32_t colorsImportant; // ��Ҫ����ɫ��
};

