#include "SceneTitle.h"
#include "SceneGameOver.h"
#include "DxLib.h"
#include "SceneMain.h"

void SceneGameOver::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;
}

SceneBase* SceneGameOver::update()
{

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (padState & PAD_INPUT_3)
	{
		DxLib_End();
	}
	return this;
}

void SceneGameOver::draw()
{
	DrawString(0, m_textPosY, "ゲームオーバー", GetColor(255, 255, 255));
}