/*------------------------------------------------------------
	
	[Model.h]
	モデルのプール
	Author : 出合翔太

-------------------------------------------------------------*/
#pragma once
#include "Loader.h"
#include <vector>

namespace Prefabs
{
	class ModelPool final
	{
	public:
		ModelPool() = delete;
		ModelPool(class Graphics& graphics);
		~ModelPool();
		void Draw(const std::string& Tag);
		void Load(const std::string& Tag, const std::string& FileName);
		void Unload(const std::string& Tag);		
	private:
		void LoadPanzer(const std::string& Tag);
		std::unordered_map<std::string, std::unique_ptr<Model>> m_Map;
		Graphics& m_Graphics;
	};
}
