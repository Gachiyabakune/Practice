#include "ShotFall.h"
#include "game.h"

namespace
{	//横に行くスピード
	constexpr float kShotSpeedX = 8.0f;
	//縦に行くスピード
	constexpr float kShotSpeedY = 6.0f;
	//重力z
	constexpr float kGravity = 0.4f;
}

void ShotFall::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = 0.0f;
	m_vec.y = kShotSpeedY;  //上方向に発射
}

void ShotFall::update( )
{
	if (!m_isExist)return;
	m_pos.y += kShotSpeedY;

	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
}