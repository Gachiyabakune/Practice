#pragma once

#include "ShotBase.h"

class ShotEnemy : public ShotBase
{
public:
	ShotEnemy()
	{
	}
	virtual ~ShotEnemy()
	{
	}

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();
};