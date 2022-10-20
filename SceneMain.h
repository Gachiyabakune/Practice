#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "enemy.h"
#include "backImg.h"
#include "villainBase.h"
#include "Vec2.h"
#include "SceneBase.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
		
	virtual ~SceneMain();

	// 初期化
	virtual void init();
	// 終了処理
	virtual void end();

	//void count();
	// 毎フレームの処理
	virtual SceneBase* update();
	// 毎フレームの描画
	virtual void draw();

	//弾の生成
	bool createShotNormal(Vec2 pos);
	bool createShotEnemy(Vec2 pos);
	bool createShotBound(Vec2 pos);
	bool createShotEnemy1way(Vec2 pos);
	bool createShotEnemy2way(Vec2 pos);
	bool createShotEnemy3way(Vec2 pos);

	bool createVillainFirst(Vec2 pos);

	Vec2 getPos() const { return m_pos; }
	virtual bool isEnd() { return m_isEnd; }
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

	//VillainFirst m_villain;
	// ショット
	std::vector<ShotBase*> m_pShotVt;
	//敵
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

	int m_enedFrame;

	bool m_isEnd;

	Vec2 m_pos;
};