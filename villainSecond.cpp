#include "villainSecond.h"
#include "game.h"
#include "DxLib.h"
#include "shot.h"
#include "ShotBase.h"
#include "SceneMain.h"

namespace
{
	constexpr float kSizeX = 48.0f;
	constexpr float kSizeY = 48.0f;
}

villainSecond::villainSecond()
{
	m_handle = -1;
	m_pMain = nullptr;
	m_count = 0;
	m_isDead = false;

	m_size.x = kSizeX;
	m_size.y = kSizeY;
}

void villainSecond::start(Vec2 pos)
{
	VillainBase::start(pos);

	m_time = 1000;
}

void villainSecond::update()
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
	if (m_count > 180)
	{
		m_pos.y += 2;
	}

	//���̊Ԋu�Ō���
	if (m_count == 200 || m_count == 203 || m_count == 206 ||
		m_count == 260 || m_count == 263 || m_count == 266 ||
		m_count == 320 || m_count == 323 || m_count == 326 ||

		m_count == 420 || m_count == 423 || m_count == 426 ||
		m_count == 480 || m_count == 483 || m_count == 486 ||
		m_count == 540 || m_count == 543 || m_count == 546 ||

		m_count == 640 || m_count == 643 || m_count == 646 ||
		m_count == 700 || m_count == 703 || m_count == 706 ||
		m_count == 760 || m_count == 763 || m_count == 766)
	{
		if (m_pMain->createShotEnemySideR(getPos()))
		{
		}
	}

	//�͈͊O�ɂȂ�Ə�����
	if (m_pos.y > 480 + kSizeY)
	{
		m_isDead = true;
	}
}

void villainSecond::draw()
{
	//����ł�����`�悵�Ȃ�
	if (!m_isDead)
	{
		DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
}
