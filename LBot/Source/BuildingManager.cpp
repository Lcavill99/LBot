/*
 *
 * Handles all building logic
 *
 */
#include "buildingManager.h"

using namespace BWAPI;

/*
 * Add unit to Unitset
 */
void BuildingManager::addUnit(BWAPI::Unitset set, BWAPI::Unit u)
{
	set.insert(u);
}

/*
 * Remove unit from unitset
 */
void BuildingManager::removeUnit(BWAPI::Unitset set, BWAPI::Unit u)
{
	set.erase(u);
}

/*
 * Recruit units
 */
void BuildingManager::recruitUnit(BWAPI::Unit u)
{
	if (u->isIdle() && !u->train(UnitTypes::Terran_Medic))
	{
		// If that fails, draw the error at the location so that you can visibly see what went wrong!
		// However, drawing the error once will only appear for a single frame
		// so create an event that keeps it on the screen for some frames
		Position pos = u->getPosition();
		Error lastErr = Broodwar->getLastError();
		Broodwar->registerEvent([pos, lastErr](Game*)
		{
			Broodwar->drawTextMap(pos, "%c%s", Text::White, lastErr.c_str());
		},   // action
			nullptr,    // condition
			Broodwar->getLatencyFrames());  // frames to run
	}
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