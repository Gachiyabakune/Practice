#include "ShotBound.h"
#include "game.h"
#include "DxLib.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;

	//跳ね返り回数
	constexpr int kBoundMax = 1;

	//グラフィックデータのサイズ
	constexpr int kSizeX = 16;
	constexpr int kSizeY = 16;
}

void ShotBound::start(Vec2 pos)
{
	ShotBase::start(pos);

	float randAngle = static_cast<float>(GetRand(179));
	float rad = randAngle * 3.14159f / 180.0;			//ラジアン変換

	m_vec.x = cosf(rad);
	m_vec.y = sinf(rad);
	m_vec *= kShotSpeed;

	m_boundCount = 0;
}

void ShotBound::update()
{
	if (!m_isExist)return;
	m_pos -= m_vec;
}