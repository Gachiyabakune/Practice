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
	//１枚目描画
	DrawGraph(x, y, m_handle, false);
	//２枚目描画
	DrawGraph(x, y - Game::kScreenHight, m_handle, false);
	//１番下までスクロールすると初期値に
	if (y == 480)
	{
		y = 0;
	}
}
