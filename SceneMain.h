#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "enemy.h"
#include "backImg.h"
#include "villainBase.h"

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
	bool createShotEnemy(Vec2 pos);
	bool createShotBound(Vec2 pos);
	bool createShotEnmeyRandom(Vec2 pos);

	bool createVillainFirst(Vec2 pos);

private:

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kGraphicDivNum];
	int m_hShotGraphic;
	int m_hShotGraphic1;
	int m_hEnemyGraphic;
	int m_VillainGraphic;
	
	// �v���C���[
	Player m_player;
	//�G
	Enemy m_enemy;
	//�w�i
	Back m_backImg;
	// �V���b�g
	std::vector<ShotBase*> m_pShotVt;
	//
	std::vector<VillainBase*> m_villainVt;

	//�T�E���h�n���h��
	int m_hTestSound;
	//�J�E���g�p
	int m_count;
	//�c�@
	int m_life;
	//������
	int m_RepelNum;

	int m_frame;		//�v���p�̕ϐ�
	int m_hitFrame;   //���G�t���[��
};