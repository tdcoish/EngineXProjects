
#include "FSM.h"
#include "Game\Private\GOSystem\GameObject.h"

FSMState::FSMState(FSM* pFSM)
	: mFSM(pFSM)
{
}


FSM::FSM(GameObject* pGameObject)
	: mGO(pGameObject)
	, mCurrent(nullptr)
	, mNext(nullptr)
{
}

FSM::~FSM()
{
}

void FSM::Initialize(FSMState* pState)
{
	// assert when mCurrent is not null?
	mCurrent = pState;
}

void FSM::Next(FSMState* pState)
{
	if (mNext != nullptr)
	{
		delete mNext;
	}

	mNext = pState;
}

void FSM::Update(float fDeltaT)
{
	if (mNext != nullptr)
	{
		mCurrent->OnExit();
		delete mCurrent;

		mCurrent = mNext;
		mCurrent->OnEnter();

		mNext = nullptr;
	}

	mCurrent->Update(fDeltaT);
}