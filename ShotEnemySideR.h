#pragma once

#include "ShotBase.h"

class ShotEnemySideR : public ShotBase
{
public:
	ShotEnemySideR()
	{
	}
	virtual ~ShotEnemySideR()
	{
	}

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();
};