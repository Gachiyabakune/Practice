#pragma once

#include "Vec2.h"
#include "enemy.h"
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

	bool isCol(Enemy& enemy);

	bool isColShot(ShotBase& shotBase);

	// ���̎擾
	Vec2 getPos() const { return m_pos; }

	//���S�ݒ�
	void setDead(bool isDead) { m_isDead = isDead; }
private:
	int m_handle[kGraphicDivNum];

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;
	//�e�������̊Ԋu
	int m_shotInterval;
	//�����[�h
	int m_reload;
	//�e��
	int m_count;
	//�L�����N�^�[�̃A�j���[�V����
	int m_animeNo;		//�\������ԍ�
	int m_animeFrame;

	int m_motion;	//�i�s����
	
	int m_energy;	//�G�i�W�[
	
	bool m_isDead;

};