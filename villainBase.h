#pragma once

#include "Vec2.h"
#include "ShotBase.h"

class VillainBase
{
public:
	VillainBase();
	virtual ~VillainBase();

	void setHandle(int handle) { m_handle = handle; }

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();
	// 表示
	virtual void draw();

	//存在るするか
	bool isExist() const { return m_isExist; }
	// 情報の取得
	Vec2 getPos() const { return m_pos; }
	Vec2 getSize() const { return m_size; }

	bool isCol(ShotBase& shotBase);
	//死亡設定
	void setDead(bool isDead) { m_isDead = isDead; }

	//継承先からも使えるようになる
protected:
	// グラフィックハンドル
	int m_handle;
	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;

	Vec2 m_size;
	//存在するか
	bool    m_isExist;

	bool m_isDead;

};