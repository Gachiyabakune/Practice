#pragma once

#include "Vec2.h"
#include "ShotBase.h"

class SceneMain;

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	// グラフィックデータ設定
	void setHandle(int handle) { m_handle = handle; }

	// プレイヤーの初期化
	void init();

	//SceneMainクラスのポインタ設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// 処理
	void update();
	// 描画
	void draw();

	// 情報の取得
	Vec2 getPos() const { return m_pos; }
	Vec2 getSize() const { return m_size; }

	bool isCol(ShotBase& shotBase);
	//死亡設定
	void setDead(bool isDead) { m_isDead = isDead; }
private:
	int m_handle;

	//SceneMainのポインタ
	SceneMain* m_pMain;

	// 表示位置
	Vec2 m_pos;
	//
	Vec2 m_size;
	// 移動
	Vec2 m_vec;

	//int m_shotInterval;
	//敵が出現してからのカウント
	int m_count;
	//出現、停止、帰還
	int m_time, m_stopTime, m_outTime;

	bool m_isDead;
};