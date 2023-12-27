#include <vector>

class BaseLevel;
class Timer;

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void addLevel(BaseLevel* level);

	void setLevel(int l);	
	int getLevel() { return currentLevel; }

	void handleInput(Timer* inputTimer);
	void update(Timer* updateTimer);
	void render(Timer* renderTimer);
protected:
	std::vector<BaseLevel*> levels;

	int currentLevel;
};