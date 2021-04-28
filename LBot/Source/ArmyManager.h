#pragma once
#include <BWAPI.h>

class ArmyManager
{

public:
	void ArmyManager::addUnit(BWAPI::Unitset set, BWAPI::Unit u);
	void ArmyManager::removeUnit(BWAPI::Unitset set, BWAPI::Unit u);
	void ArmyManager::unitAttack(BWAPI::Unit u);
	void ArmyManager::groupAttack(BWAPI::Unitset set);
};