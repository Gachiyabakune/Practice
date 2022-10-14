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

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();

private:
};