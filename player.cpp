#include "DxLib.h"
#include "game.h"
#include "player.h"

#include "SceneMain.h"

namespace
{
	//�V���b�g�̔��ˊԊu
	constexpr float kShotInterval = 16;

	//�L�����N�^�[�A�j���[�V����
	constexpr int kAnimeChangeFrame = 8;
}

Player::Player()
{
	//������
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	m_animeNo = 0;
	m_motion = 0;
	m_pMain = nullptr;
	m_shotInterval = 0;
}

Player::~Player()
{
	
}

void Player::init()
{
	m_pos.x = Game::kScreenWidth / 2 - kGraphicSizeX / 2;
	m_pos.y = 574;		//�L�����̈ʒu����ʔ�̂V�F�R
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_animeNo = 0;
	m_animeFrame = 0;
	m_motion = 3;
	m_shotInterval = 0;
}

void Player::update()
{
	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//�V���b�g��������
	m_shotInterval--;
	if (m_shotInterval < 0)m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		//���ʂ̒e
		if (padState & PAD_INPUT_1)
		{
			if (m_pMain->createShotNormal(getPos()))
			{
				m_shotInterval = kShotInterval;
				//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
			}
		}
		//�o�E���h�e
		if (padState & PAD_INPUT_2)
		{
			if (m_pMain->createShotBound(getPos()))
			{
				m_shotInterval = kShotInterval;
				//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
			}
		}
		//���C��
//		if (padState & PAD_INPUT_3)
//		{
//			if (m_pMain->createShotFall(getPos()))
//			{
//				m_shotInterval = kShotInterval;
////				PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
//			}
//		}
	}

	//�L�����̈ړ�����---------------------------------------------
	bool isKey = false;

	//�����
	if (padState & PAD_INPUT_UP)
	{
		m_pos.y--;
		m_motion = 3;
		isKey = true;
		if (m_pos.y < 0)   m_pos.y = 0;    //��ʊO�ɍs���Ȃ��悤��
	}
	//������
	if (padState & PAD_INPUT_DOWN)
	{
		m_pos.y++;
		m_motion = 0;
		isKey = true;
		if (m_pos.y > Game::kScreenHight - kGraphicSizeY)  m_pos.y = Game::kScreenHight - kGraphicSizeY;	 //��ʊO�ɍs���Ȃ��悤��
	}
	//������
	if (padState & PAD_INPUT_LEFT)
	{
		m_pos.x--;
		m_motion = 1;
		isKey = true;
		if (m_pos.x < 0)   m_pos.x = 0;	 //��ʊO�ɍs���Ȃ��悤��
	}
	//�E����
	if (padState & PAD_INPUT_RIGHT)
	{
		m_pos.x++;
		m_motion = 2;
		isKey = true;
		if (m_pos.x > Game::kScreenWidth - kGraphicSizeX)  m_pos.x = Game::kScreenWidth - kGraphicSizeX;	 //��ʊO�ɍs���Ȃ��悤��
	}
	//��������ɐi�ނȂ�������������D�悷��
	if (padState & PAD_INPUT_UP && padState & PAD_INPUT_RIGHT)
	{
		m_motion = 3;
	}
	//�E������ɐi�ނȂ�������������D�悷��
	if (padState & PAD_INPUT_UP && padState & PAD_INPUT_LEFT)
	{
		m_motion = 3;
	}
	//�L�����N�^�[�̃A�j���[�V����
	if (isKey) m_animeFrame++;

	if (m_animeFrame >= kGraphicDivX * kAnimeChangeFrame)
	{
		m_animeFrame = 0;
	}

	int tempAnimeNo = m_animeFrame / kAnimeChangeFrame;
	m_animeNo = m_motion * kGraphicDivX + tempAnimeNo;
}

void Player::draw()
{
	//DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);
}