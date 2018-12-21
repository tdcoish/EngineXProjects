#pragma once 

#include "FSM.h"
#include "Game/Public/InputManager.h"

// To be honest, none of the turret states really do anything on enter or exit.
class FSMTurretRegular : public FSMState
{
public:
	FSMTurretRegular(FSM* pFSM);
	virtual void OnEnter() override;			// gets called when enters
	virtual void OnExit() override;				// gets called when exits

	virtual void Update(float fDeltaT) override;
};

class FSMTurretGrenadeShot : public FSMState {
public:

	FSMTurretGrenadeShot(FSM* pFSM);
	//~FSMTurretGrenadeShot();

	virtual void OnEnter() override;			// gets called when enters
	virtual void OnExit() override;				// gets called when exits

	virtual void Update(float fDeltaT);
};

class FSMTurretHyperSpeed : public FSMState {
public:
	FSMTurretHyperSpeed(FSM* pFSM);

	virtual void OnEnter() override;			// gets called when enters
	virtual void OnExit() override;				// gets called when exits

	virtual void Update(float fDeltaT) override;
};
