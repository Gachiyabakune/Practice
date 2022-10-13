#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "enemy.h"
#include "backImg.h"

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
	bool createShotFall(Vec2 pos);
	bool createShotBound(Vec2 pos);

private:

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kGraphicDivNum];
	int m_hShotGraphic;
	int m_hEnemyGraphic;
	
	// プレイヤー
	Player m_player;
	//敵
	Enemy m_enemy;
	//背景
	Back m_backImg;
	// ショット
	std::vector<ShotBase*> m_pShotVt;
	//サウンドハンドル
	int m_hTestSound;
	//カウント用
	int m_count;
	//残機
	int m_life;
	
	int m_frame = 0;		//計測用の変数
	int m_hitFrame = 0;   //無敵フレーム
};