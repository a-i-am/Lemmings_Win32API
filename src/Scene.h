#pragma once
class Actor;

class Scene
{


protected:
	void addActor(Actor* actor);
	void removeActor(Actor* actor);


protected:
	// �κ�������� ���Ͱ������� ���� �׸��� �׷������Ҽ��� �־
	unordered_set<Actor*> _actors;	// ���� ��ü�� �ִ� ����
	// ������ ������ �����ؼ� �׸��� ����
	unordered_set<class Actor*> _renderList[(int32)RenderLayer::Max];

	// �߰� ������ ���͵��� ����
	vector<Actor*> _reserveAdd;		// �߰��Ǿ�� �ϴ� ���͵��� ����
	vector<Actor*> _reserveRemove;	// �����Ǿ�� �ϴ� ���͵��� ����
};

