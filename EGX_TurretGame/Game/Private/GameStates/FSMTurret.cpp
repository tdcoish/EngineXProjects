
#include "FSMTurret.h"
#include "Game\Private\COG\COGTurret.h"

/***************************************************************************
For right now, we're not going to be putting any OnExit, or OnEnter functions in 
our turret. I imagine that these might be used for a transition animation, or sound
playing, but I can't think of anything relevant for this simple game. I mean, there
aren't really any transitions worth talking about here.
***************************************************************************/

FSMTurretRegular::FSMTurretRegular(FSM* pFSM)
	: FSMState(pFSM)
{}

FSMTurretGrenadeShot::FSMTurretGrenadeShot(FSM* pFSM)
	: FSMState(pFSM)
{}

FSMTurretHyperSpeed::FSMTurretHyperSpeed(FSM* pFSM)
	: FSMState(pFSM)
{}


void FSMTurretRegular::Update(float fDeltaT) {

	COGTurret* pTur = mFSM->GetGO()->FindComponent<COGTurret>(ComponentType::Turret);

	// if the user presses spacebar, go to the next state
	InputManager* pInput = InputManager::getInstance();
	if (pInput->kStore & pInput->RMB) {
		mFSM->Next(mFSM->Create<FSMTurretGrenadeShot>());
		return;
	}

	// Here actually do the turret things for regular shooting.
	if (pInput->kStore & pInput->LMB) {
		// If we aren't cooling down
		if ((pTur->time - pTur->lastPlasmoidShot) > pTur->plasmaShotInterval) {
			pTur->ShootPlasmoid();
		}
	}
}

// Considering writing an GetKey type function that is only true for one frame. Kind of irritating having to be lightning quick here.
void FSMTurretGrenadeShot::Update(float fDeltaT) {
	COGTurret* pTur = mFSM->GetGO()->FindComponent<COGTurret>(ComponentType::Turret);

	InputManager* pInput = InputManager::getInstance();
	if (pInput->msRightClickedThisFrame) {
		mFSM->Next(mFSM->Create<FSMTurretHyperSpeed>());
		//mFSM->Next(mFSM->Create<FSMTurretRegular>());
		return;
	}

	if (pInput->kStore & pInput->LMB) {
		// If we aren't cooling down
		if ((pTur->time - pTur->lastGrenadeShot) > pTur->grenadeShotInterval) {
			pTur->ShootGrenade();
		}
	}

	if (pInput->kStore & pInput->kShift) {
		// If we aren't cooling down
		if ((pTur->time - pTur->lastGrenadeShot) > pTur->grenadeShotInterval) {
			pTur->ShootGrenade();
		}
	}
}

// not implemented
void FSMTurretHyperSpeed::Update(float fDeltaT) {

	COGTurret* pTur = mFSM->GetGO()->FindComponent<COGTurret>(ComponentType::Turret);

	//pTur->hyperShotCurrentTime += fDeltaT;

	InputManager* pInput = InputManager::getInstance();
	/*if (pInput->kStore & pInput->RMB) {
		mFSM->Next(mFSM->Create<FSMTurretRegular>());
		return;
	}*/

	if (pInput->msRightClickedThisFrame) {
		mFSM->Next(mFSM->Create<FSMTurretRegular>());
		return;
	}

	// Here actually do the turret things for regular shooting, just faster
	if (pInput->kStore & pInput->LMB) {
		// If we aren't cooling down
		if ((pTur->time - pTur->lastPlasmoidShot) > pTur->hyperShotInterval) {
			pTur->ShootPlasmoid();
		}
	}

	// And here, if our hyper speed has expired, back to regular turret.
	if (pTur->time - pTur->hyperShotCurrentTime > pTur->hyperShotMaxDuration) {
		mFSM->Next(mFSM->Create<FSMTurretRegular>());
		// maybe do an on-exit function as well.
	}
}

// Fill these in later, if at all.
void FSMTurretRegular::OnExit() { }
void FSMTurretGrenadeShot::OnExit() { }
void FSMTurretHyperSpeed::OnExit() { }


// Ah, luckily we actually do need an OnEnter, because the turret hyper speed has a limited duration.
void FSMTurretHyperSpeed::OnEnter() {
	COGTurret* pTur = mFSM->GetGO()->FindComponent<COGTurret>(ComponentType::Turret);
	pTur->hyperShotCurrentTime = pTur->time;

	pTur->mState = HYPER;
}

// Actually, it turns out we need all of them, because we need to store the currently active state in the turret script,
// So that the graphics component can properly render all this.

void FSMTurretRegular::OnEnter() {
	mFSM->GetGO()->FindComponent<COGTurret>(ComponentType::Turret)->mState = REGULAR;
}

void FSMTurretGrenadeShot::OnEnter() {
	mFSM->GetGO()->FindComponent<COGTurret>(ComponentType::Turret)->mState = GRENADE;
}






