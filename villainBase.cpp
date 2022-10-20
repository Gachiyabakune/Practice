#include "villainBase.h"
#include "DxLib.h"

namespace
{
	//�G�̃T�C�Y
	//�C��--------------------------------------------
	constexpr float kSizeX = 89.0f;
	constexpr float kSizeY = 89.0f;
	//-----------------------------------------------------
}

VillainBase::VillainBase()
{
	m_handle = -1;
	//m_pos.x = 185.5f;		//��ʂ̔���  - �L�����̃T�C�Y�̔���
	//m_pos.y = -100;
	m_pos.x = 0;
	m_pos.y = 0;
 
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_isExist = false;
	m_isDead = false;

	m_size.x = kSizeX;
	m_size.y = kSizeY;
}

VillainBase::~VillainBase()
{

}

void VillainBase::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
}

void VillainBase::update()
{
	if (!m_isDead)return;
}

// �\��
void VillainBase::draw()
{
	if (!m_isDead)return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);	
}

//�����蔻��
bool VillainBase::isCol(ShotBase& shotBase)
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

