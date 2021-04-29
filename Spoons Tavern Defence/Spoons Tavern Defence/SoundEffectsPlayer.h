#pragma once

#include "AL/al.h"
#include "OpenALErrorCheck.h"

#include <iostream>

namespace spty {

	class SoundEffectsPlayer
	{
	public:
		SoundEffectsPlayer();
		~SoundEffectsPlayer();

		void Play(const ALuint& bufferToPlay);
		void Stop();
		void Pause();
		void Resume();

		void SetBufferToPlay(const ALuint& bufferToPlay);
		void SetLooping(const bool& loop);
		void SetPosition(const float& x, const float& y, const float& z);

		bool isPlaying();

	private:
		ALuint _Source;
		ALuint _Buffer = 0;
	};

}