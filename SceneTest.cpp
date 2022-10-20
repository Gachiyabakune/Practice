#include "SceneTitle.h"
#include "SceneTest.h"
#include "DxLib.h"
#include "SceneMain.h"

void SceneTest::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;
}

SceneBase* SceneTest::update()
{

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	
	if (padState & PAD_INPUT_1)
	{
		return (new SceneMain);
	}
	return this;
}

void SceneTest::draw()
{
	DrawString(0, m_textPosY, "���[������", GetColor(255, 255, 255));
	DrawString(0, m_textPosY+20, "�G��3�̓|��", GetColor(255, 255, 255));
	DrawString(0, m_textPosY+40, "�������Ԃ��؂�邩�A���C�t���Ȃ��Ȃ�ƃQ�[���I�[�o�[", GetColor(255, 255, 255));
}