#pragma once
#include "BrickManager.h"
#include <Windows.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 20

#define EMPTY 0
#define BRICK 1
#define WALL 10

#define CUR 0
#define NEXT 1

class GameSceneManager
{
private:
	int m_iArrBoard[MAP_HEIGHT + 2][MAP_WIDTH + 2];

	BrickManager m_cBrickManager;
public:
	void Init();
	void InitMap();
	bool MoveDown(HWND hWnd);
	void MoveBrickInScene(HWND hWnd, WPARAM wParam);
	int GetAround(int delX, int delY, int nRot = INDEX_ROT);
	int SetBrickToMap(HWND hWnd);
	int CheckRemoveBrick(HWND hWnd);
	void MakeNewBrickInScene();
	void MoveBrickInScene(int delX, int delY, int rot);
	inline int GetBrickShape(int option = CUR)
	{
		switch (option)
		{
		case CUR:
			return m_cBrickManager.GetCurBrickShape();
		case NEXT:
			return m_cBrickManager.GetNextBrickShape();
		}
	}
	inline int GetBoardInfo(int x, int y)
	{
		return m_iArrBoard[y][x];
	}
	inline Point GetMovingBrickPosition()
	{
		return m_cBrickManager.GetCurPosition();
	}
	inline Point GetBrickShapePoint(int shape, int point, int rot = INDEX_ROT)
	{
		return m_cBrickManager.GetCurBrickShapePoint(shape, point, rot);
	}
};


