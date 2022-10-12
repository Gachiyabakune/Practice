#include "backImg.h"
#include "DxLib.h"

Back::Back()
{
	m_handle = LoadGraph("data/img.jpg");
}

Back::~Back()
{

}

void Back::init()
{
	x = 0;
	y = 0;
}

void Back::update()
{

}

void Back::draw()
{
	DrawGraph(x, y, m_handle, false);
}
