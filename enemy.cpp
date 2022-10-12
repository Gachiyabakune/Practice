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
	m_pos.x = 185.5f;		//画面の半分  - キャラのサイズの半分
	m_pos.y = 200;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
	m_shotInterval = 0;
}

void Enemy::update()
{
	//ここには敵が移動してきて攻撃をする処理を入れる

}

void Enemy::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}