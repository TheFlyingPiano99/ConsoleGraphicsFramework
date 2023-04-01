#include "AudioPlayer.h"
#include <mmsystem.h>

namespace cgf {

	AudioPlayer::AudioPlayer()
	{
		hmod = GetModuleHandle("audioResources.rc");
	}

	AudioPlayer::~AudioPlayer()
	{
		PlaySound(NULL, NULL, NULL);
	}
	
	void AudioPlayer::playAudio(const std::string& sourceName, SourceType type)
	{
		switch (type) {
		case SourceType::file:
			PlaySound(sourceName.c_str(), NULL, SND_ASYNC);
			break;
		case SourceType::resource:
			PlaySound(sourceName.c_str(), hmod, SND_RESOURCE | SND_ASYNC);
			break;
		default:
			break;
		}
	}

}
