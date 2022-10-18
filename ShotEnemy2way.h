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

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();

private:

	int shotCount;
	int nway;
};