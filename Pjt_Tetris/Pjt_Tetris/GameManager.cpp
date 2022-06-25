#include "GameManager.h"

//GameManager* GameManager::m_instance = NULL;

void GameManager::Init(HWND hWnd, HINSTANCE hInst)
{
	m_eGAMESTATUS = GAMEOVER;

	InitValues();

	//Init BitmapManager class.
	m_cBitmapManager.Init(hWnd, hInst);
	//Init GameSceneManager class.
	m_cGameSceneManager.Init();

	m_sizeBrickImg = m_cBitmapManager.GetNthBitmapSize(0);

}

void GameManager::InitValues()
{
	m_iInterval = m_iInitInterval;
	m_iScore = 0;
	m_iBrickCount = 0;

}

void GameManager::GameStart(HWND hWnd)
{
	//Init Map.
	m_cGameSceneManager.InitMap();

	m_eGAMESTATUS = RUNNING;

	InitValues();

	UpdateNewBrick(hWnd);
}

void GameManager::ChangeGameStatus(EGAMESTATUS gameStatus)
{
	m_eGAMESTATUS = gameStatus;
}

void GameManager::UpdateGameInfo(HWND hWnd, int removeLine)
{
	UpdateBrickCount();
	UpdateScore(removeLine);
	FasterGame(hWnd);
}

void GameManager::UpdateScore(int removeLine)
{
	m_iScore += m_iArrAddScore[removeLine];
}

void GameManager::UpdateBrickCount()
{
	m_iBrickCount++;
}

void GameManager::Update(HWND hWnd)
{
	if (m_cGameSceneManager.MoveDown(hWnd))
	{

		//Create new brick.
		UpdateNewBrick(hWnd);

		//Check Game over.
		CheckGameOver(hWnd);
	}
}

void GameManager::FasterGame(HWND hWnd)
{
	//시간 간격 축소.
	if ((m_iBrickCount % 10 == 0) && (m_iInitInterval > 200))
	{
		m_iInterval -= m_iReducedDelInterval;
		SetTimer(hWnd, 1, m_iInterval, NULL);
	}

}

void GameManager::UpdateNewBrick(HWND hWnd)
{
	m_cGameSceneManager.MakeNewBrickInScene();

	InvalidateRect(hWnd, NULL, FALSE);


}

void GameManager::CheckGameOver(HWND hWnd)
{
	//GameOver 상태인지 확인.
	if (EMPTY != m_cGameSceneManager.GetAround(0,0))
	{
		KillTimer(hWnd, 1);
		ChangeGameStatus(GAMEOVER);
		MessageBox(hWnd, TEXT("Game Over. If you wanna restart,")
			TEXT(" Please Select 게임/시작(S)."), TEXT("알림"), MB_OK);
	}

}

void GameManager::InputGameKey(HWND hWnd, WPARAM wParam)
{
	if (RUNNING != m_eGAMESTATUS || -1 == m_cGameSceneManager.GetBrickShape())
		return;
	m_cGameSceneManager.MoveBrickInScene(hWnd, wParam);
}

void GameManager::Draw(HWND hWnd, HDC hdc)
{
	HDC BackMemDC = CreateCompatibleDC(hdc);
	RECT crt;
	GetClientRect(hWnd, &crt);
	HBITMAP TempBit, OldBitmap;
	TempBit = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	OldBitmap = (HBITMAP)SelectObject(BackMemDC, TempBit);
	FillRect(BackMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));

	//Map, 고정된 Brick 그리기
	DrawSetBrick(BackMemDC);
	//현재 내려오는 블록 그리기.
	DrawMovingBrick(BackMemDC);
	//UI 그리기.
	DrawUserInterface(BackMemDC);
	
	BitBlt(hdc, crt.left, crt.top, crt.right, crt.bottom, BackMemDC, 0, 0, SRCCOPY);
	SelectObject(BackMemDC, OldBitmap);
	DeleteObject(TempBit);
	DeleteDC(BackMemDC);
}

void GameManager::Draw(HDC hdc)
{
	//Map, 고정된 Brick 그리기
	DrawSetBrick(hdc);
	//현재 내려오는 블록 그리기.
	DrawMovingBrick(hdc);
	//UI 그리기.
	DrawUserInterface(hdc);
}

void GameManager::DrawSetBrick(HDC hdc)
{
	for (int y = 0; y < MAP_HEIGHT + 2; y++)
	{
		for (int x = 0; x < MAP_WIDTH + 2; x++)
		{
			//WALL & Set Brick 그리기.
			if (0 == y || MAP_HEIGHT + 1 == y)
				m_cBitmapManager.Draw(hdc, x, y, WALL);
			else if (0 == x || MAP_WIDTH + 1 == x)
				m_cBitmapManager.Draw(hdc, x, y, WALL);
			else
				m_cBitmapManager.Draw(hdc, x, y, m_cGameSceneManager.GetBoardInfo(x, y));
		}
	}
}

void GameManager::DrawMovingBrick(HDC hdc)
{
	int iBrickShape = m_cGameSceneManager.GetBrickShape();
	if (GAMEOVER != GetGameStatus() && -1 != iBrickShape)
	{
		Point tempCurPosition = m_cGameSceneManager.GetMovingBrickPosition();
		for (int i = 0; i < INDEX_BRICK_POINT; i++)
		{
			Point tempCurShapePoint = m_cGameSceneManager.GetBrickShapePoint(iBrickShape, i);
			m_cBitmapManager.Draw(hdc, tempCurPosition.x + tempCurShapePoint.x, tempCurPosition.y + tempCurShapePoint.y, iBrickShape + 1);
		}
	}

}

void GameManager::DrawUserInterface(HDC hdc)
{
	TCHAR str[128];

	//UI 그리기.
	for (int y = MAP_HEIGHT - 5; y <= MAP_HEIGHT + 1; y++)
	{
		for (int x = MAP_WIDTH + 3; x <= MAP_WIDTH + 11; x++)
		{
			if (MAP_WIDTH + 3 == x || MAP_WIDTH + 11 == x || MAP_HEIGHT - 5 == y || MAP_HEIGHT + 1 == y)
			{
				m_cBitmapManager.Draw(hdc, x, y, WALL);
			}
			else
				m_cBitmapManager.Draw(hdc, x, y, 0);
		}
	}

	//UI 그리기: 다음 블록 표시
	if (GAMEOVER != GetGameStatus())
	{
		int iNextShape = m_cGameSceneManager.GetBrickShape(NEXT);
		for (int i = 0; i < INDEX_BRICK_POINT; i++)
		{
			Point tempCurShapePoint = m_cGameSceneManager.GetBrickShapePoint(iNextShape, i,0);
			m_cBitmapManager.Draw(hdc, MAP_WIDTH + 7 + tempCurShapePoint.x, MAP_HEIGHT - 2 + tempCurShapePoint.y, iNextShape + 1);
		}
	}

	lstrcpy(str, TEXT("Tetris Ver1.1   "));
	TextOut(hdc, (MAP_WIDTH + 4) * m_sizeBrickImg.cx, 30, str, lstrlen(str));
	wsprintf(str, TEXT("점수: %d      "), m_iScore);
	TextOut(hdc, (MAP_WIDTH + 4) * m_sizeBrickImg.cx, 60, str, lstrlen(str));
	wsprintf(str, TEXT("벽돌: %d 개      "), m_iBrickCount);
	TextOut(hdc, (MAP_WIDTH + 4) * m_sizeBrickImg.cx, 80, str, lstrlen(str));

}

void GameManager::Release()
{
	//Release bitmaps
	m_cBitmapManager.Release();
}
