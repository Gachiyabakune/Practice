#include "DxLib.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include "ShotBase.h"
#include "SceneMain.h"

namespace
{
	//キャラクターのサイズ
	constexpr float kSizeX = 32.0f;
	constexpr float kSizeY = 32.0f;

	//ショットの発射間隔
	constexpr float kShotInterval = 3;
	//リロード時間
	constexpr float kShotReload = 30;
	//マガジン数
	constexpr float kShotMagazine = 5;
	//キャラクターアニメーション
	constexpr int kAnimeChangeFrame = 8;
}

Player::Player()
{
	//初期化
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	m_animeNo = 0;
	m_motion = 0;
	m_pMain = nullptr;
	m_shotInterval = 0;
	m_animeFrame = 0;
	m_isDead = false;
}

Player::~Player()
{
	
}

void Player::init()
{
	m_pos.x = (Game::kScreenWidth - 180 - kSizeX) / 2;
	m_pos.y = 430;		//キャラの位置が画面比の７：３
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_animeNo = 0;
	m_animeFrame = 0;
	m_motion = 3;
	m_shotInterval = 0;
	m_energy = 500;
	m_count = kShotMagazine;
	m_reload = 0;

	m_size.x = kSizeX;
	m_size.y = kSizeY;
}

void Player::update()
{
	if (m_isDead) return;
	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//ショットを撃つ処理--------------------------------------
	m_shotInterval--;
	if (m_shotInterval < 0) m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		//普通の弾
		if (padState & PAD_INPUT_1 && m_count > 0)
		{
			if (m_pMain->createShotNormal(getPos()))
			{
				m_count--;
				m_shotInterval = kShotInterval;
				//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
			}
		}
		//弾が0になるとリロードを挟む------------------
		if (m_count == 0)
		{
			m_reload++;
			if (m_reload > kShotReload)
			{
				m_count = kShotMagazine;
				m_reload = 0;
			}
		}
		//----------------------------------------------

		//バウンド弾
		if (padState & PAD_INPUT_2 && m_energy >= 500)
		{
			if (m_pMain->createShotBound(getPos()))
			{
				m_shotInterval = kShotInterval;
				//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
			}
		}
		//改修中
		//if (padState & PAD_INPUT_3)
		//{
		//	if (m_pMain->createShotFall(getPos()))
		//	{
		//		m_shotInterval = kShotInterval;
		//		//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
		//	}
		//}
	}
	//------------------------------------------------------------

	//キャラの移動処理---------------------------------------------
	bool isKey = false;

	//上方向
	if (padState & PAD_INPUT_UP)
	{
		m_pos.y--;
		m_motion = 3;
		isKey = true;
		if (m_pos.y < 0)   m_pos.y = 0;    //画面外に行かないように
	}
	//下方向
	if (padState & PAD_INPUT_DOWN)
	{
		m_pos.y++;
		m_motion = 0;
		isKey = true;
		if (m_pos.y > Game::kScreenHight - kGraphicSizeY)  m_pos.y = Game::kScreenHight - kGraphicSizeY;	 //画面外に行かないように
	}
	//左方向
	if (padState & PAD_INPUT_LEFT)
	{
		m_pos.x--;
		m_motion = 1;
		isKey = true;
		if (m_pos.x < 0)   m_pos.x = 0;	 //画面外に行かないように
	}
	//右方向
	if (padState & PAD_INPUT_RIGHT)
	{
		m_pos.x++;
		m_motion = 2;
		isKey = true;
		if (m_pos.x > Game::kScreenWidth - kGraphicSizeX - 180)  m_pos.x = Game::kScreenWidth - kGraphicSizeX-180;	 //画面外に行かないように
	}
	//左上方向に進むなら向きを上方向を優先する
	if (padState & PAD_INPUT_UP && padState & PAD_INPUT_RIGHT)
	{
		m_motion = 3;
	}
	//右上方向に進むなら向きを上方向を優先する
	if (padState & PAD_INPUT_UP && padState & PAD_INPUT_LEFT)
	{
		m_motion = 3;
	}

	//キャラクターのアニメーション
	if (isKey) m_animeFrame++;

	if (m_animeFrame >= kGraphicDivX * kAnimeChangeFrame)
	{
		m_animeFrame = 0;
	}

	int tempAnimeNo = m_animeFrame / kAnimeChangeFrame;
	m_animeNo = m_motion * kGraphicDivX + tempAnimeNo;
}

void Player::draw()
{
	DrawFormatString(460, 120, GetColor(255, 255, 255), "残り弾数:%d", m_count);
	if (!m_isDead)
	{
		DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);
	}
	DrawBox(getPos().x, getPos().y, getPos().x+ kSizeX - 1, getPos().y+ kSizeX - 1, GetColor(255, 255, 255), false);
}

//敵と自分のキャラの判定
bool Player::isCol(Enemy& enemy)
{
	float playerLeft = getPos().x;
	float playerRight = getPos().x + kSizeX;
	float playerTop = getPos().y;
	float playerBottom = getPos().y + kSizeY;

	float enemyLeft = enemy.getPos().x;
	float enemyRight = enemy.getPos().x + enemy.getSize().x;
	float enemyTop = enemy.getPos().y;
	float enemyBottom = enemy.getPos().y + enemy.getSize().y;

	if (playerLeft > enemyRight)	return false;
	if (playerRight < enemyLeft)	return false;
	if (playerTop > enemyBottom)	return false;
	if (playerBottom < enemyTop)	return false;

	return true;
}

//自分のキャラと敵の弾の判定
bool Player::isColShot(ShotBase& shotBase)
{
	float playerLeft = getPos().x- kSizeX;	//当たり判定調整のため-kSizeY
	float playerRight = getPos().x + kSizeX;
	float playerTop = getPos().y;
	float playerBottom = getPos().y + kSizeY;

	float bulletLeft = shotBase.getPos().x;
	float bulletRight = shotBase.getPos().x + shotBase.getSize().x;
	float bulletTop = shotBase.getPos().y;
	float bulletBottom = shotBase.getPos().y + shotBase.getSize().y;

	//撃ったのが自分でなければ
	if (shotBase.getPlayerShot())
	{
		return false;
	}

	if (playerLeft > bulletRight)	return false;
	if (playerRight < bulletLeft)	return false;
	if (playerTop > bulletBottom)	return false;
	if (playerBottom < bulletTop)	return false;

	return true;
}