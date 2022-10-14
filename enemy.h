#pragma once

#include "Vec2.h"
#include "ShotBase.h"

class SceneMain;

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) { m_handle = handle; }

	// �v���C���[�̏�����
	void init();

	//SceneMain�N���X�̃|�C���^�ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// ����
	void update();
	// �`��
	void draw();

	// ���̎擾
	Vec2 getPos() const { return m_pos; }
	Vec2 getSize() const { return m_size; }

	bool isCol(ShotBase& shotBase);
	//���S�ݒ�
	void setDead(bool isDead) { m_isDead = isDead; }
private:
	int m_handle;

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �\���ʒu
	Vec2 m_pos;
	//
	Vec2 m_size;
	// �ړ�
	Vec2 m_vec;

	//int m_shotInterval;
	//�G���o�����Ă���̃J�E���g
	int m_count;
	//�o���A��~�A�A��
	int m_time, m_stopTime, m_outTime;

	bool m_isDead;
};