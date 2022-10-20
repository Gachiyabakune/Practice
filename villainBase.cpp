#include "villainBase.h"
#include "DxLib.h"

namespace
{
	//敵のサイズ
	//修正--------------------------------------------
	constexpr float kSizeX = 89.0f;
	constexpr float kSizeY = 89.0f;
	//-----------------------------------------------------
}

VillainBase::VillainBase()
{
	m_handle = -1;
	//m_pos.x = 185.5f;		//画面の半分  - キャラのサイズの半分
	//m_pos.y = -100;
	m_pos.x = 0;
	m_pos.y = 0;
 
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_isExist = false;
	m_isDead = false;

	m_size.x = kSizeX;
	m_size.y = kSizeY;
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
	if (!m_isDead)return;
}

// 表示
void VillainBase::draw()
{
	if (!m_isDead)return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);	
}

//当たり判定
bool VillainBase::isCol(ShotBase& shotBase)
{
	float enemyLeft = getPos().x;
	float enemyRight = getPos().x + kSizeX - 20;	//当たり判定調整のための+20
	float enemyTop = getPos().y;
	float enemyBottom = getPos().y + kSizeY;

	float bulletLeft = shotBase.getPos().x;
	float bulletRight = shotBase.getPos().x + shotBase.getSize().x;
	float bulletTop = shotBase.getPos().y;
	float bulletBottom = shotBase.getPos().y + shotBase.getSize().y;

	//自分が撃った弾の判定をもらわないために
	//弾を撃ったのがプレイヤーだったら
	if (!shotBase.getPlayerShot())
	{
		return false;
	}

	if (enemyLeft > bulletRight)	return false;
	if (enemyRight < bulletLeft)	return false;
	if (enemyTop > bulletBottom)	return false;
	if (enemyBottom < bulletTop)	return false;

	return true;
}

