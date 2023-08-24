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

// BMP 文件头结构
struct BMPHeader {
    uint16_t fileType;       // 文件类型标识（"BM"）
    uint32_t fileSize;       // 文件大小
    uint16_t reserved1;      // 保留字段1
    uint16_t reserved2;      // 保留字段2
    uint32_t offset;         // 位图数据的偏移量
    uint32_t headerSize;     // 文件头大小
    int32_t width;           // 图像宽度
    int32_t height;          // 图像高度
    uint16_t planes;         // 颜色平面数
    uint16_t bitsPerPixel;   // 每像素位数
    uint32_t compression;    // 压缩方式
    uint32_t imageSize;      // 图像数据大小
    int32_t xPixelsPerMeter; // 水平分辨率
    int32_t yPixelsPerMeter; // 垂直分辨率
    uint32_t colorsUsed;     // 使用的颜色数
    uint32_t colorsImportant; // 重要的颜色数
};

