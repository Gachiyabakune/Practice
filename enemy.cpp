#include "DxLib.h"
#include "game.h"
#include "enemy.h"

#include "SceneMain.h"

namespace
{
	constexpr float kSizeX = 89.0f;
	constexpr float kSizeY = 89.0f;
}
Enemy::Enemy()
{
	m_handle = -1;
	m_pMain = nullptr;
	m_count = 0;
	endFlag = false;
	
	m_size.x = kSizeX;
	m_size.y = kSizeY;
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
	//m_shotInterval = 0;

	m_time = 120;
	m_stopTime = 210;
	m_outTime = 600;
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
	DrawFormatString(460, 20, GetColor(255, 255, 255), "カウント数:%d", m_count);
}