#pragma once
#include "windows.h"
#define INDEX_ROT 4
#define INDEX_BRICK_POINT 4
#define RANDOM(n) (rand()%n)

struct Point
{
	int x;
	int y;
};
//Block 모양 배열.
extern Point stArrShapePoints[][INDEX_ROT][INDEX_BRICK_POINT];


class BrickManager
{
private:
	Point m_stCurPosition;
	int m_iBrickShape;
	int m_iNextBrickShape;
	int m_iBrickRot;
	const int m_iInitX = 5;
	const int m_iInitY = 2;
public:
	void Init();
	void CreateNewBrick();
	void MoveDownBrick();
	void InitBrickPosition(int x, int y, int rot);
	void CompleteBrickDown();
	void MoveBrick(int x, int y, int rot);
	inline Point GetCurPosition()
	{
		return m_stCurPosition;
	}
	inline Point GetCurBrickShapePoint(int shape, int point, int rot = INDEX_ROT)
	{
		if (INDEX_ROT == rot)
			return stArrShapePoints[shape][m_iBrickRot][point];
		else
			return stArrShapePoints[shape][rot][point];
	}
	inline int GetCurBrickShape()
	{
		return m_iBrickShape;
	}
	inline int GetCurBrickRotation()
	{
		return m_iBrickRot;
	}
	inline int GetNextBrickShape()
	{
		return m_iNextBrickShape;
	}
};

