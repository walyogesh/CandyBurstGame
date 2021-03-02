#include "SoundManager.h"
#include "Game/CandyFactory.h"

void SoundManager::init()
{
	mSwapBuffer.loadFromFile(soundDirectory+"Sounds/Drop.wav");
	mRemoveBuffer.loadFromFile(soundDirectory+"Sounds/LYNC_presence.wav");

	mRemoveSound.setBuffer(mRemoveBuffer);
	mSwapSound.setBuffer(mSwapBuffer);

}
