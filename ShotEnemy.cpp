#include "ShotEnemy.h"
#include "game.h"

namespace
{	//���ɍs���X�s�[�h
	constexpr float kShotSpeedX = 8.0f;
	//�c�ɍs���X�s�[�h
	constexpr float kShotSpeedY = 8.0f;
}

void ShotEnemy::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = 0.0f;
	m_vec.y = kShotSpeedY;  //�������ɔ���
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