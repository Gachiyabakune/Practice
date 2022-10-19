#include "SceneTitle.h"
#include "SceneEnd.h"
#include "DxLib.h"
#include "SceneMain.h"

void SceneEnd::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;
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
	DrawString(0, m_textPosY, "ƒGƒ“ƒh‰æ–Ê", GetColor(255, 255, 255));
}