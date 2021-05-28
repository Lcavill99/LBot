/*
 *
 * Handles all building logic
 *
 */
#include "buildingManager.h"

using namespace BWAPI;
using namespace Filter;

/*
 * Recruit units
 */
void BuildingManager::recruitUnit(BWAPI::Unit u)
{
}

/*
 * vs Zerg building order and management
 */
void BuildingManager::zergBuildings(BWAPI::Unitset set)
{
	depot = Broodwar->self()->allUnitCount(UnitTypes::Terran_Supply_Depot);
	barracks = Broodwar->self()->allUnitCount(UnitTypes::Terran_Barracks);
	refinery = Broodwar->self()->allUnitCount(UnitTypes::Terran_Refinery);
	academy = Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy);
	factory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Factory);
	armory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Armory);

	static int lastChecked = 0;
	static int movetime = 200;
	static bool scouting = false;

	workerManager = new WorkerManager;
	scoutManager = new ScoutManager;

	BWAPI::TilePosition base = Broodwar->self()->getStartLocation();

	/*
	 * Supply management
	 */
	 // If supply count is at cap, build a supply depot to continue progression
	if ((Broodwar->self()->supplyUsed() == Broodwar->self()->supplyTotal()) && lastChecked + 100 < Broodwar->getFrameCount() && Broodwar->self()->incompleteUnitCount(UnitTypes::Terran_Supply_Depot) == 0)
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorkerFromSet(set);

		// If worker is found
		if (builder)
		{
			// Find a location for depot
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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
		
	// Build depot
	if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorkerFromSet(set);

		// If worker is found
		if (builder)
		{
			// Find a location for depot
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base, 30);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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
	if (barracks == 0 && Broodwar->self()->supplyUsed() >= 22 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorkerFromSet(set);

		// If worker is found
		if (builder)
		{
			// Find a location for barracks
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, base, 30);

			// If build position is found
			if (buildPosition)
			{
				//Build
				builder->build(UnitTypes::Terran_Barracks, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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
	if (barracks == 1 && Broodwar->self()->supplyUsed() >= 26 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorkerFromSet(set);

		// If worker is found
		if (builder)
		{
			// Find a location for barracks
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, base, 30);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Barracks, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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
	if (depot == 1 && Broodwar->self()->supplyUsed() >= 28 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorkerFromSet(set);

		// If worker is found
		if (builder)
		{
			// Find a location for depot
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base, 30);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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
	if (refinery == 0 && Broodwar->self()->supplyUsed() >= 30 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice() && Broodwar->self()->incompleteUnitCount(UnitTypes::Terran_Refinery) == 0)
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorkerFromSet(set);

		// If worker is found
		if (builder)
		{
			Unitset geysers = Broodwar->getGeysers(); // Get all geysers
			Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
			TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position

			// If build position is found
			if (buildPosition)
			{
				// Build 
				builder->build(UnitTypes::Terran_Refinery, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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
	if (academy == 0 && Broodwar->self()->supplyUsed() >= 36 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Academy.mineralPrice() && Broodwar->self()->incompleteUnitCount(UnitTypes::Terran_Academy) == 0)
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorkerFromSet(set);

		// If worker is found
		if (builder)
		{
			// Find a location for academy
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Academy, base, 40);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Academy, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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

	// Expand

	// Build factory
	if (academy == 1 && factory == 0 && Broodwar->self()->supplyUsed() >= 68 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice() && Broodwar->self()->gas() >= UnitTypes::Terran_Factory.gasPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorkerFromSet(set);

		// If worker is found
		if (builder)
		{
			// Find a location for academy
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, base, 40);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Factory, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
				{
					Broodwar->drawBoxMap(Position(buildPosition),
						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
						Colors::Blue);
				},
					nullptr,  // condition
					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
			}
		}
	}	

	// Armoury
	if (factory == 1 && armory == 0 && Broodwar->self()->supplyUsed() >= 68 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Armory.mineralPrice() && Broodwar->self()->gas() >= UnitTypes::Terran_Armory.gasPrice() && Broodwar->self()->incompleteUnitCount(UnitTypes::Terran_Armory) == 0)
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorkerFromSet(set);

		// If worker is found
		if (builder)
		{
			// Find a location for academy
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Armory, base, 40);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Armory, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
				{
					Broodwar->drawBoxMap(Position(buildPosition),
						Position(buildPosition + UnitTypes::Terran_Armory.tileSize()),
						Colors::Blue);
				},
					nullptr,  // condition
					UnitTypes::Terran_Armory.buildTime() + 100);  // frames to run
			}
		}
	}
	// Build factory
	if (factory == 1 && Broodwar->self()->supplyUsed() >= 120 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice() && Broodwar->self()->gas() >= UnitTypes::Terran_Factory.gasPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorkerFromSet(set);

		// If worker is found
		if (builder)
		{
			// Find a location for academy
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, base, 40);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Factory, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
				{
					Broodwar->drawBoxMap(Position(buildPosition),
						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
						Colors::Blue);
				},
					nullptr,  // condition
					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
			}
		}
	}

	// Build barracks 3
	if (barracks == 2 && Broodwar->self()->supplyUsed() >= 120 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorkerFromSet(set);

		// If worker is found
		if (builder)
		{
			// Find a location for barracks
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, base, 60);

			// If build position is found
			if (buildPosition)
			{
				//Build
				builder->build(UnitTypes::Terran_Barracks, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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

	// Build barracks 4
	if (barracks == 3 && Broodwar->self()->supplyUsed() >= 120 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorkerFromSet(set);

		// If worker is found
		if (builder)
		{
			// Find a location for barracks
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, base, 60);

			// If build position is found
			if (buildPosition)
			{
				//Build
				builder->build(UnitTypes::Terran_Barracks, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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
}

/*
 * vs Protoss building order and management
 */
void BuildingManager::protossBuildings()
{
	depot = Broodwar->self()->allUnitCount(UnitTypes::Terran_Supply_Depot);
	barracks = Broodwar->self()->allUnitCount(UnitTypes::Terran_Barracks);
	refinery = Broodwar->self()->allUnitCount(UnitTypes::Terran_Refinery);
	academy = Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy);
	factory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Factory);
	armory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Armory);

	static int lastChecked = 0;
	static int movetime = 150;
	static bool scouting = false;

	workerManager = new WorkerManager;
	scoutManager = new ScoutManager;

	// Build depot
	if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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
	if (barracks == 0 && Broodwar->self()->supplyUsed() >= 22 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Barracks, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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

	// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
	if (refinery == 0 && Broodwar->self()->supplyUsed() >= 26 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			Unitset geysers = Broodwar->getGeysers(); // Get all geysers
			Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
			TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Refinery, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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

	// Build second depot
	if (depot == 1 && Broodwar->self()->supplyUsed() >= 34 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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

	// Build factory
	if (factory == 0 && depot == 2 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= 200 && Broodwar->self()->gas() >= 100)
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Factory, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
				{
					Broodwar->drawBoxMap(Position(buildPosition),
						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
						Colors::Blue);
				},
					nullptr,  // condition
					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
			}
		}
	}

	// Build third depot
	if (factory == 1 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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

	// Build second factory
	if (factory == 1 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice() && Broodwar->self()->gas() >= UnitTypes::Terran_Factory.gasPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Factory, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
				{
					Broodwar->drawBoxMap(Position(buildPosition),
						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
						Colors::Blue);
				},
					nullptr,  // condition
					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
			}
		}
	}
}

/*
 * vs Terran building order and management
 */
void BuildingManager::terranBuildings()
{
	depot = Broodwar->self()->allUnitCount(UnitTypes::Terran_Supply_Depot);
	barracks = Broodwar->self()->allUnitCount(UnitTypes::Terran_Barracks);
	refinery = Broodwar->self()->allUnitCount(UnitTypes::Terran_Refinery);
	academy = Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy);
	factory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Factory);
	armory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Armory);

	static int lastChecked = 0;
	static int movetime = 150;
	static bool scouting = false;

	workerManager = new WorkerManager;
	scoutManager = new ScoutManager;

	// Build depot
	if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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
	if (barracks == 0 && Broodwar->self()->supplyUsed() >= 22 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Barracks, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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

	// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
	if (refinery == 0 && Broodwar->self()->supplyUsed() >= 22 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			Unitset geysers = Broodwar->getGeysers(); // Get all geysers
			Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
			TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Refinery, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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

	// Build second depot
	if (depot == 1 && Broodwar->self()->supplyUsed() >= 30 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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

	// Build factory
	if (factory == 0 && Broodwar->self()->supplyUsed() >= 32 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice() && Broodwar->self()->gas() >= UnitTypes::Terran_Factory.gasPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Factory, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
				{
					Broodwar->drawBoxMap(Position(buildPosition),
						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
						Colors::Blue);
				},
					nullptr,  // condition
					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
			}
		}
	}

	// Build second factory
	if (factory == 1 && Broodwar->self()->supplyUsed() >= 36 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice() && Broodwar->self()->gas() >= UnitTypes::Terran_Factory.gasPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for barracks and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Factory, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
				{
					Broodwar->drawBoxMap(Position(buildPosition),
						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
						Colors::Blue);
				},
					nullptr,  // condition
					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
			}
		}
	}

	// Build third depot
	if (depot == 2 && Broodwar->self()->supplyUsed() >= 46 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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

	// Build fourth depot
	if (depot == 3 && Broodwar->self()->supplyUsed() >= 56 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();

		// If worker is found
		if (builder)
		{
			// Find a location for depot and construct it
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

			// If build position is found
			if (buildPosition)
			{
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				// Register an event that draws the target build location
				Broodwar->registerEvent([buildPosition, builder](Game*)
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
}

/*
 * Academy tech
 */
void BuildingManager::academyTech(BWAPI::Unit u)
{
	if (!u->isResearching() && !u->isUpgrading())
	{
		if (u->canResearch(TechTypes::Stim_Packs) && Broodwar->self()->minerals() >= TechTypes::Stim_Packs.mineralPrice() && Broodwar->self()->gas() >= TechTypes::Stim_Packs.gasPrice())
		{
			u->research(TechTypes::Stim_Packs);
		}
		else if (u->canResearch(TechTypes::Restoration) && Broodwar->self()->minerals() >= TechTypes::Restoration.mineralPrice() && Broodwar->self()->gas() >= TechTypes::Restoration.gasPrice())
		{
			u->research(TechTypes::Restoration);
		}
		else if (u->canResearch(TechTypes::Optical_Flare) && Broodwar->self()->minerals() >= TechTypes::Optical_Flare.mineralPrice() && Broodwar->self()->gas() >= TechTypes::Optical_Flare.gasPrice())
		{
			u->research(TechTypes::Optical_Flare);
		}
		else if (u->canUpgrade(UpgradeTypes::U_238_Shells) && Broodwar->self()->minerals() >= UpgradeTypes::U_238_Shells.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::U_238_Shells.gasPrice())
		{
			u->upgrade(UpgradeTypes::U_238_Shells);
		}
		else if (u->canUpgrade(UpgradeTypes::Caduceus_Reactor) && Broodwar->self()->minerals() >= UpgradeTypes::Caduceus_Reactor.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Caduceus_Reactor.gasPrice())
		{
			u->upgrade(UpgradeTypes::Caduceus_Reactor);
		}
	}	
}

/*
 * Armory tech
 */
void BuildingManager::armoryTech(BWAPI::Unit u)
{
	if (!u->isResearching() && !u->isUpgrading())
	{		
		if (u->canUpgrade(UpgradeTypes::Terran_Vehicle_Weapons) && Broodwar->self()->minerals() >= UpgradeTypes::Terran_Vehicle_Weapons.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Terran_Vehicle_Weapons.gasPrice())
		{
			u->upgrade(UpgradeTypes::Terran_Vehicle_Weapons);
		}
		else if (u->canUpgrade(UpgradeTypes::Terran_Vehicle_Plating) && Broodwar->self()->minerals() >= UpgradeTypes::Terran_Vehicle_Plating.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Terran_Vehicle_Plating.gasPrice())
		{
			u->upgrade(UpgradeTypes::Terran_Vehicle_Plating);
		}
		else if (u->canUpgrade(UpgradeTypes::Terran_Ship_Weapons) && Broodwar->self()->minerals() >= UpgradeTypes::Terran_Ship_Weapons.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Terran_Ship_Weapons.gasPrice())
		{
			u->upgrade(UpgradeTypes::Terran_Ship_Weapons);
		}
		else if (u->canUpgrade(UpgradeTypes::Terran_Ship_Plating) && Broodwar->self()->minerals() >= UpgradeTypes::Terran_Ship_Plating.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Terran_Ship_Plating.gasPrice())
		{
			u->upgrade(UpgradeTypes::Terran_Ship_Plating);
		}
	}
}