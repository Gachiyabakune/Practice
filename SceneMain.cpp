#include "DxLib.h"
#include "SceneMain.h"
#include "ShotBound.h"
#include "ShotNormal.h"
#include "ShotEnemy.h"
#include "ShotEnemy3way.h"
#include "ShotEnemy1way.h"
#include "ShotEnemy2way.h"
#include "ShotEnemySideR.h"
#include "backImg.h"
#include "villainFirst.h"
#include "villainSecond.h"
#include <cassert>

#include "SceneTitle.h"
#include "SceneTest.h"
#include "SceneEnd.h"
#include "SceneGameOver.h"


namespace
{
	//�V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;

	//���C�t
	constexpr int kLife = 10;

	//������
	constexpr int kEndNum = 3;

	//��������
	constexpr int kLimitTime = 1080;

	//�O���t�B�b�N�t�@�C����
	const char* const kPlayerGraphicFilename = "data/kawamoto.png";
}

SceneMain::SceneMain()
{
	/*for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}*/
	m_hShotGraphic = -1;		
	m_hShotGraphic1 = -1;
	m_hTestSound = -1;
	m_hEnemyGraphic = -1;
	m_VillainGraphic = -1;

	m_count = 0;		//�X�R�A
	m_life = kLife;		//���C�t

	m_enedFrame = 0;	//�I���t���[��
	m_frame = 0;		//�L�������������邽�߂̃t���[��
	m_hitFrameP = 0;		//���G����
	m_hitFrameV = 0;
	m_RepelNum = 0;		//������

	//�G�̍��W
	x = 188.5f;
	y = 0.0f;
}

SceneMain::~SceneMain()
{

}

// ������
void SceneMain::init()
{
	LoadDivGraph(kPlayerGraphicFilename, Player::kGraphicDivNum,
		Player::kGraphicDivX, Player::kGraphicDivY,
		Player::kGraphicSizeX, Player::kGraphicSizeY, m_hPlayerGraphic);

	//�e�̉摜
	m_hShotGraphic = LoadGraph("data/ice.png");
	m_hShotGraphic1 = LoadGraph("data/shot.png");
	//�G�̉摜
	m_hEnemyGraphic = LoadGraph("data/kumomitu.png");
	m_VillainGraphic = LoadGraph("data/ideti.png");
	//�T�E���h�̃��[�h
	m_hTestSound = LoadSoundMem("sound/yone.mp3");

	for (int i = 0; i < Player::kGraphicDivNum; i++)
	{
		m_player.setHandle(i, m_hPlayerGraphic[i]);
	}
	m_player.init();
	m_player.setMain(this);
	Vec2 pos;
	for (int i = 0; i < 5; i++)
	{
		if (i <= 3)
		{
			//1�̖�
			if (i == 0)
			{
				pos.x = 188.5f;
				pos.y = -100.0f;
			}
			//2�̖�
			else if (i == 1)
			{
				pos.x = 328.5f;
				pos.y = -100.0f;
			}
			//3�̖�
			else if (i == 2)
			{
				pos.x = 48.5f;
				pos.y = -100.0f;
			}
			//�G�N���X���Ăяo��
			if (createVillainFirst(pos))
			{
			}
		}
		else
		{
			if (i == 4)
			{
				pos.x = 0.0f;
				pos.y = -100.0f;
			}
			if (createVillainSecond(pos))
			{

			}
		}
	}
}

// �I������
void SceneMain::end()
{
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hShotGraphic1);
	DeleteGraph(m_VillainGraphic);
	//�T�E���h�A�����[�h
	DeleteSoundMem(m_hTestSound);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}

	for (auto& pVillain : m_villainVt)
	{
		assert(pVillain);

		delete pVillain;
		pVillain = nullptr;
	}

}

