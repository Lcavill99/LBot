#include "BuildOrder.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;

void BuildOrder::buildOrder(BWAPI::UnitInterface *u)
{
	depot = Broodwar->self()->allUnitCount(UnitTypes::Terran_Supply_Depot);
	barracks = Broodwar->self()->allUnitCount(UnitTypes::Terran_Barracks);
	refinery = Broodwar->self()->allUnitCount(UnitTypes::Terran_Refinery);
	academy = Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy);
	factory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Factory);

	/*
	*
	* ZERG build order
	*
	*/
	if (Broodwar->enemy()->getRace() == Races::Zerg)
	{	
		// Build depot
		if ((depot == 0) && (Broodwar->self()->supplyUsed() >= 18 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, u->getTilePosition());
			u->build(UnitTypes::Terran_Supply_Depot, buildPosition);
		}

		// Build barracks
		if ((depot == 1 && barracks == 0) && (Broodwar->self()->supplyUsed() >= 22 && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice()))
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, u->getTilePosition());
			u->build(UnitTypes::Terran_Barracks, buildPosition);
		}

		// Build second barracks
		if ((depot == 1 && barracks == 1) && (Broodwar->self()->supplyUsed() >= 26 && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice()))
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, u->getTilePosition());
			u->build(UnitTypes::Terran_Barracks, buildPosition);
		}

		// Build second depot
		if ((depot == 1 && barracks == 2) && (Broodwar->self()->supplyUsed() >= 28 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, u->getTilePosition());
			u->build(UnitTypes::Terran_Supply_Depot, buildPosition);
		}

		// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
		if ((depot == 2 && barracks == 2 && refinery == 0) && (Broodwar->self()->supplyUsed() >= 30 && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice()))
		{
			Unitset geysers = Broodwar->getGeysers(); // Get all geysers
			Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
			TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position
			u->build(UnitTypes::Terran_Refinery, buildPosition);
		}

		// Build academy
		if ((depot == 2 && barracks == 2 && refinery == 1 && academy == 0) && (Broodwar->self()->supplyUsed() >= 36 && Broodwar->self()->minerals() >= UnitTypes::Terran_Academy.mineralPrice()))
		{
			// Find a location for academy and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Academy, u->getTilePosition());
			u->build(UnitTypes::Terran_Academy, buildPosition);
		}				
	}

   /*
	*
    * PROTOSS build order **UNFINISHED**
	*
	*/
	else if (Broodwar->enemy()->getRace() == Races::Protoss)
	{
		// Build depot
		if ((depot == 0) && (Broodwar->self()->supplyUsed() >= 18 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, u->getTilePosition());
			u->build(UnitTypes::Terran_Supply_Depot, buildPosition);
		}

		// Build barracks
		if ((depot == 1 && barracks == 0) && (Broodwar->self()->supplyUsed() >= 22 && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice()))
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, u->getTilePosition());
			u->build(UnitTypes::Terran_Barracks, buildPosition);
		}

		// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
		if ((depot == 1 && barracks == 1 && refinery == 0) && (Broodwar->self()->supplyUsed() >= 26 && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice()))
		{
			Unitset geysers = Broodwar->getGeysers(); // Get all geysers
			Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
			TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position
			u->build(UnitTypes::Terran_Refinery, buildPosition);
		}

		// Build second depot
		if ((depot == 1 && barracks == 1 && refinery == 1) && (Broodwar->self()->supplyUsed() >= 34 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, u->getTilePosition());
			u->build(UnitTypes::Terran_Supply_Depot, buildPosition);
		}

		// Build factory
		if ((depot == 2 && barracks == 1 && refinery == 1 && factory == 0) && (Broodwar->self()->minerals() == 200 && Broodwar->self()->gas() == 100))
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, u->getTilePosition());
			u->build(UnitTypes::Terran_Factory, buildPosition);
		}

		// Build second factory
		if ((depot == 2 && barracks == 1 && refinery == 1 && factory == 1) && (Broodwar->self()->minerals() == 200))
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, u->getTilePosition());
			u->build(UnitTypes::Terran_Factory, buildPosition);
		}

	}

	/*
	*
	* TERRAN build order
	*
	*/
	else
	{
		// Build depot
		if ((depot == 0) && (Broodwar->self()->supplyUsed() >= 18 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, u->getTilePosition());
			u->build(UnitTypes::Terran_Supply_Depot, buildPosition);
		}

		// Build barracks
		if ((depot == 1 && barracks == 0) && (Broodwar->self()->supplyUsed() >= 22 && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice()))
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, u->getTilePosition());
			u->build(UnitTypes::Terran_Barracks, buildPosition);
		}

		// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
		if ((depot == 1 && barracks == 1 && refinery == 0) && (Broodwar->self()->supplyUsed() >= 22 && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice()))
		{
			Unitset geysers = Broodwar->getGeysers(); // Get all geysers
			Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
			TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position
			u->build(UnitTypes::Terran_Refinery, buildPosition);
		}

		// Build second depot
		if ((depot == 1 && barracks == 1 && refinery == 1) && (Broodwar->self()->supplyUsed() >= 30 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, u->getTilePosition());
			u->build(UnitTypes::Terran_Supply_Depot, buildPosition);
		}

		// Build factory
		if ((depot == 2 && barracks == 1 && refinery == 1) && (Broodwar->self()->supplyUsed() >= 32 && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice()))
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, u->getTilePosition());
			u->build(UnitTypes::Terran_Factory, buildPosition);
		}

		// Build second factory
		if ((depot == 2 && barracks == 1 && refinery == 1 && factory == 1) && (Broodwar->self()->supplyUsed() >= 36 && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice()))
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, u->getTilePosition());
			u->build(UnitTypes::Terran_Factory, buildPosition);
		}

		// Build third depot
		if ((depot == 2 && barracks == 1 && refinery == 1 && factory == 2) && (Broodwar->self()->supplyUsed() >= 46 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, u->getTilePosition());
			u->build(UnitTypes::Terran_Supply_Depot, buildPosition);
		}

		// Build fourth depot
		if ((depot == 3 && barracks == 1 && refinery == 1 && factory == 2) && (Broodwar->self()->supplyUsed() >= 56 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, u->getTilePosition());
			u->build(UnitTypes::Terran_Supply_Depot, buildPosition);
		}
	}
}