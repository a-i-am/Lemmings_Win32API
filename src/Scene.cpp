#include "pch.h"
#include "Scene.h"
#include "Actor.h"


// 진짜로 관리하는 actor 컨테이너에 추가
void Scene::addActor(Actor* actor)
{
	actor->init();
	// 직접 관리하는 _actor 컨테이너에 바로 넣지않는다.
	// Update 로직에서 _actor 컨테이너를 순회중일수도 있기때문에
	// 안전하게 사용하기 위해서 예약 시스템을 사용한다.
	_actors.insert(actor);
}