#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "enemy.h"
#include "backImg.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// ������
	void init();
	// �I������
	void end();

	//void count();
	// ���t���[���̏���
	bool update();
	// ���t���[���̕`��
	void draw();

	//�e�̐���
	bool createShotNormal(Vec2 pos);
	bool createShotFall(Vec2 pos);
	bool createShotBound(Vec2 pos);

private:

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kGraphicDivNum];
	int m_hShotGraphic;
	int m_hEnemyGraphic;
	
	// �v���C���[
	Player m_player;
	//�G
	Enemy m_enemy;
	ShotBase m_shotBase;
	//�w�i
	Back m_backImg;
	// �V���b�g
	std::vector<ShotBase*> m_pShotVt;
	//�T�E���h�n���h��
	int m_hTestSound;
	//�J�E���g�p
	int m_count;
	//�c�@
	int m_life;
	//������
	int m_RepelNum;

	int m_frame = 0;		//�v���p�̕ϐ�
	int m_hitFrame = 0;   //���G�t���[��
};