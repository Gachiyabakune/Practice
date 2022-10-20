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

	//死亡設定
	virtual void setDeads(bool isDead) { m_isDead = isDead; }

private:
	//SceneMainのポインタ
	SceneMain* m_pMain;
	//int m_shotInterval;
	//敵が出現してからのカウント
	int m_count;
	//出現、停止、帰還
	int m_time, m_stopTime, m_outTime;
};