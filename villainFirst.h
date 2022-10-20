#pragma once

#include "Vec2.h"
#include "villainBase.h"
#include "ShotBase.h"

class SceneMain;

class VillainFirst : public VillainBase
{
public:
	VillainFirst();
	virtual ~VillainFirst()
	{
	}
	//SceneMainクラスのポインタ設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	// グラフィックデータ設定
	void setHandle(int handle) { m_handle = handle; }
	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();

	virtual void draw();

	// 情報の取得
	Vec2 getPos() const { return m_pos; }
	Vec2 getSize() const { return m_size; }

	virtual bool isCol(ShotBase& shotBase);
	//死亡設定
	virtual void setDead(bool isDead) { m_isDead = isDead; }

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