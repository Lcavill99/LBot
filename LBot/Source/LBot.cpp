#include "LBot.h"
#include "BuildOrder.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;

BWAPI::Unitset allWorkers; // Holds all player workers
BWAPI::Unitset minWorkers; // Holds all player workers assigned to gather minerals
BWAPI::Unitset gasWorkers; // Holds all player workers assigned to gather gas
BWAPI::Unitset allBuildings; // Holds all player buildings
BWAPI::Unitset army1; // Holds all player units assigned to the offensive army
BWAPI::Unitset army2; // Holds all player units assigned to the secondary/defensive army
BWAPI::Unitset enemyBuildings; // Holds all enemy buildings

static int lastChecked = 0;
bool finScouting = false;

void LBot::onStart()
{
	// Enable the UserInput flag, which allows us to control the bot and type messages.
	Broodwar->enableFlag(Flag::UserInput);

	// Uncomment the following line and the bot will know about everything through the fog of war (cheat).
	//Broodwar->enableFlag(Flag::CompleteMapInformation);

	// Set the command optimization level so that common commands can be grouped
	// and reduce the bot's APM (Actions Per Minute).
	Broodwar->setCommandOptimizationLevel(2);	

	buildOrder = new BuildOrder;
	scoutManager = new ScoutManager;
	workerManager = new WorkerManager;
	buildingManager = new BuildingManager;
	armyManager = new ArmyManager;

	// Check if this is a replay
	if (Broodwar->isReplay())
	{
		// Announce the players in the replay
		Broodwar << "The following players are in this replay:" << std::endl;
    
		// Iterate all the players in the game using a std:: iterator
		Playerset players = Broodwar->getPlayers();
		for(auto p : players)
		{
		// Only print the player if they are not an observer
		if ( !p->isObserver() )
			Broodwar << p->getName() << ", playing as " << p->getRace() << std::endl;
		}
	}		
}

void LBot::onEnd(bool isWinner)
{
	// Called when the game ends
	if ( isWinner )
	{
		// Log your win here!
	}
}

