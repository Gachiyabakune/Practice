#include "villainFirst.h"
#include "game.h"

namespace
{
	constexpr float kShotSpeed = 2.0f;
}

void VillainFirst::start(Vec2 pos)
{
	VillainBase::start(pos);

	m_vec.x = 0.0f;
	m_vec.y = kShotSpeed;  //�������ɔ���
}

void VillainFirst::update()
{
	if (!m_isExist)return;
	m_pos += m_vec;

	//��ʊO�ɍs�����ꍇ
	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
}