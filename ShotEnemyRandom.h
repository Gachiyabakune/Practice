#pragma once

#include "ShotBase.h"

class ShotEnemyRandom : public ShotBase
{
public:
	ShotEnemyRandom()
	{
	}
	virtual ~ShotEnemyRandom()
	{
	}

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();

private:
};