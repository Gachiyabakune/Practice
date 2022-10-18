#include "ShotEnemy1way.h"
#include "game.h"
#include "DxLib.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;

	//�O���t�B�b�N�f�[�^�̃T�C�Y
	constexpr int kSizeX = 16;
	constexpr int kSizeY = 16;
}

void ShotEnemy1way::start(Vec2 pos)
{
	ShotBase::start(pos);

	shotCount = 0;

	//float randAngle = static_cast<float>(GetRand(359));
	float rad = 70 * 3.14159f / 180.0;			//���W�A���ϊ�

	m_vec.x = cosf(rad);
	m_vec.y = sinf(rad);
	m_vec *= kShotSpeed;

	//m_vec.x = 0.0f;
	//m_vec.y = kShotSpeed;  //������ɔ���
}

void ShotEnemy1way::update()
{
	if (!m_isExist)return;

	if (shotCount <= 3)
	{
		m_pos += m_vec;



		//��ʊO�ɍs�����ꍇ
		if (m_pos.y > 480 || m_pos.x > 640 || m_pos.x < 0)
		{
			m_isExist = false;
			shotCount++;
		}

	}
}