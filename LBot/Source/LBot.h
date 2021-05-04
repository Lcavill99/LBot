#pragma once
#include <BWAPI.h>
#include "BuildOrder.h"
#include "ScoutManager.h"
#include "WorkerManager.h"
#include "BuildingManager.h"
#include "ArmyManager.h"

class LBot : public BWAPI::AIModule
{	
	BuildOrder *buildOrder;
	ScoutManager *scoutManager;
	WorkerManager *workerManager;
	BuildingManager *buildingManager;
	ArmyManager *armyManager;
	
	BWAPI::Unit scout;

public:
  virtual void onStart();
  virtual void onEnd(bool isWinner);
  virtual void onFrame();
  virtual void onSendText(std::string txt);
  virtual void onReceiveText(BWAPI::Player p, std::string txt);
  virtual void onPlayerLeft(BWAPI::Player p);
  virtual void onNukeDetect(BWAPI::Position t);
  //virtual void onUnitDiscover(BWAPI::Unit u);
  //virtual void onUnitEvade(BWAPI::Unit u);
  //virtual void onUnitShow(BWAPI::Unit u);
  //virtual void onUnitHide(BWAPI::Unit u);
  virtual void onUnitCreate(BWAPI::Unit u);
  virtual void onUnitDestroy(BWAPI::Unit u);
  virtual void onUnitMorph(BWAPI::Unit u);
  //virtual void onUnitRenegade(BWAPI::Unit u);
  virtual void onSaveGame(std::string gameName);
  virtual void onUnitComplete(BWAPI::Unit u);
};
