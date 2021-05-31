/*
 *
 * Handles all building logic
 *
 */
#include "buildingManager.h"
#include "BWEB.h"

using namespace BWAPI;
using namespace Filter;

/*
 * vs Zerg building order and management
 */
void BuildingManager::zergBuildings(BWAPI::Unitset set)
{
	/*
	 * Manager files
	 */
	workerManager = new WorkerManager;
	scoutManager = new ScoutManager;

	/*
	 * BWAPI
	 */
	base = Broodwar->self()->getStartLocation();

	/*
	 * Variables
	 */
	depot = Broodwar->self()->allUnitCount(UnitTypes::Terran_Supply_Depot);
	barracks = Broodwar->self()->allUnitCount(UnitTypes::Terran_Barracks);
	refinery = Broodwar->self()->allUnitCount(UnitTypes::Terran_Refinery);
	academy = Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy);
	factory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Factory);
	armory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Armory);
	commandCenter = Broodwar->self()->allUnitCount(UnitTypes::Terran_Command_Center);

	static int lastRequest = 0;
	static int movetime = 200;		

	/*
	 * Supply management
	 */
	 // If supply count is at cap, build a supply depot to continue progression
	if (Broodwar->self()->supplyUsed() == Broodwar->self()->supplyTotal() && Broodwar->self()->supplyTotal() != 200 && lastRequest + 100 < Broodwar->getFrameCount() && Broodwar->self()->incompleteUnitCount(UnitTypes::Terran_Supply_Depot) == 0)
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a build position for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
			}
		}
	}
		
	/*
	 * Build order
	 */
	// Depot
	if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a build position for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
			}
		}
	}

	// Barracks
	if (barracks == 0 && Broodwar->self()->supplyUsed() >= 22 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a build position for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Barracks, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
			}
		}
	}

	// Barracks 2
	if (barracks == 1 && Broodwar->self()->supplyUsed() >= 26 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a build position for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Barracks, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
			}
		}
	}

	// Depot 2
	if (depot == 1 && Broodwar->self()->supplyUsed() >= 28 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a build position for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
			}
		}
	}

	// Refinery
	if (refinery == 0 && Broodwar->self()->supplyUsed() >= 30 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice() && Broodwar->self()->incompleteUnitCount(UnitTypes::Terran_Refinery) == 0)
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a build position for structure
			Unitset geysers = Broodwar->getGeysers(); // Get all geysers
			Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
			TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position

			// If build position is found
			if (buildPosition)
			{
				// Build 
				builder->build(UnitTypes::Terran_Refinery, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Refinery.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Refinery.buildTime() + 100);  // frames to run
			}
		}
	}

	// Academy
	if (academy == 0 && Broodwar->self()->supplyUsed() >= 36 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Academy.mineralPrice() && Broodwar->self()->incompleteUnitCount(UnitTypes::Terran_Academy) == 0)
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a build position for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Academy, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Academy, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Academy.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Academy.buildTime() + 100);  // frames to run
			}
		}
	}

	// Expansion
	if (Broodwar->self()->supplyUsed() >= 40 && lastRequest + 200 < Broodwar->getFrameCount() && Broodwar->self()->incompleteUnitCount(UnitTypes::Terran_Command_Center) == 0)
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for natural expansion
			BWAPI::TilePosition buildPosition = BWEB::Map::getNaturalTile();

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Command_Center, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
			}
		}
	}

	// Factory
	if (academy == 1 && factory == 0 && Broodwar->self()->supplyUsed() >= 68 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice() && Broodwar->self()->gas() >= UnitTypes::Terran_Factory.gasPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a build position for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Factory, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
			}
		}
	}	

	// Armoury
	if (factory == 1 && armory == 0 && Broodwar->self()->supplyUsed() >= 68 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Armory.mineralPrice() && Broodwar->self()->gas() >= UnitTypes::Terran_Armory.gasPrice() && Broodwar->self()->incompleteUnitCount(UnitTypes::Terran_Armory) == 0)
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a build position for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Armory, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Armory, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Armory.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Armory.buildTime() + 100);  // frames to run
			}
		}
	}
	
	// Factory 2
	if (factory == 1 && Broodwar->self()->supplyUsed() >= 80 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice() && Broodwar->self()->gas() >= UnitTypes::Terran_Factory.gasPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a build position for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Factory, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
			}
		}
	}

	// Barracks 3
	if (barracks == 2 && Broodwar->self()->supplyUsed() >= 90 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a build position for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Barracks, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
			}
		}
	}

	// Barracks 4
	if (barracks == 3 && Broodwar->self()->supplyUsed() >= 100 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a build position for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Barracks, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
			}
		}
	}
}

/*
 * vs Protoss building order and management
 */
