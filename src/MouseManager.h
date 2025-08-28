#pragma once
class MouseManager
{

public:

	virtual void mouseMoved(int32 mouseX, int32 mouseY, bool bLeftButton, bool bRightButton) = 0;

private:
	int32 posX, posY;
};