void LBot::onFrame()
{	
	// Display values
	Broodwar->drawTextScreen(0, 0,  "FPS: %d", Broodwar->getFPS());
	Broodwar->drawTextScreen(0, 10, "Workers: %d", allWorkers.size());
	Broodwar->drawTextScreen(0, 20, "Mineral workers: %d", minWorkers.size());
	Broodwar->drawTextScreen(0, 30, "Gas workers: %d", gasWorkers.size());
	Broodwar->drawTextScreen(0, 40, "Army1: %d", army1.size());
	Broodwar->drawTextScreen(0, 50, "Army2: %d", army2.size());

	// Return if the game is a replay or is paused
	if (Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self())
		return;

	// Prevent spamming by only running our onFrame once every number of latency frames.
	// Latency frames are the number of frames before commands are processed.
	if (Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0)
		return;

	// Update latest error
	Error lastErr = Broodwar->getLastError();

	// Call Build order
	buildOrder->buildOrder();
	
	/*
	 * Scouting
	 */
	//auto& enemyBase = Broodwar->enemy()->getStartLocation();

	// If we have a scout and aren't already scouting, once we have started building an academy, send scout to all possible start locations to find the enemy base
	if (Broodwar->self()->supplyUsed() >= 30 && !finScouting)
	{
		// If we dont have a scout, assign one
		if (!scout)
		{
			scout = workerManager->getWorker();
		}
		auto& startLocations = Broodwar->getStartLocations();	
		
		// Loop through all start locations
		for (BWAPI::TilePosition baseLocation : startLocations)
		{
			// If the location is already explored, move on
			if (Broodwar->isExplored(baseLocation))
			{
				continue;
			}		

			BWAPI::Position pos(baseLocation);
			// Move to start location to scout
			scout->move(pos);
			break;
		}		
	}	

	/*
	 * Attacking
	 */
	// If army is at half strength, retreat
	if (army1.size() < (army1.max_size() / 2))
	{
		//retreat
	}
	else
	{
		for (BWAPI::Unit unit : army1)
		{
			if (unit->getHitPoints() < (unit->getInitialHitPoints() / 2))
			{
				//retreat to back of group
			}
			unit->attack(unit->getClosestUnit(Filter::IsEnemy));			
		}
	}	
		
	/*
	 * Supply management
	 */
	// If supply count is at cap, build a supply depot to continue progression
	if (lastErr == Errors::Insufficient_Supply && lastChecked + 150 < Broodwar->getFrameCount())
	{
		lastChecked = Broodwar->getFrameCount();

		Unit builder = workerManager->getWorker();		

		// If worker is found and its not the scout
		if (builder != scout)
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

	/*
	 * Unit iteration
	 */
	// Iterate through all owned units
	for (auto &u : Broodwar->self()->getUnits())
	{
		/*
		 * Initial selection process
		 */
		// Ignore the unit if it no longer exists
		if (!u->exists())
			continue;

		// Ignore the unit if it has one of the following status ailments
		if (u->isLockedDown() || u->isMaelstrommed() || u->isStasised())
			continue;

		// Ignore the unit if it is in one of the following states
		if (u->isLoaded() || !u->isPowered() || u->isStuck())
			continue;

		// Ignore the unit if it is incomplete or busy constructing
		if (!u->isCompleted() || u->isConstructing())
			continue;
		
		/*
		 * Workers
		 */
		if (u->getType().isWorker())
		{	
			/*
		     * Unitset management
		     */
			// If worker isn't in the allWorkers unitset
			if (!allWorkers.contains(u))
			{
				// Add to gasWorkers unitset
				allWorkers.insert(u);
			}
			if (u->isGatheringMinerals() && !minWorkers.contains(u))
			{   
				// If worker is in the refinery workers unitset, remove to avoid duplicate
				if (gasWorkers.contains(u))
				{
					gasWorkers.erase(u);
				}
				// Add to mineral workers unitset
				minWorkers.insert(u);
			}
			if (u->isGatheringGas() && gasWorkers.size() != 3 && !gasWorkers.contains(u))
			{
				// If worker is in the mineral workers unitset, remove to avoid duplicate
				if (minWorkers.contains(u))
				{
					minWorkers.erase(u);
				}
				// Add to refinery workers unitset
				gasWorkers.insert(u);
			}

			/*
			 * Worker gathering functionality
			 */
			// If worker is idle and is not the scout
			if (u->isIdle() && u != scout)
			{
				// If worker is carrying a resource return them to the command center
				if (u->isCarryingGas() || u->isCarryingMinerals())
				{
					u->returnCargo();
				}
				// Assign workers to refinery *WORKS TEMP only with 1 refinery*
				else if ((Broodwar->self()->completedUnitCount(UnitTypes::Terran_Refinery) == 1 && gasWorkers.size() != 3) || gasWorkers.contains(u))
				{
					workerManager->gatherGas(u);
				}
				// Otherwise assign to minerals
				else
				{
					workerManager->gatherMinerals(u);
				}				
			}
		}

		/*
		 * Marines
		 */
		else if (u->getType() == UnitTypes::Terran_Marine)
		{
			if (u->isIdle())
			{
				//if (u->getHitPoints() < (u->getInitialHitPoints() / 2))
				//{
				//	//Retreat back to base and get to max size
				//	//if army is at base then continue
				//	TilePosition base = Broodwar->self()->getStartLocation();
				//	Position pos(base);
				//	u->move(pos);
				//}
			}			
		}

		/*
		 * Medics
		 */
		if (u->getType() == UnitTypes::Terran_Medic)
		{
			if (u->isIdle())
			{
				//if (u->getHitPoints() < (u->getInitialHitPoints() / 2))
				//{
				//	//Retreat back to base and get to max size
				//	//if army is at base then continue
				//	TilePosition base = Broodwar->self()->getStartLocation();
				//	Position pos(base);
				//	u->move(pos);
				//}
			}
		}

		/*
		 * Command Center
		 */
		else if (u->getType() == UnitTypes::Terran_Command_Center)
		{
			// Construct workers if idle (24 workers per command center)
			if (u->isIdle() && Broodwar->self()->allUnitCount(UnitTypes::Terran_SCV) != Broodwar->self()->allUnitCount(UnitTypes::Terran_Command_Center) * 24 && !u->train(UnitTypes::Terran_SCV))
			{
				// If that fails, draw the error at the location so that you can visibly see what went wrong!
				// However, drawing the error once will only appear for a single frame
				// so create an event that keeps it on the screen for some frames
				Position pos = u->getPosition();
				Error lastErr = Broodwar->getLastError();
				Broodwar->registerEvent([pos,lastErr](Game*)
				{ 
					Broodwar->drawTextMap(pos, "%c%s", Text::White, lastErr.c_str()); 
				},   // action
					nullptr,    // condition
					Broodwar->getLatencyFrames());  // frames to run
			}
		}
		
		/*
		 * Barracks
		 */
		else if (u->getType() == UnitTypes::Terran_Barracks)
		{
			if (Broodwar->enemy()->getRace() == Races::Zerg)
			{
				// Train 1 medic for every 3 marines, enough for 2 armies
				if (Broodwar->self()->allUnitCount(UnitTypes::Terran_Academy) == 1 && (Broodwar->self()->allUnitCount(UnitTypes::Terran_Marine) == 9 && Broodwar->self()->allUnitCount(UnitTypes::Terran_Medic) != 3 || Broodwar->self()->allUnitCount(UnitTypes::Terran_Marine) == 18 && Broodwar->self()->allUnitCount(UnitTypes::Terran_Medic) != 6))
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

				// Train marines until marine army count is reached
				else if (u->isIdle() && Broodwar->self()->allUnitCount(UnitTypes::Terran_Marine) != 18 && !u->train(UnitTypes::Terran_Marine))
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
			else if (Broodwar->enemy()->getRace() == Races::Protoss)
			{

			}
			else if (Broodwar->enemy()->getRace() == Races::Terran)
			{
				if (u->isIdle() && Broodwar->self()->allUnitCount(UnitTypes::Terran_Marine) != 8 && !u->train(UnitTypes::Terran_Vulture))
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
		}

		/*
		 * Academy
		 */
		else if (u->getType() == UnitTypes::Terran_Academy)
		{
			// Perform research
			buildingManager->researchTech(u);
		}
	}	
}

void LBot::onSendText(std::string txt)
{
	// Send the text to the game if it is not being processed.
	Broodwar->sendText("%s", txt.c_str());

	// Make sure to use %s and pass the text as a parameter,
	// otherwise you may run into problems when you use the %(percent) character!
}

void LBot::onReceiveText(BWAPI::Player p, std::string txt)
{
	// Parse the received text
	Broodwar << p->getName() << " said \"" << txt << "\"" << std::endl;
}

void LBot::onPlayerLeft(BWAPI::Player p)
{
	// Interact verbally with the other players in the game by
	// announcing that the other player has left.
	Broodwar->sendText("Goodbye %s!", p->getName().c_str());
}

void LBot::onNukeDetect(BWAPI::Position t)
{
	// Check if the target is a valid position
	if (t)
	{
		// if so, print the location of the nuclear strike target
		Broodwar << "Nuclear Launch Detected at " << t << std::endl;
	}
	else 
	{
		// Otherwise, ask other players where the nuke is!
		Broodwar->sendText("Where's the nuke?");
	}
	// You can also retrieve all the nuclear missile targets using Broodwar->getNukeDots()!
}

void LBot::onUnitDiscover(BWAPI::Unit u)
{
	if (u->getPlayer() == Broodwar->enemy())
	{
		//If enemy base is discovered, stop scouting and go home
		if (u->getType().isResourceDepot())
		{						
			// Add to enemy buildings unitset
			enemyBuildings.insert(u);

			// Finish scouting
			finScouting = true;

			// Get player base location
			BWAPI::TilePosition home = Broodwar->self()->getStartLocation();
			BWAPI::Position homePos(home);

			// Move to base
			scout->move(homePos);

			if (scout->getPosition().getDistance(homePos) < 100)
			{
				scout = NULL;
			}			
		}
	}    
}

//void LBot::onUnitEvade(BWAPI::Unit u)
//{
//}

//void LBot::onUnitShow(BWAPI::Unit u)
//{
//}

//void LBot::onUnitHide(BWAPI::Unit u)
//{
//}

// NOTE: Workers and command center that the player starts with counts as being created when the game starts
void LBot::onUnitCreate(BWAPI::Unit u)
{	
	//// Upon creation of unit belonging to player
	//if (u->getPlayer() == Broodwar->self())
	//{
	//	// Unitset management
	//	if (u->getType().isWorker())
	//	{
	//		// Add worker to worker unitset
	//		allWorkers.insert(u);
	//	}
	//	else if (u->getType().isBuilding())
	//	{
	//		// Add building to building unitset
	//		allBuildings.insert(u);
	//	}
	//	// If army1 isnt full
	//	else if ((!u->getType().isWorker() && !u->getType().isBuilding()) && army1.size() != 12)
	//	{
	//		// Add unit to army1
	//		army1.insert(u);
	//	}
	//	// If army1 is full and army2 isnt
	//	else if ((!u->getType().isWorker() && !u->getType().isBuilding()) && army1.size() == 12 && army2.size() != 12)
	//	{
	//		// Add unit to army2
	//		army2.insert(u);
	//	}
	//}

	if (Broodwar->isReplay())
	{
		// if we are in a replay, then we will print out the build order of the structures
		if (u->getType().isBuilding() && !u->getPlayer()->isNeutral())
		{
			int seconds = Broodwar->getFrameCount()/24;
			int minutes = seconds/60;
			seconds %= 60;
			Broodwar->sendText("%.2d:%.2d: %s creates a %s", minutes, seconds, u->getPlayer()->getName().c_str(), u->getType().c_str());
		}
	}
}

void LBot::onUnitDestroy(BWAPI::Unit u)
{	
	static int lastChecked = 0;

	// Upon destroying of unit belonging to player
	if (u->getPlayer() == Broodwar->self())
	{
		// Unitset management
		if (u->getType().isWorker())
		{
			allWorkers.erase(u);

			// Make sure to remove worker from assigned resource unitset
			if (minWorkers.contains(u))
			{
				minWorkers.erase(u);
			}
			if (gasWorkers.contains(u))
			{
				gasWorkers.erase(u);
			}
		}
		else if (u->getType().isBuilding())
		{
			allBuildings.erase(u);
			// REBUILD BUILDING			
		}
		else if ((!u->getType().isWorker() && !u->getType().isBuilding()) && army1.contains(u))
		{
			army1.erase(u);
		}
		else if ((!u->getType().isWorker() && !u->getType().isBuilding()) && army2.contains(u))
		{
			army2.erase(u);
		}
	}
}

void LBot::onUnitMorph(BWAPI::Unit u)
{
	if (Broodwar->isReplay())
	{
		// if we are in a replay, then we will print out the build order of the structures
		if (u->getType().isBuilding() && !u->getPlayer()->isNeutral())
		{
			int seconds = Broodwar->getFrameCount()/24;
			int minutes = seconds/60;
			seconds %= 60;
			Broodwar->sendText("%.2d:%.2d: %s morphs a %s", minutes, seconds, u->getPlayer()->getName().c_str(), u->getType().c_str());
		}
	}
}

//void LBot::onUnitRenegade(BWAPI::Unit u)
//{
//}

void LBot::onSaveGame(std::string gameName)
{
	Broodwar << "The game was saved to \"" << gameName << "\"" << std::endl;
}

void LBot::onUnitComplete(BWAPI::Unit u)
{
	// Upon creation of unit belonging to player
	if (u->getPlayer() == Broodwar->self())
	{
		// Unitset management
		if (u->getType().isWorker())
		{
			// Add worker to worker unitset
			allWorkers.insert(u);
		}
		else if (u->getType().isBuilding())
		{
			// Add building to building unitset
			allBuildings.insert(u);
		}
		// If army1 isnt full
		else if ((!u->getType().isWorker() && !u->getType().isBuilding()) && army1.size() != 12)
		{
			// Add unit to army1
			army1.insert(u);
		}
		// If army1 is full and army2 isnt
		else if ((!u->getType().isWorker() && !u->getType().isBuilding()) && army1.size() == 12 && army2.size() != 12)
		{
			// Add unit to army2
			army2.insert(u);
		}
	}
}