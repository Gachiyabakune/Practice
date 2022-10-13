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
	if (!m_isExist)return;
	DrawGraphF(m_pos.x+8, m_pos.y, m_handle, true);	//�e���L�����̐^�񒆂���o��悤�ɒ���
}

//bool ShotBase::isCol(Enemy& enemy)
//{
//	float bulletLeft = getPos().x;
//	float bulletRight = getPos().x + kSizeX;
//	float bulletTop = getPos().y;
//	float bulletBottom = getPos().y + kSizeY;
//
//	float enemyLeft = enemy.getPos().x;
//	float enemyRight = enemy.getPos().x + enemy.getSize().x;
//	float enemyTop = enemy.getPos().y;
//	float enemyBottom = enemy.getPos().y + enemy.getSize().y;
//
//	if (bulletLeft > enemyRight)	return false;
//	if (bulletRight < enemyLeft)	return false;
//	if (bulletTop > enemyBottom)	return false;
//	if (bulletBottom < enemyTop)	return false;
//
//	return true;
//}
