#include "DxLib.h"
#include "game.h"
#include "enemy.h"
#include "shot.h"
#include "ShotBase.h"
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
	m_isDead = false;
	
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
	m_stopTime = 180;
	m_outTime = 480;	
}

void Enemy::update()
{
	m_count++;		//カウント
	
	//ゲーム開始時画面上から出現し決められた時間になるとその場所で止まる
	if (m_time < m_count && m_count < m_stopTime)
	{
		m_pos.y += 2;
	}

	if (m_count == 200 ||m_count == 203 || m_count == 206 ||
		m_count == 240 ||m_count == 243 || m_count == 246 ||
		m_count == 280 ||m_count == 283 || m_count == 286)
	{
		if (m_pMain->createShotEnemy(getPos()))
		{
		}
	}
	//決められた時間外になると画面外に消えていく
	else if (m_count > m_outTime)
	{
		m_pos.y -= 2;
		if (m_pos.y < -40)
		{
			m_isDead = true;
		}
	}
	//死んでいたら画面外に飛ばす
	if (m_isDead)
	{
		m_pos.y = -100;
	}
}


void Enemy::draw()
{
	//死んでいたら描画しない
	if (!m_isDead)
	{
		DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
	DrawFormatString(460, 20, GetColor(255, 255, 255), "カウント数:%d", m_count);
}


//当たり判定
bool Enemy::isCol(ShotBase& shotBase)
{
	float enemyLeft = getPos().x;
	float enemyRight = getPos().x + kSizeX-20;	//当たり判定調整のための+20
	float enemyTop = getPos().y;
	float enemyBottom = getPos().y + kSizeY;

	float bulletLeft = shotBase.getPos().x;
	float bulletRight = shotBase.getPos().x + shotBase.getSize().x;
	float bulletTop = shotBase.getPos().y;
	float bulletBottom = shotBase.getPos().y + shotBase.getSize().y;
	
	//自分が撃った弾の判定をもらわないために
	//弾を撃ったのがプレイヤーだったら
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