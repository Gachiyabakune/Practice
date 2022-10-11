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
	m_vec.y = kShotSpeed;  //ã•ûŒü‚É”­Ë
}

void ShotNormal::update()
{
	if (!m_isExist)return;
	m_pos -= m_vec;

	//‰æ–ÊŠO‚És‚Á‚½ê‡
	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
	/*if (m_pos.x < 0)
	{
		m_isExist = false;
	}*/
}