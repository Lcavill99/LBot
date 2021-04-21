/*
 *
 * Handles all research logic
 *
 */
#include "Research.h"

using namespace BWAPI;

void Research::research(BWAPI::Unit u)
{
	//** ACADEMY **//
	if (u->getType() == UnitTypes::Terran_Academy)
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
}