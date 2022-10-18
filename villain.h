#pragma once

#include "Vec2.h"

class Villain
{
public:
	Villain();
	virtual ~Villain();

	void setHandle(int handle) { m_handle = handle; }

	//�V���b�g�J�n
	void start(Vec2 pos);

	// �X�V
	void update();
	// �\��
	void draw();

	//���݂邷�邩
	bool isExist() const { return m_isExist; }

	Vec2 getPos() const { return m_pos; }
	Vec2 getSize() const { return m_size; }

private:
	// �O���t�B�b�N�n���h��
	int m_handle;
	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;

	Vec2 m_size;
	//���݂��邩
	bool    m_isExist;
};