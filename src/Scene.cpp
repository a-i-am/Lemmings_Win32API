#include "pch.h"
#include "Scene.h"
#include "Actor.h"


// ��¥�� �����ϴ� actor �����̳ʿ� �߰�
void Scene::addActor(Actor* actor)
{
	actor->init();
	// ���� �����ϴ� _actor �����̳ʿ� �ٷ� �����ʴ´�.
	// Update �������� _actor �����̳ʸ� ��ȸ���ϼ��� �ֱ⶧����
	// �����ϰ� ����ϱ� ���ؼ� ���� �ý����� ����Ѵ�.
	_actors.insert(actor);
}