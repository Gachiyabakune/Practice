#pragma once

#include "ShotBase.h"

class ShotEnemy2way : public ShotBase
{
public:
	ShotEnemy2way()
	{
	}
	virtual ~ShotEnemy2way()
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