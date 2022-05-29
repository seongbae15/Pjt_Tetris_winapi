#include "BitmapManager.h"

void BitmapManager::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);
	for (int i = 0; i < BITMAP_COUNT; i++)
	{
		m_pArrBitmap[i] = new Bitmap;
		m_pArrBitmap[i]->Init(hdc, hInst,i);
	}
}

void BitmapManager::Draw(HDC hdc, int x, int y, int bitmapIndex)
{
	m_pArrBitmap[bitmapIndex]->Draw(hdc, x, y);
}

void BitmapManager::Release()
{
	for (int i = 0; i < BITMAP_COUNT; i++)
	{
		delete m_pArrBitmap[i];

	}
}

BitmapManager::~BitmapManager()
{
	for (int i = 0; i < BITMAP_COUNT; i++)
	{
		delete m_pArrBitmap[i];

	}

}