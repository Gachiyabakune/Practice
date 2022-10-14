#pragma once

#include "villainBase.h"

class VillainFirst : public VillainBase
{
public:
	VillainFirst()
	{
	}
	virtual ~VillainFirst()
	{
	}

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();
};