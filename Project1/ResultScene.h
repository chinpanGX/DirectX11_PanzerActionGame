/*-------------------------------------------------
	
	[ResultScene.h]
	Author : o‡ãÄ‘¾

--------------------------------------------------*/
#pragma once
#include "Scene.h"

namespace GameScene
{
	// ƒŠƒUƒ‹ƒg
	class Result final : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	private:
		void Load()override;
		void Unload()override;
	};
}
