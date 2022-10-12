#pragma once

class SceneMain;

class Back
{
private:
	//座標
	double x, y;

	//グラフィックハンドル
	int m_handle;
	
public:
	Back();
	virtual ~Back();

	void init();

	void update();

	void draw();
};
