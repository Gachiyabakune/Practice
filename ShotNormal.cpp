#include "ShotNormal.h"
#include "game.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;
}

void ShotNormal::start(Vec2 pos)
{
	ShotBase::start(pos);

	/*m_vec.x = kShotSpeed;
	m_vec.y = 0.0f;*/
	m_vec.x = 0.0f;
	m_vec.y = kShotSpeed;  //上方向に発射
}

void ShotNormal::update()
{
	if (!m_isExist)return;
	m_pos -= m_vec;

	//画面外に行った場合
	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
}