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
	//m_vec.y = kShotSpeed;  //下方向に発射

	//m_pos.x = 400;
	//m_pos.y = -100;

	m_pos.x = 185.5f;		//画面の半分  - キャラのサイズの半分
	m_pos.y = -100;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_time = 120;
	m_stopTime = 180;
	m_outTime = 480;
}

void VillainFirst::update()
{
	//死んでいたら画面外に飛ばす
	if (m_isDead)
	{
		m_pos.y = -1000;
		return;
	}

	if (m_isDead) return;

	m_count++;		//カウント

	//ゲーム開始時画面上から出現し決められた時間になるとその場所で止まる
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
	//決められた時間外になると画面外に消えていく
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
	//死んでいたら描画しない
	if (!m_isDead)
	{
		DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
	DrawFormatString(460, 20, GetColor(255, 255, 255), "カウント数:%d", m_count);
}

//当たり判定
bool VillainFirst::isCol(ShotBase& shotBase)
{
	float enemyLeft = getPos().x;
	float enemyRight = getPos().x + kSizeX - 20;	//当たり判定調整のための+20
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