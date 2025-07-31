
#include "GameState.h"

class Scene : public GameState
{

public:
	void init();
	void update(int deltaTime);
	void render();

private:
	void initMap();
	void initUI();
	void updateUI();

	bool paused = false;
	bool speedUp = false;
};
