#include<SFML\Audio.hpp>
using namespace std;
using namespace sf;

class SoundManager
{

public:
	void init();

	SoundBuffer mSwapBuffer;
	Sound mSwapSound;

	SoundBuffer mRemoveBuffer;
	Sound mRemoveSound;
 
};