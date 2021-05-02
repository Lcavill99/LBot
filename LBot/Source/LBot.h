#pragma once
#include <BWAPI.h>
#include "BuildOrder.h"
#include "ScoutManager.h"
#include "WorkerManager.h"
#include "BuildingManager.h"
#include "ArmyManager.h"

class LBot : public BWAPI::AIModule
{
	int barracks;
	int depot;
	int refinery;
	int academy;
	int medics;

	BuildOrder *buildOrder;
	ScoutManager *scoutManager;
	WorkerManager *workerManager;
	BuildingManager *buildingManager;
	ArmyManager *armyManager;

public:
  virtual void onStart();
  virtual void onEnd(bool isWinner);
  virtual void onFrame();
  virtual void onSendText(std::string text);
  virtual void onReceiveText(BWAPI::Player player, std::string text);
  virtual void onPlayerLeft(BWAPI::Player player);
  virtual void onNukeDetect(BWAPI::Position target);
  //virtual void onUnitDiscover(BWAPI::Unit unit);
  //virtual void onUnitEvade(BWAPI::Unit unit);
  //virtual void onUnitShow(BWAPI::Unit unit);
  //virtual void onUnitHide(BWAPI::Unit unit);
  virtual void onUnitCreate(BWAPI::Unit u);
  virtual void onUnitDestroy(BWAPI::Unit u);
  virtual void onUnitMorph(BWAPI::Unit unit);
  //virtual void onUnitRenegade(BWAPI::Unit unit);
  virtual void onSaveGame(std::string gameName);
  virtual void onUnitComplete(BWAPI::Unit unit);
};
