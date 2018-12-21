#pragma once

class FSM;
class GameObject;

//
// base state for FSM
//

class FSMState
{
public:

	FSMState(FSM* pFSM);
	virtual ~FSMState() { }

	virtual void OnEnter() { }			// gets called when enters
	virtual void OnExit() { }			// gets called when exits

	virtual void Update(float fDeltaT) { }

protected:

	FSM * mFSM;
	
};

//
// the FSM itself, it can create states and transition between them
//


class FSM
{
public:

	FSM(GameObject* pGameObject);
	~FSM();

	void Initialize(FSMState* pState);
	void Next(FSMState* pState);

	void Update(float fDeltaT);

	template<class T>
	T* Create()
	{
		return new T(this);
	}

	GameObject* GetGO() { return mGO; }

private:

	GameObject * mGO;		// this could be the COG that contains the FSM

	FSMState* mCurrent;
	FSMState* mNext;

};

