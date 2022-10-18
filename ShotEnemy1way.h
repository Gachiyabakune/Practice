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

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();

private:

	int shotCount;
	int nway;
};