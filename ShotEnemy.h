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

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();
};