#include "DxLib.h"
#include "SceneMain.h"
#include "ShotBound.h"
#include "ShotNormal.h"
#include "ShotEnemy.h"
#include "ShotEnemy3way.h"
#include "ShotEnemy1way.h"
#include "ShotEnemy2way.h"
#include "ShotEnemySideR.h"
#include "backImg.h"
#include "villainFirst.h"
#include "villainSecond.h"
#include <cassert>

#include "SceneTitle.h"
#include "SceneTest.h"
#include "SceneEnd.h"
#include "SceneGameOver.h"


namespace
{
	//ショットの発射間隔
	constexpr int kShotInterval = 16;

	//ライフ
	constexpr int kLife = 10;

	//討伐数
	constexpr int kEndNum = 3;

	//制限時間
	constexpr int kLimitTime = 1080;

	//グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/kawamoto.png";
}

SceneMain::SceneMain()
{
	/*for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}*/
	m_hShotGraphic = -1;		
	m_hShotGraphic1 = -1;
	m_hTestSound = -1;
	m_hEnemyGraphic = -1;
	m_VillainGraphic = -1;

	m_count = 0;		//スコア
	m_life = kLife;		//ライフ

	m_enedFrame = 0;	//終了フレーム
	m_frame = 0;		//キャラが復活するためのフレーム
	m_hitFrameP = 0;		//無敵時間
	m_hitFrameV = 0;
	m_RepelNum = 0;		//討伐数

	//敵の座標
	x = 188.5f;
	y = 0.0f;
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
	m_hShotGraphic1 = LoadGraph("data/shot.png");
	//敵の画像
	m_hEnemyGraphic = LoadGraph("data/kumomitu.png");
	m_VillainGraphic = LoadGraph("data/ideti.png");
	//サウンドのロード
	m_hTestSound = LoadSoundMem("sound/yone.mp3");

	for (int i = 0; i < Player::kGraphicDivNum; i++)
	{
		m_player.setHandle(i, m_hPlayerGraphic[i]);
	}
	m_player.init();
	m_player.setMain(this);
	Vec2 pos;
	for (int i = 0; i < 5; i++)
	{
		if (i <= 3)
		{
			//1体目
			if (i == 0)
			{
				pos.x = 188.5f;
				pos.y = -100.0f;
			}
			//2体目
			else if (i == 1)
			{
				pos.x = 328.5f;
				pos.y = -100.0f;
			}
			//3体目
			else if (i == 2)
			{
				pos.x = 48.5f;
				pos.y = -100.0f;
			}
			//敵クラスを呼び出し
			if (createVillainFirst(pos))
			{
			}
		}
		else
		{
			if (i == 4)
			{
				pos.x = 0.0f;
				pos.y = -100.0f;
			}
			if (createVillainSecond(pos))
			{

			}
		}
	}
}

// 終了処理
void SceneMain::end()
{
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hShotGraphic1);
	DeleteGraph(m_VillainGraphic);
	//サウンドアンロード
	DeleteSoundMem(m_hTestSound);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}

	for (auto& pVillain : m_villainVt)
	{
		assert(pVillain);

		delete pVillain;
		pVillain = nullptr;
	}

}

