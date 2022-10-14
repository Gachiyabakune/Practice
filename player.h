#pragma once

#include "Vec2.h"
#include "enemy.h"
class SceneMain;

class Player
{
public:
	//定数定義

	//グラフィックデータ分割数
	static constexpr int kGraphicDivX = 3;
	static constexpr int kGraphicDivY = 4;
	static constexpr int kGraphicDivNum = kGraphicDivX * kGraphicDivY;
	//グラフィックデータサイズ
	static constexpr int kGraphicSizeX = 32;
	static constexpr int kGraphicSizeY = 32;

public:
	Player();
	virtual ~Player();

	// グラフィックデータ設定
	void setHandle(int index,int handle) { m_handle[index] = handle; }

	// プレイヤーの初期化
	void init();

	//SceneMainクラスのポインタ設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// 処理
	void update();
	// 描画
	void draw();

	bool isCol(Enemy& enemy);

	bool isColShot(ShotBase& shotBase);

	// 情報の取得
	Vec2 getPos() const { return m_pos; }

	//死亡設定
	void setDead(bool isDead) { m_isDead = isDead; }
private:
	int m_handle[kGraphicDivNum];

	//SceneMainのポインタ
	SceneMain* m_pMain;

	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;
	//弾を撃つ時の間隔
	int m_shotInterval;
	//リロード
	int m_reload;
	//弾数
	int m_count;
	//キャラクターのアニメーション
	int m_animeNo;		//表示する番号
	int m_animeFrame;

	int m_motion;	//進行方向
	
	int m_energy;	//エナジー
	
	bool m_isDead;

};