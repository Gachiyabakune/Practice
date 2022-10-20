#pragma once
#include "SceneBase.h"

class SceneEnd : public SceneBase
{
public:
	SceneEnd()
	{
		m_textPosY = 0;
		m_textVecY = 0;
		m_isEnd = false;
	}
	virtual ~SceneEnd() {}


	virtual void init()override;
	virtual void end()override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	// テキスト表示位置変更
	int m_textPosY;
	int m_textVecY;

	int m_handle;

	bool m_isEnd;
};