// 毎フレームの処理
SceneBase* SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_backImg.update();
	m_player.update();

	m_enedFrame++;
	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
	
		pShot->update();

		for (auto& pVillain : m_villainVt)
		{
			//敵の死亡判定---------------------------
			if (pVillain->isCol(*pShot))
			{
				pVillain->setDead(true);	//キャラが死亡

				if (m_hitFrameV == 0)	//1回の当たり判定時に１回しかライフは減らさない
				{
					//PlaySoundMem(m_hTestSound, DX_PLAYTYPE_NORMAL,true);
					m_RepelNum++;		//討伐数カウント
					m_count += 100;
				}
				m_hitFrameV = 10;	//無敵時間20フレーム
			}
			//------------------------------------------
		}
		
		if (m_hitFrameV != 0)	//死んでいる時
		{
			m_hitFrameV--;		//無敵フレームを減らす
		}

		//自分の弾の当たり判定-------------------------------------------

		if (m_player.isColShot(*pShot)&& m_hitFrameP == 0)	//無敵じゃないとき
		{
			//m_player.setDead(true);	//キャラが死亡
			m_life--;	//死亡時ライフを一つ減らす

			m_hitFrameP = 40;	//無敵時間20フレーム
		}

		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vectorの要素削除
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;

		//------------------------------------------------------------
	}

	if (m_hitFrameP != 0)	//死んでいる時
	{
		m_hitFrameP--;		//無敵フレームを減らす
	}
	if (true)
	{
		m_frame++;			//死んでいるとき1ずつカウント
	}
	if (m_frame == 30)		//カウントがたまるとキャラが復活
	{
		m_player.setDead(false);
		m_frame = 0;
	}

	std::vector<VillainBase*>::iterator its = m_villainVt.begin();
	//敵クラスの処理------------------------------------------------
	while(its != m_villainVt.end())
	{
		auto& pVillain = (*its);
		assert(pVillain);
		pVillain->update();

		if (m_player.isCol(*pVillain))
		{
			m_player.setDead(true);	//キャラが死亡

			if (m_hitFrameP == 0)	//1回の当たり判定時に１回しかライフは減らさない
			{
				m_life--;	//死亡時ライフを一つ減らす
			}
			m_hitFrameP = 20;	//無敵時間20フレーム
		}

		if (!pVillain->isExist())
		{
			delete pVillain;
			pVillain = nullptr;

			//vectorの要素削除
			its = m_villainVt.erase(its);
			continue;
		}
		its++;
	}
	//-------------------------------------------------------------


	//自キャラの判定-----------------------------------------------
	
	if (m_hitFrameP != 0)	//死んでいる時
	{
		m_hitFrameP--;		//無敵フレームを減らす
	}
	if (true)
	{
		m_frame++;			//死んでいるとき1ずつカウント
	}
	if (m_frame == 30)		//カウントがたまるとキャラが復活
	{
		m_player.setDead(false);
		m_frame = 0;
	}

	//オプション画面
	/*if (padState & PAD_INPUT_8)
	{
		return(new SceneTest);
	}*/

	//終了判定--------------------------------------------------
	if (m_RepelNum >= kEndNum)
	{
		return (new SceneEnd);		//条件達成すると終了画面に移る
	}

	if (m_life == 0 || m_count > kLimitTime)
	{
		return (new SceneGameOver);
	}
	return this;
}

// 毎フレームの描画
void SceneMain::draw()
{
	m_backImg.draw();
	m_player.draw();
	//m_enemy.draw();

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
	for (auto& pVillain : m_villainVt)
	{
		assert(pVillain);
		pVillain->draw();
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
	//DrawFormatString(460, 140, GetColor(255, 255, 255), "%d", m_hitFrame);
}


//弾の生成--------------------------------------------------------------
bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);

	pShot->setPlayerShot(true);		//撃っているのが敵か味方か判別
	
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemy(Vec2 pos)
{
	ShotEnemy* pShot = new ShotEnemy;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//撃っているのが敵か味方か判別

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotBound(Vec2 pos)
{
	ShotBound* pShot = new ShotBound;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);

	pShot->setPlayerShot(true);		//撃っているのが敵か味方か判別

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemy1way(Vec2 pos)
{
	ShotEnemy1way* pShot = new ShotEnemy1way;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//撃っているのが敵か味方か判別

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemy2way(Vec2 pos)
{
	ShotEnemy2way* pShot = new ShotEnemy2way;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//撃っているのが敵か味方か判別

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemy3way(Vec2 pos)
{
	ShotEnemy3way* pShot = new ShotEnemy3way;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//撃っているのが敵か味方か判別

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemySideR(Vec2 pos)
{
	ShotEnemySideR* pShot = new ShotEnemySideR;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//撃っているのが敵か味方か判別

	m_pShotVt.push_back(pShot);

	return true;
}
//-------------------------------------------------

bool SceneMain::createVillainFirst(Vec2 pos)
{
	VillainFirst* pVillain = new VillainFirst;
	pVillain->setHandle(m_hEnemyGraphic);
	pVillain->setMain(this);
	pVillain->start(pos);
	m_villainVt.push_back(pVillain);

	return true;
}

bool SceneMain::createVillainSecond(Vec2 pos)
{
	villainSecond* pVillain = new villainSecond;
	pVillain->setHandle(m_VillainGraphic);
	pVillain->setMain(this);
	pVillain->start(pos);
	m_villainVt.push_back(pVillain);

	return true;
}