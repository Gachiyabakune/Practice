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

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();
};