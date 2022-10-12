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

	// 毎フレームの処理
	void update();
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
};