#include "villainFirst.h"
#include "game.h"
#include "DxLib.h"
#include "shot.h"
#include "ShotBase.h"
#include "SceneMain.h"

namespace
{
	constexpr float kSizeX = 89.0f;
	constexpr float kSizeY = 89.0f;
}

VillainFirst::VillainFirst()
{
	m_handle = -1;
	m_pMain = nullptr;
	m_count = 0;
	m_isDead = false;

	m_size.x = kSizeX;
	m_size.y = kSizeY;
}

void VillainFirst::start(Vec2 pos)
{
	VillainBase::start(pos);

	//m_vec.x = 0.0f;
	//m_vec.y = kShotSpeed;  //�������ɔ���

	//m_pos.x = 400;
	//m_pos.y = -100;

	m_pos.x = 185.5f;		//��ʂ̔���  - �L�����̃T�C�Y�̔���
	m_pos.y = -100;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_time = 120;
	m_stopTime = 180;
	m_outTime = 480;
}

void VillainFirst::update()
{
	//����ł������ʊO�ɔ�΂�
	if (m_isDead)
	{
		m_pos.y = -1000;
		return;
	}

	if (m_isDead) return;

	m_count++;		//�J�E���g

	//�Q�[���J�n����ʏォ��o�������߂�ꂽ���ԂɂȂ�Ƃ��̏ꏊ�Ŏ~�܂�
	if (m_time < m_count && m_count < m_stopTime)
	{
		m_pos.y += 2;
	}

	if (m_count == 200 || m_count == 203 || m_count == 206 ||
		m_count == 260 || m_count == 263 || m_count == 266 ||
		m_count == 320 || m_count == 323 || m_count == 326)
	{
		if (m_pMain->createShotEnemy1way(getPos()))
		{
		}
		if (m_pMain->createShotEnemy2way(getPos()))
		{
		}
		if (m_pMain->createShotEnemy3way(getPos()))
		{
		}
	}
	//���߂�ꂽ���ԊO�ɂȂ�Ɖ�ʊO�ɏ����Ă���
	else if (m_count > m_outTime)
	{
		m_pos.y -= 2;
		if (m_pos.y < -40)
		{
			m_isDead = true;
		}
	}
}

void VillainFirst::draw()
{
	//����ł�����`�悵�Ȃ�
	if (!m_isDead)
	{
		DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
	DrawFormatString(460, 20, GetColor(255, 255, 255), "�J�E���g��:%d", m_count);
}

//�����蔻��
bool VillainFirst::isCol(ShotBase& shotBase)
{
	float enemyLeft = getPos().x;
	float enemyRight = getPos().x + kSizeX - 20;	//�����蔻�蒲���̂��߂�+20
	float enemyTop = getPos().y;
	float enemyBottom = getPos().y + kSizeY;

	float bulletLeft = shotBase.getPos().x;
	float bulletRight = shotBase.getPos().x + shotBase.getSize().x;
	float bulletTop = shotBase.getPos().y;
	float bulletBottom = shotBase.getPos().y + shotBase.getSize().y;

	//�������������e�̔���������Ȃ����߂�
	//�e���������̂��v���C���[��������
	if (!shotBase.getPlayerShot())
	{
		return false;
	}

	if (enemyLeft > bulletRight)	return false;
	if (enemyRight < bulletLeft)	return false;
	if (enemyTop > bulletBottom)	return false;
	if (enemyBottom < bulletTop)	return false;

	return true;
}