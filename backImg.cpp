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
	//�P���ڕ`��
	DrawGraph(x, y, m_handle, false);
	//�Q���ڕ`��
	DrawGraph(x, y - Game::kScreenHight, m_handle, false);
	//�P�ԉ��܂ŃX�N���[������Ə����l��
	if (y == 480)
	{
		y = 10;
	}
}
