#pragma once
#include <Windows.h>
#include <string>

namespace cgf{
	
	enum class SourceType {
		file,
		resource
	};

	class AudioPlayer
	{
	public:

		AudioPlayer();

		~AudioPlayer();

		void playAudio(const std::string& sourceName, SourceType type);

	private:
		HMODULE hmod;
	};
}

