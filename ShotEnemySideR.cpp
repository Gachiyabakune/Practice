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
	m_vec.y = 0.0f;  //�E�����ɔ���
}

void ShotEnemySideR::update()
{
	if (!m_isExist)return;

	m_pos += m_vec;

	//��ʊO�ɍs�����ꍇ
	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
}