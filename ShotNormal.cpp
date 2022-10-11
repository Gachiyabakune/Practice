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
	m_vec.y = kShotSpeed;  //������ɔ���
}

void ShotNormal::update()
{
	if (!m_isExist)return;
	m_pos -= m_vec;

	//��ʊO�ɍs�����ꍇ
	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
	/*if (m_pos.x < 0)
	{
		m_isExist = false;
	}*/
}