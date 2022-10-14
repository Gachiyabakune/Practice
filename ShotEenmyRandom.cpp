#include "ShotEnemyRandom.h"
#include "game.h"
#include "DxLib.h"

namespace
{
	constexpr float kShotSpeed = 2.0f;

	//�O���t�B�b�N�f�[�^�̃T�C�Y
	constexpr int kSizeX = 16;
	constexpr int kSizeY = 16;
}

void ShotEnemyRandom::start(Vec2 pos)
{
	ShotBase::start(pos);

	float randAngle = static_cast<float>(GetRand(359));
	float rad = randAngle * 3.14159f / 180.0;			//���W�A���ϊ�

	m_vec.x = cosf(rad);
	m_vec.y = sinf(rad);
	m_vec *= kShotSpeed;
}

void ShotEnemyRandom::update()
{
	if (!m_isExist)return;
	m_pos += m_vec;

	//��ʊO�ɂ������V���b�g�̏I������
	if (m_pos.x > (0 - kSizeX))
	{
		m_isExist = false;
	}
	if (m_pos.x > (0 - kSizeY))
	{
		m_isExist = false;
	}

	if (m_pos.y > Game::kScreenHight)
	{
		m_isExist = false;
	}
	if (m_pos.y > Game::kScreenHight)
	{
		m_isExist = false;
	}
}