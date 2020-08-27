#include "Object.hpp"

class Energy : public virtual OtterEngine::Object
{
public:
	Energy(Vector2d, int);
	~Energy();
	int getValue();
	void updateEvents(OtterEngine::Engine*);
	
private:
	std::vector<OtterEngine::Event<Energy>> _events;
	int _value;
};
