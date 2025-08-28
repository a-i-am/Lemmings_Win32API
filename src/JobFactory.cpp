#include "pch.h"
#include "JobFactory.h"
#include "Walker.h"
#include "Digger.h"
#include "Escaper.h"
#include "Faller.h"

Job* JobFactory::CreateWalkerJob()
{
	Walker* walkerJob = new Walker();
	//walkerJob->InitAnims(owner);
	return walkerJob;
}

//Job* JobFactory::CreateDiggerJob()
//{
//	Digger* diggerJob = new Digger();
//	return diggerJob;
//}

//Job* JobFactory::CreateEscaperJob()
//{
//	Escaper* escaperJob = new Escaper();
//	return escaperJob;
//}

//Job* JobFactory::CreateFallerJob()
//{
//	Faller* fallerJob = new Faller();
//	return fallerJob;
//}
