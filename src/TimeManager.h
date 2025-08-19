#pragma once

#include "Singleton.h"

// �ð� ������ ���α׷��� ����ִ��� �����ϰ� �Ѱ��� ����
// 
// 
// �ǽ� : Ÿ�̸� �ý���, ����ٰ� �ڵ� �߰��Ͻø� �ǿ�.
// Ÿ�̸Ӱ� �� �︮��, �ݹ� �ý��� ���.

using TimerFunc = std::function<void()>;	// �Լ������� or std::function

class Timer
{
public:
	Timer(TimerFunc func, float interval, bool loop) : _func(func), _interval(interval), _loop(loop) {}

	// ��ȯ�� : Ÿ�̸Ӱ� ����Ǿ����� (true : ����, false:����)
	bool update(float deltaTime);

private:
	//@TODO: �ݹ� �޴� ��ü�� ���� �ֱ⵵ �Ű��� �Ѵ�.
	// ����, Ÿ�̸Ӱ� ������� �Ǹ�, �ݹ�޴� ��ü���� �˷��� �Ҽ��� �ִ�.
	// �ݹ� �ý����� ����ϰ� �Ǹ�, �� �����ֱ⿡ ���ؼ� �Ű��� ����.
	// �װ� ������ ����Ʈ ������ ����ϴ°͵� ���� �ȴ�.
	TimerFunc	_func;


	float		_sumTime = 0;
	float		_interval = 0;
	bool		_loop = false;
};

class TimeManager : public Singleton<TimeManager>
{
	friend Singleton<TimeManager>;

private:
	TimeManager() {}

public:
	void init();
	void update();
	void destroy();

	uint32 getFps() { return _fps; }
	float getDeltaTime() { return _deltaTime; }

	// Ÿ�̸Ӹ� ����س���, ����� ��ü ��ü�� ��������� �����ϱ�, ����ó���� �ؾ��Ѵ�.
	Timer* addTimer(TimerFunc func, float interval, bool loop);

private:
	uint64 _frequency = 0;	// CPU Ŭ��
	uint64 _prevCount = 0;

	// ���������Ӱ� ���� ������ ������ �ð� ����
	float _deltaTime = 0.0f;

private:

	// �ʴ� �� ����������
	uint32 _frameCount = 0;
	float _frameTime = 0.f;
	uint32 _fps = 0;

	// Ÿ�̸� ����
	unordered_set<Timer*> _timers;
};

