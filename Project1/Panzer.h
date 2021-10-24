/*------------------------------------------------------------

	[vehicle.h]
	Author : 出合翔太

	戦車を構成するクラス

-------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include "Status.h"
#include <string>

class Body;
class Turret;
class MainGun;
class Panzer final : public Actor
{
public:
	Panzer() = delete;
	Panzer(const std::string& PanzerTag);
	~Panzer();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	
	// Setter&&Getter
	// パーツ
	const Body& GetBody() const;
	const Turret& GetTurret() const;
	const MainGun& GetMainGun() const;
private:
	// 戦車のパーツ
	std::unique_ptr<Body> m_Body;
	std::unique_ptr<Turret> m_Turret;
	std::unique_ptr<MainGun> m_Gun;
	class Resource& m_Resource;
	class Graphics& m_Graphics;
};

