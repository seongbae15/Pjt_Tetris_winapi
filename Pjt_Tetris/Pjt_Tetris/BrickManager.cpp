#include "BrickManager.h"

extern Point stArrShapePoints[][INDEX_ROT][INDEX_BRICK_POINT] = {
	{{{0,0},{1,0},{2,0},{-1,0}},{{0,0},{0,1},{0,-1},{0,-2}},{{0,0},{1,0},{2,0},{-1,0}},{{0,0},{0,1},{0,-1},{0,-2}}},
	{{{0,0},{1,0},{0,1},{1,1}},{{0,0},{1,0},{0,1},{1,1}},{{0,0},{1,0},{0,1},{1,1}},{{0,0},{1,0},{0,1},{1,1}}},
	{{{0,0},{-1,0},{0,-1},{1,-1}},{{0,0},{0,1},{-1,0},{-1,-1}},{{0,0},{-1,0},{0,-1},{1,-1}},{{0,0},{0,1},{-1,0},{-1,-1}}},
	{{{0,0},{-1,-1},{0,-1},{1,0}},{{0,0},{-1,0},{-1,1},{0,-1}},{{0,0},{-1,-1},{0,-1},{1,0}},{{0,0},{-1,0},{-1,1},{0,-1}}},
	{{{0,0},{-1,0},{1,0},{-1,-1}},{{0,0},{0,-1},{0,1},{-1,1}},{{0,0},{-1,0},{1,0},{1,1}},{{0,0},{0,-1},{0,1},{1,-1}}},
	{{{0,0},{1,0},{-1,0},{1,-1}},{{0,0},{0,1},{0,-1},{-1,-1}},{{0,0},{1,0},{-1,0},{-1,1}},{{0,0},{0,-1},{0,1},{1,1}}},
	{{{0,0},{-1,0},{1,0},{0,1}},{{0,0},{0,-1},{0,1},{1,0}},{{0,0},{-1,0},{1,0},{0,-1}},{{0,0},{-1,0},{0,-1},{0,1}}},
	{{{0,0},{0,0},{0,0},{0,0}},{{0,0},{0,0},{0,0},{0,0}},{{0,0},{0,0},{0,0},{0,0}},{{0,0},{0,0},{0,0},{0,0}}},
	{{{0,0},{0,0},{0,-1},{1,0}},{{0,0},{0,0},{-1,0},{0,-1}},{{0,0},{0,0},{0,1},{-1,0}},{{0,0},{0,0},{0,1},{1,0}}},
};

void BrickManager::Init()
{
	m_iNextBrickShape = RANDOM(sizeof(stArrShapePoints) / sizeof(stArrShapePoints[0]));
}

void BrickManager::MoveDownBrick()
{
	m_stCurPosition.y++;
}

void BrickManager::CreateNewBrick()
{
	m_iBrickShape = m_iNextBrickShape;
	m_iNextBrickShape = RANDOM(sizeof(stArrShapePoints) / sizeof(stArrShapePoints[0]));

	InitBrickPosition(m_iInitX, m_iInitY, 0);

}

void BrickManager::InitBrickPosition(int x, int y, int rot)
{
	m_stCurPosition.x = x;
	m_stCurPosition.y = y;
	m_iBrickRot = rot;
}

void BrickManager::CompleteBrickDown()
{
	m_iBrickShape = -1;
}

void BrickManager::MoveBrick(int delX, int delY, int rot)
{
	m_stCurPosition.x += delX;
	m_stCurPosition.y += delY;
	m_iBrickRot = rot;
}
