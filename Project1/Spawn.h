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
class ResPawn final : public IManager
{
public:
	ResPawn();
	~ResPawn();
	void Begin()override;
	void Update(GameManager* Manager, Pawn* Pawn, int32_t Type)override;
	const bool GetResPawn() const;
private:
	std::vector<std::unique_ptr<class ISPawn>> m_SPawn;
	bool m_IsResPawn = false; // true�Ń��X�|�[������
};

class ISPawn
{
public:
	ISPawn() {}
	virtual ~ISPawn() {}
	virtual void SetSPawn() = 0;
};

// �v���C���[�̃X�|�[��
class PlayerSPawn final : public ISPawn
{
public:
	PlayerSPawn();
	~PlayerSPawn();
	void SetSPawn()override;
};

// �G�l�~�[�̃X�|�[��
class EnemySPawn final : public ISPawn
{
public:
	EnemySPawn();
	~EnemySPawn();
	 void SetSPawn()override;
};
