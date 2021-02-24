#include "BuildOrder.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;

void BuildOrder::buildOrder(BWAPI::Unitset workers)
{
	depot = Broodwar->self()->allUnitCount(UnitTypes::Terran_Supply_Depot);
	barracks = Broodwar->self()->allUnitCount(UnitTypes::Terran_Barracks);
	refinery = Broodwar->self()->allUnitCount(UnitTypes::Terran_Refinery);
	academy = Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy);
	factory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Factory);
	static int lastChecked = 0;

	/*
	*
	* ZERG build order
	*
	*/
	if (Broodwar->enemy()->getRace() == Races::Zerg)
	{	
		// Build depot
		if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastChecked + 300 < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
		{
			lastChecked = Broodwar->getFrameCount();

			Unit worker = workers.getClosestUnit(IsIdle || IsGatheringMinerals);

			// If worker is found
			if (worker)
			{
				// Find a location for depot
				TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, worker->getTilePosition());

				// If build position is found
				if (buildPosition)
				{
					// Build
					worker->build(UnitTypes::Terran_Supply_Depot, buildPosition);

					// Register an event that draws the target build location
					Broodwar->registerEvent([buildPosition, worker](Game*)
					{
						Broodwar->drawBoxMap(Position(buildPosition),
							Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
							Colors::Blue);
					},
						nullptr,  // condition
						UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
				}
			}						
		}

		// Build barracks
		if (barracks == 0 && Broodwar->self()->supplyUsed() >= 22 && lastChecked + 300 < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
		{
			lastChecked = Broodwar->getFrameCount();

			Unit worker = workers.getClosestUnit(IsIdle || IsGatheringMinerals);

			// If worker is found
			if (worker)
			{
				// Find a location for barracks
				TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, worker->getTilePosition());

				// If build position is found
				if (buildPosition)
				{
					//Build
					worker->build(UnitTypes::Terran_Barracks, buildPosition);

					// Register an event that draws the target build location
					Broodwar->registerEvent([buildPosition, worker](Game*)
					{
						Broodwar->drawBoxMap(Position(buildPosition),
							Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
							Colors::Blue);
					},
						nullptr,  // condition
						UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
				}
			}
		}

		// Build second barracks
		if (barracks == 1 && Broodwar->self()->supplyUsed() >= 26 && lastChecked + 300 < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
		{
			lastChecked = Broodwar->getFrameCount();

			Unit worker = workers.getClosestUnit(IsIdle || IsGatheringMinerals);

			// If worker is found
			if (worker)
			{
				// Find a location for barracks
				TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, worker->getTilePosition());

				// If build position is found
				if (buildPosition)
				{
					// Build
					worker->build(UnitTypes::Terran_Barracks, buildPosition);

					// Register an event that draws the target build location
					Broodwar->registerEvent([buildPosition, worker](Game*)
					{
						Broodwar->drawBoxMap(Position(buildPosition),
							Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
							Colors::Blue);
					},
						nullptr,  // condition
						UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
				}
			}
		}

		// Build second depot
		if (depot == 1 && Broodwar->self()->supplyUsed() >= 28 && lastChecked + 300 < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
		{
			lastChecked = Broodwar->getFrameCount();

			Unit worker = workers.getClosestUnit(IsIdle || IsGatheringMinerals);

			// If worker is found
			if (worker)
			{
				// Find a location for depot
				TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, worker->getTilePosition());

				// If build position is found
				if (buildPosition)
				{
					// Build
					worker->build(UnitTypes::Terran_Supply_Depot, buildPosition);

					// Register an event that draws the target build location
					Broodwar->registerEvent([buildPosition, worker](Game*)
					{
						Broodwar->drawBoxMap(Position(buildPosition),
							Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
							Colors::Blue);
					},
						nullptr,  // condition
						UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
				}
			}
		}

		// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
		if (refinery == 0 && Broodwar->self()->supplyUsed() >= 30 && lastChecked + 300 < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice())
		{
			lastChecked = Broodwar->getFrameCount();

			Unit worker = workers.getClosestUnit(IsIdle || IsGatheringMinerals);

			// If worker is found
			if (worker)
			{
				Unitset geysers = Broodwar->getGeysers(); // Get all geysers
				Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
				TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position

				// If build position is found
				if (buildPosition)
				{
					// Build 
					worker->build(UnitTypes::Terran_Refinery, buildPosition);

					// Register an event that draws the target build location
					Broodwar->registerEvent([buildPosition, worker](Game*)
					{
						Broodwar->drawBoxMap(Position(buildPosition),
							Position(buildPosition + UnitTypes::Terran_Refinery.tileSize()),
							Colors::Blue);
					},
						nullptr,  // condition
						UnitTypes::Terran_Refinery.buildTime() + 100);  // frames to run
				}
			}
		}

		// Build academy
		if (academy == 0 && Broodwar->self()->supplyUsed() >= 36 && lastChecked + 300 < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Academy.mineralPrice())
		{
			lastChecked = Broodwar->getFrameCount();

			Unit worker = workers.getClosestUnit(IsIdle || IsGatheringMinerals);

			// If worker is found
			if (worker)
			{
				// Find a location for academy
				TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Academy, worker->getTilePosition());

				// If build position is found
				if (buildPosition)
				{
					// Build
					worker->build(UnitTypes::Terran_Academy, buildPosition);

					// Register an event that draws the target build location
					Broodwar->registerEvent([buildPosition, worker](Game*)
					{
						Broodwar->drawBoxMap(Position(buildPosition),
							Position(buildPosition + UnitTypes::Terran_Academy.tileSize()),
							Colors::Blue);
					},
						nullptr,  // condition
						UnitTypes::Terran_Academy.buildTime() + 100);  // frames to run
				}
			}
		}				
	}

 //  /*
	//*
 //   * PROTOSS build order **UNFINISHED**
	//*
	//*/
	//else if (Broodwar->enemy()->getRace() == Races::Protoss)
	//{
	//	// Build depot
	//	if ((depot == 0) && (Broodwar->self()->supplyUsed() >= 18 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
	//	{
	//		// Find a location for depot and construct it
	//		TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, worker->getTilePosition());
	//		worker->build(UnitTypes::Terran_Supply_Depot, buildPosition);
	//	}

	//	// Build barracks
	//	if ((depot == 1 && barracks == 0) && (Broodwar->self()->supplyUsed() >= 22 && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice()))
	//	{
	//		// Find a location for barracks and construct it
	//		TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, worker->getTilePosition());
	//		worker->build(UnitTypes::Terran_Barracks, buildPosition);
	//	}

	//	// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
	//	if ((depot == 1 && barracks == 1 && refinery == 0) && (Broodwar->self()->supplyUsed() >= 26 && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice()))
	//	{
	//		Unitset geysers = Broodwar->getGeysers(); // Get all geysers
	//		Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
	//		TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position
	//		worker->build(UnitTypes::Terran_Refinery, buildPosition);
	//	}

	//	// Build second depot
	//	if ((depot == 1 && barracks == 1 && refinery == 1) && (Broodwar->self()->supplyUsed() >= 34 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
	//	{
	//		// Find a location for depot and construct it
	//		TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, worker->getTilePosition());
	//		worker->build(UnitTypes::Terran_Supply_Depot, buildPosition);
	//	}

	//	// Build factory
	//	if ((depot == 2 && barracks == 1 && refinery == 1 && factory == 0) && (Broodwar->self()->minerals() == 200 && Broodwar->self()->gas() == 100))
	//	{
	//		// Find a location for barracks and construct it
	//		TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, worker->getTilePosition());
	//		worker->build(UnitTypes::Terran_Factory, buildPosition);
	//	}

	//	// Build second factory
	//	if ((depot == 2 && barracks == 1 && refinery == 1 && factory == 1) && (Broodwar->self()->minerals() == 200))
	//	{
	//		// Find a location for barracks and construct it
	//		TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, worker->getTilePosition());
	//		worker->build(UnitTypes::Terran_Factory, buildPosition);
	//	}

	//}

	///*
	//*
	//* TERRAN build order
	//*
	//*/
	//else
	//{
	//	// Build depot
	//	if ((depot == 0) && (Broodwar->self()->supplyUsed() >= 18 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
	//	{
	//		// Find a location for depot and construct it
	//		TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, worker->getTilePosition());
	//		worker->build(UnitTypes::Terran_Supply_Depot, buildPosition);
	//	}

	//	// Build barracks
	//	if ((depot == 1 && barracks == 0) && (Broodwar->self()->supplyUsed() >= 22 && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice()))
	//	{
	//		// Find a location for barracks and construct it
	//		TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, worker->getTilePosition());
	//		worker->build(UnitTypes::Terran_Barracks, buildPosition);
	//	}

	//	// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
	//	if ((depot == 1 && barracks == 1 && refinery == 0) && (Broodwar->self()->supplyUsed() >= 22 && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice()))
	//	{
	//		Unitset geysers = Broodwar->getGeysers(); // Get all geysers
	//		Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
	//		TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position
	//		worker->build(UnitTypes::Terran_Refinery, buildPosition);
	//	}

	//	// Build second depot
	//	if ((depot == 1 && barracks == 1 && refinery == 1) && (Broodwar->self()->supplyUsed() >= 30 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
	//	{
	//		// Find a location for depot and construct it
	//		TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, worker->getTilePosition());
	//		worker->build(UnitTypes::Terran_Supply_Depot, buildPosition);
	//	}

	//	// Build factory
	//	if ((depot == 2 && barracks == 1 && refinery == 1) && (Broodwar->self()->supplyUsed() >= 32 && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice()))
	//	{
	//		// Find a location for barracks and construct it
	//		TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, worker->getTilePosition());
	//		worker->build(UnitTypes::Terran_Factory, buildPosition);
	//	}

	//	// Build second factory
	//	if ((depot == 2 && barracks == 1 && refinery == 1 && factory == 1) && (Broodwar->self()->supplyUsed() >= 36 && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice()))
	//	{
	//		// Find a location for barracks and construct it
	//		TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, worker->getTilePosition());
	//		worker->build(UnitTypes::Terran_Factory, buildPosition);
	//	}

	//	// Build third depot
	//	if ((depot == 2 && barracks == 1 && refinery == 1 && factory == 2) && (Broodwar->self()->supplyUsed() >= 46 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
	//	{
	//		// Find a location for depot and construct it
	//		TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, worker->getTilePosition());
	//		worker->build(UnitTypes::Terran_Supply_Depot, buildPosition);
	//	}

	//	// Build fourth depot
	//	if ((depot == 3 && barracks == 1 && refinery == 1 && factory == 2) && (Broodwar->self()->supplyUsed() >= 56 && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice()))
	//	{
	//		// Find a location for depot and construct it
	//		TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, worker->getTilePosition());
	//		worker->build(UnitTypes::Terran_Supply_Depot, buildPosition);
	//	}
	//}
}