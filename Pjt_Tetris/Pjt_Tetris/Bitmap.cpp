#include "Bitmap.h"

extern HWND hWndMain;

Bitmap::Bitmap()
{
}

void Bitmap::Init(HDC hdc, HINSTANCE hInst, int id)
{
	m_pBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1 + id));

	BITMAP bitmapInfo;
	GetObject(m_pBitmap, sizeof(bitmapInfo), &bitmapInfo);
	m_size.cx = bitmapInfo.bmWidth;
	m_size.cy = bitmapInfo.bmHeight;
}

void Bitmap::Draw(HDC hdc, int x, int y)
{
	m_MemDC = CreateCompatibleDC(hdc);
	m_pOldBitmap = (HBITMAP)SelectObject(m_MemDC, m_pBitmap);
	BitBlt(hdc, x* m_size.cx, y* m_size.cx, m_size.cx, m_size.cy, m_MemDC, 0, 0, SRCCOPY);
	SelectObject(m_MemDC, m_pOldBitmap);
	DeleteDC(m_MemDC);

}

Bitmap::~Bitmap()
{
	SelectObject(m_MemDC, m_pOldBitmap);
	DeleteObject(m_pBitmap);
	DeleteDC(m_MemDC);
}