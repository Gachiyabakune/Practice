#include "DxLib.h"
#include "game.h"
#include "enemy.h"

#include "SceneMain.h"

Enemy::Enemy()
{
	m_handle = -1;
	m_pMain = nullptr;
	m_shotInterval = 0;

	m_time = 120;
	m_stopTime = 210;
	m_outTime = 600;
	count = 0;

	endFlag = false;
}

Enemy::~Enemy()
{

}

void Enemy::init()
{
	m_pos.x = 185.5f;		//画面の半分  - キャラのサイズの半分
	m_pos.y = -100;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
	m_shotInterval = 0;
}

void Enemy::update()
{
	m_count++;
	
	if (m_time < m_count && m_count < m_stopTime)
	{
		m_pos.y += 2;
	}
	else if (m_count > m_outTime)
	{
		m_pos.y -= 2;
		if (m_pos.y < -40)
		{
			endFlag = true;
		}
	}
}


void Enemy::draw()
{
	if (!endFlag)
	{
		DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
	DrawFormatString(0, 50, GetColor(255, 255, 255), "カウント数:%d", m_count);
}