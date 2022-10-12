#pragma once

#include "Vec2.h"

class SceneMain;

class Player
{
public:
	//�萔��`

	//�O���t�B�b�N�f�[�^������
	static constexpr int kGraphicDivX = 3;
	static constexpr int kGraphicDivY = 4;
	static constexpr int kGraphicDivNum = kGraphicDivX * kGraphicDivY;
	//�O���t�B�b�N�f�[�^�T�C�Y
	static constexpr int kGraphicSizeX = 32;
	static constexpr int kGraphicSizeY = 32;

public:
	Player();
	virtual ~Player();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int index,int handle) { m_handle[index] = handle; }

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

private:
	int m_handle[kGraphicDivNum];

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;

	int m_shotInterval;

	//�L�����N�^�[�̃A�j���[�V����
	int m_animeNo;		//�\������ԍ�
	int m_animeFrame;

	int m_motion;	//�i�s����
};