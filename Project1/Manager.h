/*--------------------------------------------------------------

	[AudioManager.h]
	Author : 出合翔太

	管理クラスの基底クラス

----------------------------------------------------------------*/
#pragma once
#include <stdint.h>
#include <memory>
#include <string>

class GameManager;
class Pawn;
class IManager
{
public:
	virtual ~IManager() {};
	virtual void Update(GameManager* manager, Pawn* pawn, int32_t Type) = 0;
};

