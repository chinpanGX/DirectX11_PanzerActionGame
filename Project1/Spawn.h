/*--------------------------------------------------------------
	
	[Spwan.h]
	Author : �o���đ�

	�X�|�[��������

--------------------------------------------------------------*/
#pragma once
#include "Manager.h"
#include "myLib.h"
#include <vector>

// ���X�|�[��
class Respawn final : public IManager
{
public:
	Respawn();
	~Respawn();
	void Begin()override;
	void Update(GameManager* Manager, Pawn* Pawn, int32_t Type)override;
	const bool GetResPawn() const;
private:
	std::vector<std::unique_ptr<class ISpawn>> m_Spawn;
	bool m_IsResPawn = false; // true�Ń��X�|�[������
};

class ISpawn
{
public:
	ISpawn() {}
	virtual ~ISpawn() {}
	virtual void SetSpawn() = 0;
};

// �v���C���[�̃X�|�[��
class PlayerSpawn final : public ISpawn
{
public:
	PlayerSpawn();
	~PlayerSpawn();
	void SetSpawn()override;
};

// �G�l�~�[�̃X�|�[��
class EnemySpawn final : public ISpawn
{
public:
	EnemySpawn();
	~EnemySpawn();
	 void SetSpawn()override;
};
