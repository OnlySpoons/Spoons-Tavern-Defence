#pragma once

#include "AL/al.h"

namespace spty {

	class SoundSource
	{
	public:
		SoundSource();
		~SoundSource();

		void Play(const ALuint bufferToPlay);

	private:
		ALuint _Source;
		float _Pitch = 1.0f;
		float _Gain = 1.0f;
		float _Position[3] = { 0, 0, 0 };
		float _Velocity[3] = { 0, 0, 0 };
		bool _isLooping = false;
		ALuint _Buffer = 0;
	};

}