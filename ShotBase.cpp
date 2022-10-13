#include "ShotBase.h"
#include "DxLib.h"

namespace
{
		
}

ShotBase::ShotBase()
{
	m_handle = -1;
	m_pos.x = 100.0f;
	m_pos.y = 100.0f;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_isExist = false;
}

ShotBase::~ShotBase()
{

}

void ShotBase::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
}

void ShotBase::update()
{
	if (!m_isExist)return;
}
// 表示
void ShotBase::draw()
{
	if (!m_isExist)return;
	DrawGraphF(m_pos.x+8, m_pos.y, m_handle, true);	//弾がキャラの真ん中から出るように調整
}
