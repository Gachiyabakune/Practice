#include "ShotEnemy.h"
#include "game.h"

namespace
{	//���ɍs���X�s�[�h
	constexpr float kShotSpeedX = 8.0f;
	//�c�ɍs���X�s�[�h
	constexpr float kShotSpeedY = 8.0f;
	//�d��z
	constexpr float kGravity = 0.4f;
}

void ShotEnemy::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = 0.0f;
	m_vec.y = kShotSpeedY;  //������ɔ���
}

void ShotEnemy::update( )
{
	if (!m_isExist)return;
	m_pos.y += kShotSpeedY;

	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
}