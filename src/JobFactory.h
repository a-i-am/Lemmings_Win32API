#pragma once

#include "Job.h"
#include "Singleton.h"


class JobFactory
{

public:
	Job* CreateWalkerJob();
	Job* CreateDiggerJob();
	Job* CreateEscaperJob();
	Job* CreateFallerJob();

	//Job* createExploderJob();
	//Job* createMinerJob();
	//Job* createFloaterJob();
	//Job* createBasherJob();
	//Job* createBlockerJob();
	//Job* createClimberJob();
	//Job* createBuilderJob();
};