void BuildingManager::protossBuildings(BWAPI::Unitset set)
{
	/*
	 * Manager files
	 */
	workerManager = new WorkerManager;
	scoutManager = new ScoutManager;

	/*
	 * BWAPI
	 */
	base = Broodwar->self()->getStartLocation();

	/*
	 * variables
	 */
	depot = Broodwar->self()->allUnitCount(UnitTypes::Terran_Supply_Depot);
	barracks = Broodwar->self()->allUnitCount(UnitTypes::Terran_Barracks);
	refinery = Broodwar->self()->allUnitCount(UnitTypes::Terran_Refinery);
	academy = Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy);
	factory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Factory);
	armory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Armory);
	commandCenter = Broodwar->self()->allUnitCount(UnitTypes::Terran_Command_Center);

	static int lastRequest = 0;
	static int movetime = 200;

	/*
	 * Supply management
	 */
	 // If supply count is at cap, build a supply depot to continue progression
	if (Broodwar->self()->supplyUsed() == Broodwar->self()->supplyTotal() && Broodwar->self()->supplyTotal() != 200 && lastRequest + 100 < Broodwar->getFrameCount() && Broodwar->self()->incompleteUnitCount(UnitTypes::Terran_Supply_Depot) == 0)
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
			}
		}
	}

	/*
	 * Build order
	 */
	// Depot
	if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{ 
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
			}
		}
	}

	// Barracks
	if (barracks == 0 && Broodwar->self()->supplyUsed() >= 22 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Barracks, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
			}
		}
	}

	// Refinery
	if (refinery == 0 && Broodwar->self()->supplyUsed() >= 26 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			Unitset geysers = Broodwar->getGeysers();
			Unit closestGeyser = geysers.getClosestUnit();
			TilePosition buildPosition = closestGeyser->getTilePosition();

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Refinery, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Refinery.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Refinery.buildTime() + 100);  // frames to run
			}
		}
	}	

	// Depot 2
	if (depot == 1 && Broodwar->self()->supplyUsed() >= 34 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
			}
		}
	}

	// Factory
	if (factory == 0 && depot == 2 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= 200 && Broodwar->self()->gas() >= 100)
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Factory, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
			}
		}
	}

	// Depot 3
	if (factory == 1 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
			}
		}
	}

	// Factory 2
	if (factory == 1 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice() && Broodwar->self()->gas() >= UnitTypes::Terran_Factory.gasPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Factory, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
			}
		}
	}
}

/*
 * vs Terran building order and management
 */
