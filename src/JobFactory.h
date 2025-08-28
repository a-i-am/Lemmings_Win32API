#pragma once

#include "Singleton.h"
#include "Job.h" 

class JobFactory
{
public:
	static JobFactory& instance()
	{
		static JobFactory instance;
		return instance;
	};
public:
	Job* CreateWalkerJob();
	//Job* CreateDiggerJob();
	//Job* CreateEscaperJob();
	//Job* CreateFallerJob();

	//Job* createExploderJob();
	//Job* createMinerJob();
	//Job* createFloaterJob();
	//Job* createBasherJob();
	//Job* createBlockerJob();
	//Job* createClimberJob();
	//Job* createBuilderJob();
};

