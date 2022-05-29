#pragma once
#include "Singletone.h"
#include "BitmapManager.h"
#include "GameSceneManager.h"

enum EGAMESTATUS
{
	GAMEOVER,
	RUNNING,
	PAUSE,
};


class GameManager:public Singletone<GameManager>
{
private:
	BitmapManager m_cBitmapManager;
	GameSceneManager m_cGameSceneManager;

	EGAMESTATUS m_eGAMESTATUS;
	int m_iInterval;
	int m_iScore;
	int m_iBrickCount;
	SIZE m_sizeBrickImg;
	const int m_iInitInterval=1000;
	const int m_iReducedDelInterval = 50;
	const int m_iArrAddScore[5] = { 0,1,5,10,20 };

public:
	void Init(HWND hWnd, HINSTANCE hInst);
	void InitValues();
	void Update(HWND hWnd);
	void Release();
	void GameStart(HWND hWnd);
	void ChangeGameStatus(EGAMESTATUS gameStatus);
	void UpdateGameInfo(HWND hWnd, int removeLine);
	void UpdateScore(int removeLine);
	void UpdateBrickCount();
	void FasterGame(HWND hWnd);
	void UpdateNewBrick(HWND hWnd);
	void CheckGameOver(HWND hWnd);
	void InputGameKey(HWND hWnd, WPARAM wParam);
	void Draw(HDC hdc);
	void DrawSetBrick(HDC hdc);
	void DrawMovingBrick(HDC hdc);
	void DrawUserInterface(HDC hdc);
	inline EGAMESTATUS  GetGameStatus()
	{
		return m_eGAMESTATUS;
	}
	inline int GetIntervalTime()
	{
		return m_iInterval;
	}
	inline int GetScore()
	{
		return m_iScore;
	}
	inline int GetBrickCount()
	{
		return m_iBrickCount;
	}
	inline SIZE GetImgSize()
	{
		return m_sizeBrickImg;
	}
};
