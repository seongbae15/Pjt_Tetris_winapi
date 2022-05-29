#pragma once
#include "GameManager.h"

#include "GameSceneManager.h"


void GameSceneManager::Init()
{
	InitMap();

	m_cBrickManager.Init();
}

void GameSceneManager::InitMap()
{
	for (int y = 0; y < MAP_HEIGHT + 2; y++)
	{
		for (int x = 0; x < MAP_WIDTH + 2; x++)
		{
			m_iArrBoard[y][x] = ((y == 0 || y == MAP_HEIGHT + 1)
				|| (x == 0 || x == MAP_WIDTH + 1)) ? WALL : EMPTY;
		}
	}

}

bool GameSceneManager::MoveDown(HWND hWnd)
{
	if (GetAround(0,1) != EMPTY)
	{
		//Set brick to map.
		int iRemoveCount = SetBrickToMap(hWnd);
		GameManager::GetInstance()->UpdateGameInfo(hWnd, iRemoveCount);
		return true;
	}
	m_cBrickManager.MoveDownBrick();
	
	InvalidateRect(hWnd, NULL, FALSE);
	UpdateWindow(hWnd);
	return false;
}

int GameSceneManager::GetAround(int delX, int delY, int nRot)
{
	int iTemp = EMPTY;
	int iShape = m_cBrickManager.GetCurBrickShape();
	Point tempCurPosition = m_cBrickManager.GetCurPosition();
	for (int i = 0; i < INDEX_BRICK_POINT; i++)
	{
		Point tempCurBrickPoint = m_cBrickManager.GetCurBrickShapePoint(iShape, i, nRot);
		iTemp = max(iTemp, m_iArrBoard[tempCurPosition.y + delY + tempCurBrickPoint.y][tempCurPosition.x + delX + tempCurBrickPoint.x]);
	}
	return iTemp;
}

int GameSceneManager::SetBrickToMap(HWND hWnd)
{
	Point tempCurPosition = m_cBrickManager.GetCurPosition();
	int iShape = m_cBrickManager.GetCurBrickShape();

	for (int i = 0; i < INDEX_BRICK_POINT; i++)
	{
		Point tempCurBrickPoint = m_cBrickManager.GetCurBrickShapePoint(iShape,i);
		m_iArrBoard[tempCurPosition.y + tempCurBrickPoint.y][tempCurPosition.x + tempCurBrickPoint.x] = m_cBrickManager.GetCurBrickShape()+1;
	}
	//블록 내려놓은 상태.
	m_cBrickManager.CompleteBrickDown();

	//블록 제거 검사.
	int iRemoveCount = CheckRemoveBrick(hWnd);

	return iRemoveCount;
}

int GameSceneManager::CheckRemoveBrick(HWND hWnd)
{
	int iRemoveCount = 0;
	//블록 제거 검사.
	for (int y = 1; y < MAP_HEIGHT + 1; y++)
	{
		int x;
		for (x = 1; x < MAP_WIDTH + 1; x++)
		{
			//블록 빈부분이 잆을 경우, x축 검사 탈출.
			if (EMPTY == m_iArrBoard[y][x])
				break;
		}

		if (x == MAP_WIDTH + 1)
		{
			iRemoveCount++;
			//삭제될 위치~윗부분까지 전체 아래로 Down.
			for (int ty = y; ty > 1; ty--)
			{

				for (x = 1; x < MAP_WIDTH + 1; x++)
				{
					m_iArrBoard[ty][x] = m_iArrBoard[ty-1][x];
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
			UpdateWindow(hWnd);
			
			//Delay.
			Sleep(150);
		}
	}
	
	return iRemoveCount;

}

void GameSceneManager::MakeNewBrickInScene()
{
	m_cBrickManager.CreateNewBrick();
}

void GameSceneManager::MoveBrickInScene(HWND hWnd, WPARAM wParam)
{
	int iTransfromRot = m_cBrickManager.GetCurBrickRotation();
	switch (wParam)
	{
	case VK_LEFT:
		if (GetAround(-1,0) == EMPTY)
		{
			MoveBrickInScene(-1, 0, iTransfromRot);
			InvalidateRect(hWnd, NULL, FALSE);
			UpdateWindow(hWnd);
		}
		break;
	case VK_RIGHT:
		if (GetAround(1,0) == EMPTY)
		{
			MoveBrickInScene(1, 0, iTransfromRot);
			InvalidateRect(hWnd, NULL, FALSE);
			UpdateWindow(hWnd);

		}
		break;
	case VK_UP:
		iTransfromRot = ((3 == iTransfromRot) ? 0 : iTransfromRot + 1);
		if (GetAround(0,0, iTransfromRot) == EMPTY)
		{
			MoveBrickInScene(0, 0, iTransfromRot);
			InvalidateRect(hWnd, NULL, FALSE);
			UpdateWindow(hWnd);
		}
		break;
	case VK_DOWN:
		if (MoveDown(hWnd) != false)
			MakeNewBrickInScene();
		break;
	case VK_SPACE:
		while (MoveDown(hWnd) == false) { ; }
		MakeNewBrickInScene();
		break;
	default:
		break;
	}
}

void GameSceneManager::MoveBrickInScene(int delX, int delY, int rot)
{
	m_cBrickManager.MoveBrick(delX, delY, rot);
}





