#pragma once

#include "ShotBase.h"

class ShotEnemy1way : public ShotBase
{
public:
	ShotEnemy1way()
	{
	}
	virtual ~ShotEnemy1way()
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