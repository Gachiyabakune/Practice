#include "DxLib.h"
#include "game.h"
#include "enemy.h"

#include "SceneMain.h"

Enemy::Enemy()
{
	m_handle = -1;
	m_pMain = nullptr;
	m_shotInterval = 0;
}

Enemy::~Enemy()
{

}

void Enemy::init()
{
	m_pos.x = 185.5f;		//��ʂ̔���  - �L�����̃T�C�Y�̔���
	m_pos.y = 200;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
	m_shotInterval = 0;
}

void Enemy::update()
{
	//�����ɂ͓G���ړ����Ă��čU�������鏈��������

}

void Enemy::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}