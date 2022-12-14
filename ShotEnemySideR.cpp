#include "ShotEnemySideR.h"
#include "game.h"

namespace
{
	constexpr float kShotSpeed = 4.0f;
}

void ShotEnemySideR::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = kShotSpeed;
	m_vec.y = 0.0f;  //右方向に発射
}

void ShotEnemySideR::update()
{
	if (!m_isExist)return;

	m_pos += m_vec;

	//画面外に行った場合
	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
}