void BuildingManager::terranBuildings(BWAPI::Unitset set)
{
	/*
	 * Manager files
	 */
	workerManager = new WorkerManager;
	scoutManager = new ScoutManager;

	/*
	 * BWAPI
	 */
	base = Broodwar->self()->getStartLocation();

	/*
	 * Variables
	 */
	depot = Broodwar->self()->allUnitCount(UnitTypes::Terran_Supply_Depot);
	barracks = Broodwar->self()->allUnitCount(UnitTypes::Terran_Barracks);
	refinery = Broodwar->self()->allUnitCount(UnitTypes::Terran_Refinery);
	academy = Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy);
	factory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Factory);
	armory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Armory);
	commandCenter = Broodwar->self()->allUnitCount(UnitTypes::Terran_Command_Center);

	static int lastRequest = 0;
	static int movetime = 200;
	
	/*
	 * Supply management
	 */
	 // If supply count is at cap, build a supply depot to continue progression
	if (Broodwar->self()->supplyUsed() == Broodwar->self()->supplyTotal() && Broodwar->self()->supplyTotal() != 200 && lastRequest + 100 < Broodwar->getFrameCount() && Broodwar->self()->incompleteUnitCount(UnitTypes::Terran_Supply_Depot) == 0)
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
			}
		}
	}

	/*
	 * Build order
	 */
	// Depot
	if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
			}
		}
	}

	// Barracks
	if (barracks == 0 && Broodwar->self()->supplyUsed() >= 22 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Barracks, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
			}
		}
	}

	// Refinery
	if (refinery == 0 && Broodwar->self()->supplyUsed() >= 22 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			Unitset geysers = Broodwar->getGeysers();
			Unit closestGeyser = geysers.getClosestUnit();
			TilePosition buildPosition = closestGeyser->getTilePosition();

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Refinery, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Refinery.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Refinery.buildTime() + 100);  // frames to run
			}
		}
	}

	// Depot 2
	if (depot == 1 && Broodwar->self()->supplyUsed() >= 30 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
			}
		}
	}

	// Factory
	if (factory == 0 && Broodwar->self()->supplyUsed() >= 32 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice() && Broodwar->self()->gas() >= UnitTypes::Terran_Factory.gasPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Factory, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
			}
		}
	}

	// Factory 2
	if (factory == 1 && Broodwar->self()->supplyUsed() >= 36 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice() && Broodwar->self()->gas() >= UnitTypes::Terran_Factory.gasPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Factory, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
			}
		}
	}

	// Depot 3
	if (depot == 2 && Broodwar->self()->supplyUsed() >= 46 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
			}
		}
	}

	// Depot 4
	if (depot == 3 && Broodwar->self()->supplyUsed() >= 56 && lastRequest + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	{
		// Update lastRequest
		lastRequest = Broodwar->getFrameCount();

		// Get builder
		Unit builder = workerManager->getWorkerFromSet(set);

		// If builder is found
		if (builder)
		{
			// Find a location for structure
			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, base);

			// If build position is found
			if (buildPosition)
			{
				// Build
				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

				//// Register an event that draws the target build location
				//Broodwar->registerEvent([buildPosition, builder](Game*)
				//{
				//	Broodwar->drawBoxMap(Position(buildPosition),
				//		Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
				//		Colors::Blue);
				//},
				//	nullptr,  // condition
				//	UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
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
		// Stimpacks
		if (u->canResearch(TechTypes::Stim_Packs) && Broodwar->self()->minerals() >= TechTypes::Stim_Packs.mineralPrice() && Broodwar->self()->gas() >= TechTypes::Stim_Packs.gasPrice())
		{
			u->research(TechTypes::Stim_Packs);
		}
		// U238 shells
		else if (u->canUpgrade(UpgradeTypes::U_238_Shells) && Broodwar->self()->minerals() >= UpgradeTypes::U_238_Shells.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::U_238_Shells.gasPrice())
		{
			u->upgrade(UpgradeTypes::U_238_Shells);
		}
		// Caduceus reactor
		else if (u->canUpgrade(UpgradeTypes::Caduceus_Reactor) && Broodwar->self()->minerals() >= UpgradeTypes::Caduceus_Reactor.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Caduceus_Reactor.gasPrice())
		{
			u->upgrade(UpgradeTypes::Caduceus_Reactor);
		}
		// Optical flare
		else if (u->canResearch(TechTypes::Optical_Flare) && Broodwar->self()->minerals() >= TechTypes::Optical_Flare.mineralPrice() && Broodwar->self()->gas() >= TechTypes::Optical_Flare.gasPrice())
		{
			u->research(TechTypes::Optical_Flare);
		}
		// Restoration
		else if (u->canResearch(TechTypes::Restoration) && Broodwar->self()->minerals() >= TechTypes::Restoration.mineralPrice() && Broodwar->self()->gas() >= TechTypes::Restoration.gasPrice())
		{
			u->research(TechTypes::Restoration);
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
		// Vehicle weapons
		if (u->canUpgrade(UpgradeTypes::Terran_Vehicle_Weapons) && Broodwar->self()->minerals() >= UpgradeTypes::Terran_Vehicle_Weapons.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Terran_Vehicle_Weapons.gasPrice())
		{
			u->upgrade(UpgradeTypes::Terran_Vehicle_Weapons);
		}
		// vehicle plating
		else if (u->canUpgrade(UpgradeTypes::Terran_Vehicle_Plating) && Broodwar->self()->minerals() >= UpgradeTypes::Terran_Vehicle_Plating.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Terran_Vehicle_Plating.gasPrice())
		{
			u->upgrade(UpgradeTypes::Terran_Vehicle_Plating);
		}
		// Ship weapons
		else if (u->canUpgrade(UpgradeTypes::Terran_Ship_Weapons) && Broodwar->self()->minerals() >= UpgradeTypes::Terran_Ship_Weapons.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Terran_Ship_Weapons.gasPrice())
		{
			u->upgrade(UpgradeTypes::Terran_Ship_Weapons);
		}
		// Ship plating
		else if (u->canUpgrade(UpgradeTypes::Terran_Ship_Plating) && Broodwar->self()->minerals() >= UpgradeTypes::Terran_Ship_Plating.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Terran_Ship_Plating.gasPrice())
		{
			u->upgrade(UpgradeTypes::Terran_Ship_Plating);
		}
	}
}

/*
 * Machine shop tech
 */
void BuildingManager::machineTech(BWAPI::Unit u)
{
	if (!u->isResearching() && !u->isUpgrading())
	{
		// Siege mode
		if (u->canResearch(TechTypes::Tank_Siege_Mode) && Broodwar->self()->minerals() >= TechTypes::Tank_Siege_Mode.mineralPrice() && Broodwar->self()->gas() >= TechTypes::Tank_Siege_Mode.gasPrice())
		{
			u->research(TechTypes::Tank_Siege_Mode);
		}
		// Spider mines
		else if (u->canResearch(TechTypes::Spider_Mines) && Broodwar->self()->minerals() >= TechTypes::Spider_Mines.mineralPrice() && Broodwar->self()->gas() >= TechTypes::Spider_Mines.gasPrice())
		{
			u->research(TechTypes::Spider_Mines);
		}
		// Ion thrusters
		else if (u->canResearch(UpgradeTypes::Ion_Thrusters) && Broodwar->self()->minerals() >= UpgradeTypes::Ion_Thrusters.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Ion_Thrusters.gasPrice())
		{
			u->upgrade(UpgradeTypes::Ion_Thrusters);
		}
		// Charon Boosters
		else if (u->canResearch(UpgradeTypes::Charon_Boosters) && Broodwar->self()->minerals() >= UpgradeTypes::Charon_Boosters.mineralPrice() && Broodwar->self()->gas() >= UpgradeTypes::Charon_Boosters.gasPrice())
		{
			u->upgrade(UpgradeTypes::Charon_Boosters);
		}
	}
}
