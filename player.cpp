#include "DxLib.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include "ShotBase.h"
#include "SceneMain.h"

namespace
{
	//�L�����N�^�[�̃T�C�Y
	constexpr float kSizeX = 32.0f;
	constexpr float kSizeY = 32.0f;

	//�V���b�g�̔��ˊԊu
	constexpr float kShotInterval = 3;
	//�����[�h����
	constexpr float kShotReload = 30;
	//�}�K�W����
	constexpr float kShotMagazine = 5;
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
	m_animeFrame = 0;
	m_isDead = false;
}

Player::~Player()
{
	
}

void Player::init()
{
	m_pos.x = (Game::kScreenWidth - 180 - kSizeX) / 2;
	m_pos.y = 430;		//�L�����̈ʒu����ʔ�̂V�F�R
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_animeNo = 0;
	m_animeFrame = 0;
	m_motion = 3;
	m_shotInterval = 0;
	m_energy = 500;
	m_count = kShotMagazine;
	m_reload = 0;

	m_size.x = kSizeX;
	m_size.y = kSizeY;
}

void Player::update()
{
	if (m_isDead) return;
	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//�V���b�g��������--------------------------------------
	m_shotInterval--;
	if (m_shotInterval < 0) m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		//���ʂ̒e
		if (padState & PAD_INPUT_1 && m_count > 0)
		{
			if (m_pMain->createShotNormal(getPos()))
			{
				m_count--;
				m_shotInterval = kShotInterval;
				//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
			}
		}
		//�e��0�ɂȂ�ƃ����[�h������------------------
		if (m_count == 0)
		{
			m_reload++;
			if (m_reload > kShotReload)
			{
				m_count = kShotMagazine;
				m_reload = 0;
			}
		}
		//----------------------------------------------

		//�o�E���h�e
		if (padState & PAD_INPUT_2 && m_energy >= 500)
		{
			if (m_pMain->createShotBound(getPos()))
			{
				m_shotInterval = kShotInterval;
				//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
			}
		}
		//���C��
		//if (padState & PAD_INPUT_3)
		//{
		//	if (m_pMain->createShotFall(getPos()))
		//	{
		//		m_shotInterval = kShotInterval;
		//		//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
		//	}
		//}
	}
	//------------------------------------------------------------

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
		if (m_pos.x > Game::kScreenWidth - kGraphicSizeX - 180)  m_pos.x = Game::kScreenWidth - kGraphicSizeX-180;	 //��ʊO�ɍs���Ȃ��悤��
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
	DrawFormatString(460, 120, GetColor(255, 255, 255), "�c��e��:%d", m_count);
	if (!m_isDead)
	{
		DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);
	}
	DrawBox(getPos().x, getPos().y, getPos().x+ kSizeX - 1, getPos().y+ kSizeX - 1, GetColor(255, 255, 255), false);
}

//�G�Ǝ����̃L�����̔���
bool Player::isCol(Enemy& enemy)
{
	float playerLeft = getPos().x;
	float playerRight = getPos().x + kSizeX;
	float playerTop = getPos().y;
	float playerBottom = getPos().y + kSizeY;

	float enemyLeft = enemy.getPos().x;
	float enemyRight = enemy.getPos().x + enemy.getSize().x;
	float enemyTop = enemy.getPos().y;
	float enemyBottom = enemy.getPos().y + enemy.getSize().y;

	if (playerLeft > enemyRight)	return false;
	if (playerRight < enemyLeft)	return false;
	if (playerTop > enemyBottom)	return false;
	if (playerBottom < enemyTop)	return false;

	return true;
}

//�����̃L�����ƓG�̒e�̔���
bool Player::isColShot(ShotBase& shotBase)
{
	float playerLeft = getPos().x- kSizeX;	//�����蔻�蒲���̂���-kSizeY
	float playerRight = getPos().x + kSizeX;
	float playerTop = getPos().y;
	float playerBottom = getPos().y + kSizeY;

	float bulletLeft = shotBase.getPos().x;
	float bulletRight = shotBase.getPos().x + shotBase.getSize().x;
	float bulletTop = shotBase.getPos().y;
	float bulletBottom = shotBase.getPos().y + shotBase.getSize().y;

	//�������̂������łȂ����
	if (shotBase.getPlayerShot())
	{
		return false;
	}

	if (playerLeft > bulletRight)	return false;
	if (playerRight < bulletLeft)	return false;
	if (playerTop > bulletBottom)	return false;
	if (playerBottom < bulletTop)	return false;

	return true;
}