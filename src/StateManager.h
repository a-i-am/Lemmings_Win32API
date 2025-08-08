#pragma once
#include "Singleton.h"

class StateManager : public Singleton<StateManager>
{
	friend Singleton<StateManager>;

private:	
	StateManager() {}


};


