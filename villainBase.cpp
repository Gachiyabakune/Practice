#include "villainBase.h"
#include "DxLib.h"

namespace
{
	//敵のサイズ
	//修正--------------------------------------------
	constexpr float kSizeX = 64.0;
	constexpr float kSizeY = 64.0;
	//-----------------------------------------------------
}

VillainBase::VillainBase()
{
	m_handle = -1;
	m_pos.x = 100.0f;
	m_pos.y = 100.0f;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_isExist = false;
}

VillainBase::~VillainBase()
{

}

void VillainBase::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
}

void VillainBase::update()
{
	if (!m_isExist)return;
}

// 表示
void VillainBase::draw()
{
	if (!m_isExist)return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);	
}

