/*
 *
 * Handles all build order logic
 *
 */
#include "BuildOrder.h"

using namespace BWAPI;
using namespace Filter;

void BuildOrder::buildOrder()
{	
	depot = Broodwar->self()->allUnitCount(UnitTypes::Terran_Supply_Depot);
	barracks = Broodwar->self()->allUnitCount(UnitTypes::Terran_Barracks);
	refinery = Broodwar->self()->allUnitCount(UnitTypes::Terran_Refinery);
	academy = Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy);
	factory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Factory);

	static int lastChecked = 0;
	static int movetime = 150;
	bool haveScout = false;	

	workerManager = new WorkerManager;
	scoutManager = new ScoutManager;
		
	/*
	*
	* ZERG build order
	*
	*/
	if (Broodwar->enemy()->getRace() == Races::Zerg)
	{
		// Build depot
		if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
		{
			lastChecked = Broodwar->getFrameCount();

			Unit builder = workerManager->getWorker();

			// If worker is found
			if (builder)
			{
				// Find a location for depot
				TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

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

			Unit builder = workerManager->getWorker();

			// If worker is found
			if (builder)
			{
				// Find a location for barracks
				TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, builder->getTilePosition());

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

			Unit builder = workerManager->getWorker();

			// If worker is found
			if (builder)
			{
				// Find a location for barracks
				TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, builder->getTilePosition());

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

			Unit builder = workerManager->getWorker();

			// If worker is found
			if (builder)
			{
				// Find a location for depot
				TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

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
		if (refinery == 0 && Broodwar->self()->supplyUsed() >= 30 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice())
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
		if (academy == 0 && Broodwar->self()->supplyUsed() >= 36 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Academy.mineralPrice())
		{
			lastChecked = Broodwar->getFrameCount();

			Unit builder = workerManager->getWorker();

			// If worker is found
			if (builder)
			{
				// Find a location for academy
				TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Academy, builder->getTilePosition());

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
		if (academy == 1 && !haveScout && lastChecked + movetime < Broodwar->getFrameCount())
		{
			lastChecked = Broodwar->getFrameCount();
			scoutManager->setScout();
			haveScout = true;
			scoutManager->goScout();			
		}
	}

	///*
	// *
	// * PROTOSS build order **UNFINISHED**
	// *
	// */
	//else if (Broodwar->enemy()->getRace() == Races::Protoss)
	//{
	//	// Build depot
	//	if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			// Find a location for depot and construct it
	//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}

	//	// Build barracks
	//	if (barracks == 0 && Broodwar->self()->supplyUsed() >= 22 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			// Find a location for barracks and construct it
	//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, builder->getTilePosition());

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Barracks, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}

	//	// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
	//	if (refinery == 0 && Broodwar->self()->supplyUsed() >= 26 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice())
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			Unitset geysers = Broodwar->getGeysers(); // Get all geysers
	//			Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
	//			TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Refinery, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Refinery.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Refinery.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}

	//	// Build second depot
	//	if (depot == 1 && Broodwar->self()->supplyUsed() >= 34 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			// Find a location for depot and construct it
	//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}

	//	// Build factory
	//	if (factory == 0 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() == 200 && Broodwar->self()->gas() == 100)
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			// Find a location for barracks and construct it
	//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, builder->getTilePosition());

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Factory, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}

	//	// Build second factory
	//	if (factory == 1 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() == 200)
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			// Find a location for barracks and construct it
	//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, builder->getTilePosition());

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Factory, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
	//			}
	//		}
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
	//	if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			// Find a location for depot and construct it
	//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}

	//	// Build barracks
	//	if (barracks == 0 && Broodwar->self()->supplyUsed() >= 22 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			// Find a location for barracks and construct it
	//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, builder->getTilePosition());

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Barracks, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}

	//	// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
	//	if (refinery == 0 && Broodwar->self()->supplyUsed() >= 22 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice())
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			Unitset geysers = Broodwar->getGeysers(); // Get all geysers
	//			Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
	//			TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Refinery, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Refinery.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Refinery.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}

	//	// Build second depot
	//	if (depot == 1 && Broodwar->self()->supplyUsed() >= 30 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			// Find a location for depot and construct it
	//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}

	//	// Build factory
	//	if (factory == 0 && Broodwar->self()->supplyUsed() >= 32 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice())
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			// Find a location for barracks and construct it
	//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, builder->getTilePosition());

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Factory, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}

	//	// Build second factory
	//	if (factory == 1 && Broodwar->self()->supplyUsed() >= 36 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice())
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			// Find a location for barracks and construct it
	//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, builder->getTilePosition());

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Factory, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}

	//	// Build third depot
	//	if (depot == 2 && Broodwar->self()->supplyUsed() >= 46 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			// Find a location for depot and construct it
	//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}

	//	// Build fourth depot
	//	if (depot == 3 && Broodwar->self()->supplyUsed() >= 56 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
	//	{
	//		lastChecked = Broodwar->getFrameCount();

	//		Unit builder = workerManager->getWorkerUS(set);

	//		// If worker is found
	//		if (builder)
	//		{
	//			// Find a location for depot and construct it
	//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());

	//			// If build position is found
	//			if (buildPosition)
	//			{
	//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);

	//				// Register an event that draws the target build location
	//				Broodwar->registerEvent([buildPosition, builder](Game*)
	//				{
	//					Broodwar->drawBoxMap(Position(buildPosition),
	//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
	//						Colors::Blue);
	//				},
	//					nullptr,  // condition
	//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
	//			}
	//		}
	//	}
	//}
}

