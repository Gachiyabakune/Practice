#include "DxLib.h"
#include "SceneMain.h"
#include "ShotBound.h"
#include "ShotNormal.h"
#include "ShotFall.h"
#include "enemy.h"
#include "backImg.h"
#include <cassert>

namespace
{
	//ショットの発射間隔
	constexpr int kShotInterval = 16;

	//ライフ
	constexpr int kLife = 3;

	//グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/kawamoto.png";
}

SceneMain::SceneMain()
{
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}
	m_hShotGraphic = -1;
	m_hTestSound = -1;
	m_hEnemyGraphic = -1;
	m_count = 0;
	m_life = kLife;

	m_frame = 0;	
	m_hitFrame = 0;
	m_RepelNum = 0;
}

SceneMain::~SceneMain()
{

}

// 初期化
void SceneMain::init()
{
	LoadDivGraph(kPlayerGraphicFilename, Player::kGraphicDivNum,
		Player::kGraphicDivX, Player::kGraphicDivY,
		Player::kGraphicSizeX, Player::kGraphicSizeY, m_hPlayerGraphic);

	//弾の画像
	m_hShotGraphic = LoadGraph("data/ice.png");
	//敵の画像
	m_hEnemyGraphic = LoadGraph("data/kumomitu.png");
	//サウンドのロード
	m_hTestSound = LoadSoundMem("sound/cursor0.mp3");

	//m_player.setHandle(m_hPlayerGraphic);
	for (int i = 0; i < Player::kGraphicDivNum; i++)
	{
		m_player.setHandle(i, m_hPlayerGraphic[i]);
	}
	m_player.init();
	m_player.setMain(this);

	m_enemy.setHandle(m_hEnemyGraphic);
	m_enemy.init();
	m_enemy.setMain(this);
}

// 終了処理
void SceneMain::end()
{
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
		m_RepelNum++;
	}
	//グラフィックアンロード
//	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hShotGraphic);
	//サウンドアンロード
	DeleteSoundMem(m_hTestSound);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}
}

// 毎フレームの処理
bool SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if(padState & PAD_INPUT_1)
	{
		PlaySoundMem(m_hTestSound, DX_PLAYTYPE_BACK, true);
	}

	m_backImg.update();
	m_player.update();
	m_enemy.update();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
		pShot->update()
			;
		//敵の死亡判定---------------------------
		if (m_enemy.isCol(*pShot))
		{
			m_enemy.setDead(true);	//キャラが死亡

			if (m_hitFrame == 0)	//1回の当たり判定時に１回しかライフは減らさない
			{
				PlaySoundFile("sound/atotyotto.mp3", DX_PLAYTYPE_NORMAL);
				m_RepelNum++;
			}
			m_hitFrame = 20;	//無敵時間20フレーム

			if (m_hitFrame != 0)	//死んでいる時
			{
				m_hitFrame--;		//無敵フレームを減らす
			}
		}
		//----------------------------------------

		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vectorの要素削除
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}
	if (m_player.isCol(m_enemy))
	{
		m_player.setDead(true);	//キャラが死亡

		if (m_hitFrame == 0)	//1回の当たり判定時に１回しかライフは減らさない
		{
			m_life--;	//死亡時ライフを一つ減らす
		}
		m_hitFrame = 20;	//無敵時間20フレーム
	}
	if (m_hitFrame != 0)	//死んでいる時
	{
		m_hitFrame--;		//無敵フレームを減らす
	}
	if (true)
	{
		m_frame++;			//死んでいるとき1ずつカウント
	}
	if (m_frame == 300)		//カウントがたまるとキャラが復活
	{
		//m_player.setDead(false);
		m_frame = 0;
	}

	


	return false;
}

// 毎フレームの描画
void SceneMain::draw()
{
	m_backImg.draw();
	m_player.draw();
	m_enemy.draw();

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
	//現在存在している弾の数を表示
	DrawFormatString(460, 0, GetColor(255, 255, 255), "弾の数:%d", m_pShotVt.size());
	//
	DrawFormatString(460, 40, GetColor(255, 255, 255), "討伐数:%d", m_RepelNum);
	//
	DrawFormatString(460, 60, GetColor(255, 255, 255), "SCORE:%d", m_count);
	//
	DrawFormatString(460, 80, GetColor(255, 255, 255), "LIFE:%d", m_life);
	//
	DrawFormatString(460, 100, GetColor(255, 255, 255), "ENERGY:%d", m_count);
}

bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotFall(Vec2 pos)
{
	ShotFall* pShot = new ShotFall;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotBound(Vec2 pos)
{
	ShotBound* pShot = new ShotBound;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}