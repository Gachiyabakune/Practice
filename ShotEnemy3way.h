#pragma once

#include "ShotBase.h"

class ShotEnemy3way : public ShotBase
{
public:
	ShotEnemy3way()
	{
	}
	virtual ~ShotEnemy3way()
	{
	}

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();

private:

	int shotCount;
	int nway;
};