///*
// * Zerg build order
// */
//void BuildOrder::Zerg(BWAPI::Unitset set)
//{
//	workerManager = new WorkerManager;
//	scoutManager = new ScoutManager;
//
//	depot = Broodwar->self()->allUnitCount(UnitTypes::Terran_Supply_Depot);
//	barracks = Broodwar->self()->allUnitCount(UnitTypes::Terran_Barracks);
//	refinery = Broodwar->self()->allUnitCount(UnitTypes::Terran_Refinery);
//	academy = Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy);
//	factory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Factory);
//
//	static int lastChecked = 0;
//	static int movetime = 150;
//	bool haveScout = false;
//
//	// Build depot
//	if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for depot
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				// Build
//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build barracks
//	if (barracks == 0 && Broodwar->self()->supplyUsed() >= 22 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for barracks
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				//Build
//				builder->build(UnitTypes::Terran_Barracks, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build second barracks
//	if (barracks == 1 && Broodwar->self()->supplyUsed() >= 26 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for barracks
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				// Build
//				builder->build(UnitTypes::Terran_Barracks, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build second depot
//	if (depot == 1 && Broodwar->self()->supplyUsed() >= 28 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for depot
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				// Build
//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
//	if (refinery == 0 && Broodwar->self()->supplyUsed() >= 30 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			Unitset geysers = Broodwar->getGeysers(); // Get all geysers
//			Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
//			TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position
//
//			// If build position is found
//			if (buildPosition)
//			{
//				// Build 
//				builder->build(UnitTypes::Terran_Refinery, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Refinery.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Refinery.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build academy
//	if (academy == 0 && Broodwar->self()->supplyUsed() >= 36 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Academy.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for academy
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Academy, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				// Build
//				builder->build(UnitTypes::Terran_Academy, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Academy.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Academy.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//	if (academy == 1 && !haveScout && lastChecked + movetime < Broodwar->getFrameCount())
//	{
//		scoutManager->setScout(set);
//		haveScout = true;
//		scoutManager->goScout();
//	}
//}
//
///*
// * Protoss build order
// */
//void BuildOrder::Protoss(BWAPI::Unitset set)
//{
//	workerManager = new WorkerManager;
//	scoutManager = new ScoutManager;
//
//	depot = Broodwar->self()->allUnitCount(UnitTypes::Terran_Supply_Depot);
//	barracks = Broodwar->self()->allUnitCount(UnitTypes::Terran_Barracks);
//	refinery = Broodwar->self()->allUnitCount(UnitTypes::Terran_Refinery);
//	academy = Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy);
//	factory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Factory);
//
//	static int lastChecked = 0;
//	static int movetime = 150;
//	bool haveScout = false;
//
//	// Build depot
//	if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for depot and construct it
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build barracks
//	if (barracks == 0 && Broodwar->self()->supplyUsed() >= 22 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for barracks and construct it
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Barracks, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
//	if (refinery == 0 && Broodwar->self()->supplyUsed() >= 26 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			Unitset geysers = Broodwar->getGeysers(); // Get all geysers
//			Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
//			TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Refinery, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Refinery.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Refinery.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build second depot
//	if (depot == 1 && Broodwar->self()->supplyUsed() >= 34 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for depot and construct it
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build factory
//	if (factory == 0 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() == 200 && Broodwar->self()->gas() == 100)
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for barracks and construct it
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Factory, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build second factory
//	if (factory == 1 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() == 200)
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for barracks and construct it
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Factory, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//}
//
///*
// * Terran build order
// */
//void BuildOrder::Terran(BWAPI::Unitset set)
//{
//	workerManager = new WorkerManager;
//	scoutManager = new ScoutManager;
//
//	depot = Broodwar->self()->allUnitCount(UnitTypes::Terran_Supply_Depot);
//	barracks = Broodwar->self()->allUnitCount(UnitTypes::Terran_Barracks);
//	refinery = Broodwar->self()->allUnitCount(UnitTypes::Terran_Refinery);
//	academy = Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy);
//	factory = Broodwar->self()->allUnitCount(UnitTypes::Terran_Factory);
//
//	static int lastChecked = 0;
//	static int movetime = 150;
//	bool haveScout = false;
//
//	// Build depot
//	if (depot == 0 && Broodwar->self()->supplyUsed() >= 18 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for depot and construct it
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build barracks
//	if (barracks == 0 && Broodwar->self()->supplyUsed() >= 22 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Barracks.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for barracks and construct it
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Barracks, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Barracks.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Barracks.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build refinery **NEEDS TO BE IMPROVED FROM CLOSEST**
//	if (refinery == 0 && Broodwar->self()->supplyUsed() >= 22 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Refinery.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			Unitset geysers = Broodwar->getGeysers(); // Get all geysers
//			Unit closestGeyser = geysers.getClosestUnit(); // Get closest geyser
//			TilePosition buildPosition = closestGeyser->getTilePosition(); // Get closest geyser position
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Refinery, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Refinery.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Refinery.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build second depot
//	if (depot == 1 && Broodwar->self()->supplyUsed() >= 30 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for depot and construct it
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build factory
//	if (factory == 0 && Broodwar->self()->supplyUsed() >= 32 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for barracks and construct it
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Factory, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build second factory
//	if (factory == 1 && Broodwar->self()->supplyUsed() >= 36 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Factory.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for barracks and construct it
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Factory, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Factory, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Factory.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Factory.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build third depot
//	if (depot == 2 && Broodwar->self()->supplyUsed() >= 46 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for depot and construct it
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//
//	// Build fourth depot
//	if (depot == 3 && Broodwar->self()->supplyUsed() >= 56 && lastChecked + movetime < Broodwar->getFrameCount() && Broodwar->self()->minerals() >= UnitTypes::Terran_Supply_Depot.mineralPrice())
//	{
//		lastChecked = Broodwar->getFrameCount();
//
//		Unit builder = workerManager->getWorkerUS(set);
//
//		// If worker is found
//		if (builder)
//		{
//			// Find a location for depot and construct it
//			TilePosition buildPosition = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());
//
//			// If build position is found
//			if (buildPosition)
//			{
//				builder->build(UnitTypes::Terran_Supply_Depot, buildPosition);
//
//				// Register an event that draws the target build location
//				Broodwar->registerEvent([buildPosition, builder](Game*)
//				{
//					Broodwar->drawBoxMap(Position(buildPosition),
//						Position(buildPosition + UnitTypes::Terran_Supply_Depot.tileSize()),
//						Colors::Blue);
//				},
//					nullptr,  // condition
//					UnitTypes::Terran_Supply_Depot.buildTime() + 100);  // frames to run
//			}
//		}
//	}
//}