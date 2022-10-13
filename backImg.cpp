#include "backImg.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	constexpr int scrollSpead = 2;
}
Back::Back()
{
	m_handle = LoadGraph("data/midori2.jpg");
	x = 0;
	y = 0;
}

Back::~Back()
{

}

void Back::init()
{

}

void Back::update()
{
	y += scrollSpead;
}

void Back::draw()
{
	//‚P–‡–Ú•`‰æ
	DrawGraph(x, y, m_handle, false);
	//‚Q–‡–Ú•`‰æ
	DrawGraph(x, y - Game::kScreenHight, m_handle, false);
	//‚P”Ô‰º‚Ü‚ÅƒXƒNƒ[ƒ‹‚·‚é‚Æ‰Šú’l‚É
	if (y == 480)
	{
		y = 10;
	}
}
