#pragma once
#include "Singleton.h"

class ParticleSystemManager : public Singleton<ParticleSystemManager>
{
	friend Singleton<ParticleSystemManager>;
	
private: 
	ParticleSystemManager(){}



};

