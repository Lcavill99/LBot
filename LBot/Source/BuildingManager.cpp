/*
 *
 * Handles all building logic
 *
 */
#include "buildingManager.h"

using namespace BWAPI;

/*
 * Recruit units
 */
void BuildingManager::recruitUnit(BWAPI::Unit u)
{
	
}

/*
 * Research tech
 */
void BuildingManager::researchTech(BWAPI::Unit u)
{
	if (!u->isResearching() && !u->isUpgrading())
	{
		if (u->canResearch(TechTypes::Stim_Packs) && Broodwar->self()->minerals() >= TechTypes::Stim_Packs.mineralPrice() && Broodwar->self()->gas() >= TechTypes::Stim_Packs.gasPrice())
		{
			u->research(TechTypes::Stim_Packs);
		}
		if (u->canResearch(TechTypes::Restoration) && Broodwar->self()->minerals() >= TechTypes::Restoration.mineralPrice() && Broodwar->self()->gas() >= TechTypes::Restoration.gasPrice())
		{
			u->research(TechTypes::Restoration);
		}
		if (u->canResearch(TechTypes::Optical_Flare) && Broodwar->self()->minerals() >= TechTypes::Optical_Flare.mineralPrice() && Broodwar->self()->gas() >= TechTypes::Optical_Flare.gasPrice())
		{
			u->research(TechTypes::Optical_Flare);
		}
		if (u->canUpgrade(UpgradeTypes::U_238_Shells) && Broodwar->self()->minerals() >= UpgradeTypes::U_238_Shells.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::U_238_Shells.gasPrice())
		{
			u->upgrade(UpgradeTypes::U_238_Shells);
		}
		if (u->canUpgrade(UpgradeTypes::Caduceus_Reactor) && Broodwar->self()->minerals() >= UpgradeTypes::Caduceus_Reactor.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Caduceus_Reactor.gasPrice())
		{
			u->upgrade(UpgradeTypes::Caduceus_Reactor);
		}
	}	
}