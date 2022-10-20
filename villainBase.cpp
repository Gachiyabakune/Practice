#include "villainBase.h"
#include "DxLib.h"

namespace
{
	//“G‚ÌƒTƒCƒY
	//C³--------------------------------------------
	constexpr float kSizeX = 89.0f;
	constexpr float kSizeY = 89.0f;
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

// •\Ž¦
void VillainBase::draw()
{
	if (!m_isDead)return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);	
}

//“–‚½‚è”»’è
bool VillainBase::isCol(ShotBase& shotBase)
{
	float enemyLeft = getPos().x;
	float enemyRight = getPos().x + kSizeX - 20;	//“–‚½‚è”»’è’²®‚Ì‚½‚ß‚Ì+20
	float enemyTop = getPos().y;
	float enemyBottom = getPos().y + kSizeY;

	float bulletLeft = shotBase.getPos().x;
	float bulletRight = shotBase.getPos().x + shotBase.getSize().x;
	float bulletTop = shotBase.getPos().y;
	float bulletBottom = shotBase.getPos().y + shotBase.getSize().y;

	//Ž©•ª‚ªŒ‚‚Á‚½’e‚Ì”»’è‚ð‚à‚ç‚í‚È‚¢‚½‚ß‚É
	//’e‚ðŒ‚‚Á‚½‚Ì‚ªƒvƒŒƒCƒ„[‚¾‚Á‚½‚ç
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

