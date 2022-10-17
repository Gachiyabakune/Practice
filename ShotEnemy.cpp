#include "ShotEnemy.h"
#include "game.h"

namespace
{	//横に行くスピード
	constexpr float kShotSpeedX = 8.0f;
	//縦に行くスピード
	constexpr float kShotSpeedY = 8.0f;
}

void ShotEnemy::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = 0.0f;
	m_vec.y = kShotSpeedY;  //下方向に発射
}

void ShotEnemy::update( )
{
	if (!m_isExist)return;
	m_pos.y += kShotSpeedY;

	if (m_pos.y > 480)
	{
		m_isExist = false;
	}
}