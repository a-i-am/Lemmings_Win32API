#pragma once
class KeyboardManager
{

public:
	virtual void keyPressed(int32 key) = 0;
	virtual void keyReleased(int32 key) = 0;
	virtual void specialKeyPressed(int32 key) = 0;
	virtual void specialKeyReleased(int32 key) = 0;
};
