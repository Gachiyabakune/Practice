#pragma once

#include "Vec2.h"
//#include "enemy.h"

class ShotBase
{
public:
	ShotBase();
	virtual ~ShotBase();

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

	void setPlayerShot(bool isPlayer) {m_isPlayer = isPlayer;}	//撃っているのが敵か味方か
	bool getPlayerShot() const {return m_isPlayer; }			

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
	bool m_isExist;

	bool m_isPlayer;

};