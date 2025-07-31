
#pragma once
class MouseManager
{

public:

	virtual void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) = 0;

private:
	int posX, posY;
};

