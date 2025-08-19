#include "pch.h"
#include "TimeManager.h"

void TimeManager::init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount)); // CPU Ŭ��
}

void TimeManager::update()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	// ��������(FPS ����� ����)
	_frameCount++;
	_frameTime += _deltaTime;

	// 1�ʴ� ������ ī��Ʈ�� ���´�.
	if (_frameTime >= 1.0f)
	{
		_fps = _frameCount;
		_frameTime -= 1.0f;
		_frameCount = 0;
	}

	// Ÿ�̸� ����
	for (auto iter = _timers.begin(); iter != _timers.end();)
	{
		Timer* timer = *iter;
		if (false == timer->update(_deltaTime))
		{
			// ����� Ÿ�̸�
			iter = _timers.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void TimeManager::destroy()
{
	for (auto iter : _timers)
	{
		SAFE_DELETE(iter);
	}
	_timers.clear();
}

Timer* TimeManager::addTimer(TimerFunc func, float interval, bool loop)
{
	Timer* timer = new Timer(func, interval, loop);
	_timers.insert(timer);

	return timer;
}

bool Timer::update(float deltaTime)
{
	_sumTime += deltaTime;
	if (_sumTime >= _interval)
	{
		// �˶��� ������ϴ� �ð��� �Ǹ�, �ݹ� ȣ��
		_func();

		if (_loop)
		{
			_sumTime -= _interval;
		}
		else
		{
			return false;
		}
	}

	return true;
}
