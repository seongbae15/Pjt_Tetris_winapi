#pragma once
#include "resource.h"
#include <windows.h>
class Bitmap
{
private:
	HDC m_MemDC;
	HBITMAP m_pBitmap;
	HBITMAP m_pOldBitmap;
	SIZE m_size;
public:
	Bitmap();
	~Bitmap();
	//void Init(HDC hdc, HINSTANCE hInst, int id);
	void Init(HDC hdc, HINSTANCE hInst, int id);
	void Draw(HDC hdc, int x, int y);
	inline SIZE GetBitmapSize()
	{
		return m_size;
	}
};

