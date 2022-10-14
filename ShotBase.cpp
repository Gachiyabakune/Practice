#include "ShotBase.h"
#include "DxLib.h"

namespace
{
	//�e�̃T�C�Y
	constexpr float kSizeX = 16.0f;
	constexpr float kSizeY = 16.0f;
}

ShotBase::ShotBase()
{
	m_handle = -1;
	m_pos.x = 100.0f;
	m_pos.y = 100.0f;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_isExist = false;
	m_isPlayer = false;
}

ShotBase::~ShotBase()
{

}

void ShotBase::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
}

void ShotBase::update()
{
	if (!m_isExist)return;
}
// �\��
void ShotBase::draw()
{
	//����ł�����`�悵�Ȃ�
	if (!m_isExist)return;

	//
	if (m_isPlayer)
	{
		DrawGraphF(m_pos.x + 8, m_pos.y, m_handle, true);	//�e���L�����̐^�񒆂���o��悤�ɒ���
	}
	else if (!m_isPlayer)
	{
		DrawGraphF(m_pos.x + 32, m_pos.y+64, m_handle, true);	//�e���L�����̐^�񒆂���o��悤�ɒ���
	}
	
}

