#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "enemy.h"
#include "backImg.h"
#include "villainBase.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// 初期化
	void init();
	// 終了処理
	void end();

	//void count();
	// 毎フレームの処理
	bool update();
	// 毎フレームの描画
	void draw();

	//弾の生成
	bool createShotNormal(Vec2 pos);
	bool createShotEnemy(Vec2 pos);
	bool createShotBound(Vec2 pos);
	bool createShotEnmeyRandom(Vec2 pos);

	bool createVillainFirst(Vec2 pos);

private:

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kGraphicDivNum];
	int m_hShotGraphic;
	int m_hShotGraphic1;
	int m_hEnemyGraphic;
	int m_VillainGraphic;
	
	// プレイヤー
	Player m_player;
	//敵
	Enemy m_enemy;
	//背景
	Back m_backImg;
	// ショット
	std::vector<ShotBase*> m_pShotVt;
	//
	std::vector<VillainBase*> m_villainVt;

	//サウンドハンドル
	int m_hTestSound;
	//カウント用
	int m_count;
	//残機
	int m_life;
	//討伐数
	int m_RepelNum;

	int m_frame;		//計測用の変数
	int m_hitFrame;   //無敵フレーム
};