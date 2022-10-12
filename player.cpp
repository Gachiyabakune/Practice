#include "DxLib.h"
#include "game.h"
#include "player.h"

#include "SceneMain.h"

namespace
{
	//ショットの発射間隔
	constexpr float kShotInterval = 16;

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
}

Player::~Player()
{
	
}

void Player::init()
{
	m_pos.x = Game::kScreenWidth / 2 - kGraphicSizeX / 2;
	m_pos.y = 574;		//キャラの位置が画面比の７：３
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_animeNo = 0;
	m_animeFrame = 0;
	m_motion = 3;
	m_shotInterval = 0;
}

void Player::update()
{
	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//ショットを撃つ処理
	m_shotInterval--;
	if (m_shotInterval < 0)m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		//普通の弾
		if (padState & PAD_INPUT_1)
		{
			if (m_pMain->createShotNormal(getPos()))
			{
				m_shotInterval = kShotInterval;
				//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
			}
		}
		//バウンド弾
		if (padState & PAD_INPUT_2)
		{
			if (m_pMain->createShotBound(getPos()))
			{
				m_shotInterval = kShotInterval;
				//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
			}
		}
		//改修中
//		if (padState & PAD_INPUT_3)
//		{
//			if (m_pMain->createShotFall(getPos()))
//			{
//				m_shotInterval = kShotInterval;
////				PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
//			}
//		}
	}

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
		if (m_pos.x > Game::kScreenWidth - kGraphicSizeX)  m_pos.x = Game::kScreenWidth - kGraphicSizeX;	 //画面外に行かないように
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
	//DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);
}