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

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();
};