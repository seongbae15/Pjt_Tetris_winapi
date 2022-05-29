#pragma once
#include "Bitmap.h"

#define BITMAP_COUNT 11

class BitmapManager
{
private:
	Bitmap* m_pArrBitmap[BITMAP_COUNT];
public:
	BitmapManager() {};
	~BitmapManager();
	void Init(HWND hWnd, HINSTANCE hInst);
	void Draw(HDC hdc, int x, int y, int bitmapIndex);
	void Release();
	inline SIZE GetNthBitmapSize(int i)
	{
		return m_pArrBitmap[i]->GetBitmapSize();
	}
};

