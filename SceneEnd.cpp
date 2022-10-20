#include "SceneTitle.h"
#include "SceneEnd.h"
#include "DxLib.h"
#include "SceneMain.h"


//namespace
//{
//	const char* const kPlayerGraphicFilename = "data/end.png";
//}

void SceneEnd::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_handle = 0;
	m_isEnd = false;

	m_handle = LoadGraph("data/end.png");
}

SceneBase* SceneEnd::update()
{

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (padState & PAD_INPUT_3)
	{
		DxLib_End();
	}
	return this;
}

void SceneEnd::draw()
{
	DrawString(0, m_textPosY, "ÉQÅ[ÉÄÉNÉäÉA", GetColor(255, 255, 255));
	DrawGraphF(0, 0, m_handle, false);
}