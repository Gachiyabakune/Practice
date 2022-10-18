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

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();

private:

	int shotCount;
	int nway;
};