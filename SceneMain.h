#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "enemy.h"
#include "backImg.h"
#include "villainBase.h"
#include "Vec2.h"
#include "SceneBase.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
		
	virtual ~SceneMain();

	// ������
	virtual void init();
	// �I������
	virtual void end();

	//void count();
	// ���t���[���̏���
	virtual SceneBase* update();
	// ���t���[���̕`��
	virtual void draw();

	//�e�̐���
	bool createShotNormal(Vec2 pos);
	bool createShotEnemy(Vec2 pos);
	bool createShotBound(Vec2 pos);
	bool createShotEnemy1way(Vec2 pos);
	bool createShotEnemy2way(Vec2 pos);
	bool createShotEnemy3way(Vec2 pos);

	bool createVillainFirst(Vec2 pos);

	Vec2 getPos() const { return m_pos; }
	virtual bool isEnd() { return m_isEnd; }
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

	//VillainFirst m_villain;
	// �V���b�g
	std::vector<ShotBase*> m_pShotVt;
	//�G
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

	int m_enedFrame;

	bool m_isEnd;

	Vec2 m_pos;
};