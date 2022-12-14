#include "ShotEnemy3way.h"
#include "game.h"
#include "DxLib.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;

	//グラフィックデータのサイズ
	constexpr int kSizeX = 16;
	constexpr int kSizeY = 16;
}

void ShotEnemy3way::start(Vec2 pos)
{
	ShotBase::start(pos);

	shotCount = 0;
	
	//float randAngle = static_cast<float>(GetRand(359));
	float rad = 110  * 3.14159f / 180.0;			//ラジアン変換

	m_vec.x = cosf(rad);
	m_vec.y = sinf(rad);
	m_vec *= kShotSpeed;

	//m_vec.x = 0.0f;
	//m_vec.y = kShotSpeed;  //上方向に発射
}

void ShotEnemy3way::update()
{
	if (!m_isExist)return;

	if (shotCount <= 3)
	{
		m_pos += m_vec;
		
		//画面外に行った場合
		if (m_pos.y > 480 ||m_pos.y < 0|| m_pos.x > 460 || m_pos.x < 0)
		{
			m_isExist = false;
			shotCount++;
		}

	}
}