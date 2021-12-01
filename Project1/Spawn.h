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
	void Update(GameManager* manager, Pawn* pawn, int32_t Type)override;
	const bool GetRespawn() const;
private:
	std::vector<std::unique_ptr<class ISpawn>> m_Spawn;
	bool m_IsRespawn = false; // true�Ń��X�|�[������
};

class ISpawn
{
public:
	ISpawn() = delete;
	ISpawn(const D3DXVECTOR3& pos) : m_SpawnPoint(pos) {}
	virtual ~ISpawn() {}
	virtual void SetSpawn() = 0;
protected:
	const D3DXVECTOR3& GetSpawnPoint() const { return m_SpawnPoint; }
private:
	D3DXVECTOR3 m_SpawnPoint;
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