// ���t���[���̏���
SceneBase* SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_backImg.update();
	m_player.update();

	m_enedFrame++;
	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
	
		pShot->update();

		for (auto& pVillain : m_villainVt)
		{
			//�G�̎��S����---------------------------
			if (pVillain->isCol(*pShot))
			{
				pVillain->setDead(true);	//�L���������S

				if (m_hitFrameV == 0)	//1��̓����蔻�莞�ɂP�񂵂����C�t�͌��炳�Ȃ�
				{
					//PlaySoundMem(m_hTestSound, DX_PLAYTYPE_NORMAL,true);
					m_RepelNum++;		//�������J�E���g
					m_count += 100;
				}
				m_hitFrameV = 10;	//���G����20�t���[��
			}
			//------------------------------------------
		}
		
		if (m_hitFrameV != 0)	//����ł��鎞
		{
			m_hitFrameV--;		//���G�t���[�������炷
		}

		//�����̒e�̓����蔻��-------------------------------------------

		if (m_player.isColShot(*pShot)&& m_hitFrameP == 0)	//���G����Ȃ��Ƃ�
		{
			//m_player.setDead(true);	//�L���������S
			m_life--;	//���S�����C�t������炷

			m_hitFrameP = 40;	//���G����20�t���[��
		}

		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vector�̗v�f�폜
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;

		//------------------------------------------------------------
	}

	if (m_hitFrameP != 0)	//����ł��鎞
	{
		m_hitFrameP--;		//���G�t���[�������炷
	}
	if (true)
	{
		m_frame++;			//����ł���Ƃ�1���J�E���g
	}
	if (m_frame == 30)		//�J�E���g�����܂�ƃL����������
	{
		m_player.setDead(false);
		m_frame = 0;
	}

	std::vector<VillainBase*>::iterator its = m_villainVt.begin();
	//�G�N���X�̏���------------------------------------------------
	while(its != m_villainVt.end())
	{
		auto& pVillain = (*its);
		assert(pVillain);
		pVillain->update();

		if (m_player.isCol(*pVillain))
		{
			m_player.setDead(true);	//�L���������S

			if (m_hitFrameP == 0)	//1��̓����蔻�莞�ɂP�񂵂����C�t�͌��炳�Ȃ�
			{
				m_life--;	//���S�����C�t������炷
			}
			m_hitFrameP = 20;	//���G����20�t���[��
		}

		if (!pVillain->isExist())
		{
			delete pVillain;
			pVillain = nullptr;

			//vector�̗v�f�폜
			its = m_villainVt.erase(its);
			continue;
		}
		its++;
	}
	//-------------------------------------------------------------


	//���L�����̔���-----------------------------------------------
	
	if (m_hitFrameP != 0)	//����ł��鎞
	{
		m_hitFrameP--;		//���G�t���[�������炷
	}
	if (true)
	{
		m_frame++;			//����ł���Ƃ�1���J�E���g
	}
	if (m_frame == 30)		//�J�E���g�����܂�ƃL����������
	{
		m_player.setDead(false);
		m_frame = 0;
	}

	//�I�v�V�������
	/*if (padState & PAD_INPUT_8)
	{
		return(new SceneTest);
	}*/

	//�I������--------------------------------------------------
	if (m_RepelNum >= kEndNum)
	{
		return (new SceneEnd);		//�����B������ƏI����ʂɈڂ�
	}

	if (m_life == 0 || m_count > kLimitTime)
	{
		return (new SceneGameOver);
	}
	return this;
}

// ���t���[���̕`��
void SceneMain::draw()
{
	m_backImg.draw();
	m_player.draw();
	//m_enemy.draw();

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
	for (auto& pVillain : m_villainVt)
	{
		assert(pVillain);
		pVillain->draw();
	}
	//���ݑ��݂��Ă���e�̐���\��
	DrawFormatString(460, 0, GetColor(255, 255, 255), "�e�̐�:%d", m_pShotVt.size());
	//
	DrawFormatString(460, 40, GetColor(255, 255, 255), "������:%d", m_RepelNum);
	//
	DrawFormatString(460, 60, GetColor(255, 255, 255), "SCORE:%d", m_count);
	//
	DrawFormatString(460, 80, GetColor(255, 255, 255), "LIFE:%d", m_life);
	//
	DrawFormatString(460, 100, GetColor(255, 255, 255), "ENERGY:%d", m_count);
	//DrawFormatString(460, 140, GetColor(255, 255, 255), "%d", m_hitFrame);
}


//�e�̐���--------------------------------------------------------------
bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);

	pShot->setPlayerShot(true);		//�����Ă���̂��G������������
	
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemy(Vec2 pos)
{
	ShotEnemy* pShot = new ShotEnemy;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//�����Ă���̂��G������������

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotBound(Vec2 pos)
{
	ShotBound* pShot = new ShotBound;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);

	pShot->setPlayerShot(true);		//�����Ă���̂��G������������

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemy1way(Vec2 pos)
{
	ShotEnemy1way* pShot = new ShotEnemy1way;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//�����Ă���̂��G������������

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemy2way(Vec2 pos)
{
	ShotEnemy2way* pShot = new ShotEnemy2way;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//�����Ă���̂��G������������

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemy3way(Vec2 pos)
{
	ShotEnemy3way* pShot = new ShotEnemy3way;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//�����Ă���̂��G������������

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemySideR(Vec2 pos)
{
	ShotEnemySideR* pShot = new ShotEnemySideR;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//�����Ă���̂��G������������

	m_pShotVt.push_back(pShot);

	return true;
}
//-------------------------------------------------

bool SceneMain::createVillainFirst(Vec2 pos)
{
	VillainFirst* pVillain = new VillainFirst;
	pVillain->setHandle(m_hEnemyGraphic);
	pVillain->setMain(this);
	pVillain->start(pos);
	m_villainVt.push_back(pVillain);

	return true;
}

bool SceneMain::createVillainSecond(Vec2 pos)
{
	villainSecond* pVillain = new villainSecond;
	pVillain->setHandle(m_VillainGraphic);
	pVillain->setMain(this);
	pVillain->start(pos);
	m_villainVt.push_back(pVillain);

	return true;
}