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
	// Display the game frame rate as text in the upper left area of the screen
	Broodwar->drawTextScreen(200, 0,  "FPS: %d", Broodwar->getFPS());

	// Return if the game is a replay or is paused
	if (Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self())
		return;

	// Prevent spamming by only running our onFrame once every number of latency frames.
	// Latency frames are the number of frames before commands are processed.
	if (Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0)
		return;

	buildOrder->buildOrder();

	// Iterate through all the units owned by the player
	for (auto &u : Broodwar->self()->getUnits())
	{
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
			// Unitset management
			if (!allWorkers.contains(u))
			{
				// Add to gasWorkers unitset
				allWorkers.insert(u);
			}
			if (u->isGatheringMinerals() && !minWorkers.contains(u))
			{   
				// If worker is in the refinery workers unitset, remove to avoid dupilcate
				if (gasWorkers.contains(u))
				{
					gasWorkers.erase(u);
				}
				// Add to mineral workers unitset
				minWorkers.insert(u);
			}
			if (u->isGatheringGas() && !gasWorkers.contains(u))
			{
				// If worker is in the mineral workers unitset, remove to avoid dupilcate
				if (minWorkers.contains(u))
				{
					minWorkers.erase(u);
				}
				// Add to refinery workers unitset
				gasWorkers.insert(u);
			}

			// If worker is idle
			if (u->isIdle())
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
				else
				{
					workerManager->gatherMinerals(u);
				}				
			}
		}

		/*
		 * Command Center
		 */
		else if (u->getType() == UnitTypes::Terran_Command_Center)
		{
			// Construct workers if idle
			if (u->isIdle() && !u->train(UnitTypes::Terran_SCV))
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

				// Retrieve the supply provider type in the case that we have run out of supplies
				UnitType supplyProviderType = u->getType().getRace().getSupplyProvider();
				static int lastChecked = 0;

				// If we are supply blocked and haven't tried constructing more recently
				if (lastErr == Errors::Insufficient_Supply && lastChecked + 400 < Broodwar->getFrameCount() && Broodwar->self()->incompleteUnitCount(supplyProviderType) == 0)
				{
					lastChecked = Broodwar->getFrameCount();

					// Retrieve a unit that is capable of constructing the supply needed
					Unit supplyBuilder = u->getClosestUnit(GetType == supplyProviderType.whatBuilds().first && (IsIdle || IsGatheringMinerals) && IsOwned);
					
					// If a unit was found
					if (supplyBuilder)
					{
						if (supplyProviderType.isBuilding())
						{
							TilePosition targetBuildLocation = Broodwar->getBuildLocation(supplyProviderType, supplyBuilder->getTilePosition());
							if (targetBuildLocation)
							{
								// Register an event that draws the target build location
								Broodwar->registerEvent([targetBuildLocation,supplyProviderType](Game*)
								{
									Broodwar->drawBoxMap(Position(targetBuildLocation), Position(targetBuildLocation + supplyProviderType.tileSize()), Colors::Blue);
								},
									nullptr,  // condition
									supplyProviderType.buildTime() + 100);  // frames to run

								// Order the builder to construct the supply structure
								supplyBuilder->build(supplyProviderType, targetBuildLocation);
							}
						}
						else
						{
							// Train the supply provider (Overlord) if the provider is not a structure
							supplyBuilder->train(supplyProviderType);
						}
					} // closure: supplyBuilder is valid
				} // closure: insufficient supply
			} // closure: failed to train idle unit
		}
		
		/*
		 * Barracks
		 */
		else if (u->getType() == UnitTypes::Terran_Barracks)
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

		/*
		 * Academy
		 */
		if (u->getType() == UnitTypes::Terran_Academy)
		{
			// Perform research
			buildingManager->researchTech(u);
		}
		
		////** MARINES **//
		//else if (u->getType() == UnitTypes::Terran_Marine)
		//{
		//	// insert unit into army
		//	if (army1.size() < 12) // ALTER TO IF CONTAINS THE UNIT
		//	{
		//		army1.insert(u);
		//	}
		//	else if (army1.size() == 12 && army2.size() < 12)
		//	{
		//		army2.insert(u);
		//	}
		//}

		////** MEDICS **//
		//else if (u->getType() == UnitTypes::Terran_Medic)
		//{
		//	// insert unit into army
		//	if (army1.size() < 12)
		//	{
		//		army1.insert(u);
		//	}
		//	else if (army1.size() == 12 && army2.size() < 12)
		//	{
		//		army2.insert(u);
		//	}
		//}
		
	} // closure: unit iterator		
}

void LBot::onSendText(std::string text)
{
	// Send the text to the game if it is not being processed.
	Broodwar->sendText("%s", text.c_str());

	// Make sure to use %s and pass the text as a parameter,
	// otherwise you may run into problems when you use the %(percent) character!
}

void LBot::onReceiveText(BWAPI::Player player, std::string text)
{
	// Parse the received text
	Broodwar << player->getName() << " said \"" << text << "\"" << std::endl;
}

void LBot::onPlayerLeft(BWAPI::Player player)
{
	// Interact verbally with the other players in the game by
	// announcing that the other player has left.
	Broodwar->sendText("Goodbye %s!", player->getName().c_str());
}

void LBot::onNukeDetect(BWAPI::Position target)
{
	// Check if the target is a valid position
	if ( target )
	{
		// if so, print the location of the nuclear strike target
		Broodwar << "Nuclear Launch Detected at " << target << std::endl;
	}
	else 
	{
		// Otherwise, ask other players where the nuke is!
		Broodwar->sendText("Where's the nuke?");
	}
	// You can also retrieve all the nuclear missile targets using Broodwar->getNukeDots()!
}

// MAY POTENTIALLY FIX THE SCOUTING ISSUE?
//void LBot::onUnitDiscover(BWAPI::Unit unit)
//{
//    //IF ENEMY BASE DISCOVERED, SEND SCOUT HOME?
//}

//void LBot::onUnitEvade(BWAPI::Unit unit)
//{
//}

//void LBot::onUnitShow(BWAPI::Unit unit)
//{
//}

//void LBot::onUnitHide(BWAPI::Unit unit)
//{
//}

// NOTE: Workers and command center that the player starts with counts as being created
void LBot::onUnitCreate(BWAPI::Unit u)
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

	if (Broodwar->isReplay())
	{
		// if we are in a replay, then we will print out the build order of the structures
		if (unit->getType().isBuilding() && !unit->getPlayer()->isNeutral())
		{
			int seconds = Broodwar->getFrameCount()/24;
			int minutes = seconds/60;
			seconds %= 60;
			Broodwar->sendText("%.2d:%.2d: %s creates a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
		}
	}
}

void LBot::onUnitDestroy(BWAPI::Unit u)
{	
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

void LBot::onUnitMorph(BWAPI::Unit unit)
{
	if ( Broodwar->isReplay() )
	{
		// if we are in a replay, then we will print out the build order of the structures
		if ( unit->getType().isBuilding() && !unit->getPlayer()->isNeutral() )
		{
			int seconds = Broodwar->getFrameCount()/24;
			int minutes = seconds/60;
			seconds %= 60;
			Broodwar->sendText("%.2d:%.2d: %s morphs a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
		}
	}
}

//void LBot::onUnitRenegade(BWAPI::Unit unit)
//{
//}

void LBot::onSaveGame(std::string gameName)
{
	Broodwar << "The game was saved to \"" << gameName << "\"" << std::endl;
}

void LBot::onUnitComplete(BWAPI::Unit unit)
{
}