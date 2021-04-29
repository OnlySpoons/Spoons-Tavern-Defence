#pragma once

#include <vector>

#include "AL/al.h"
#include "AL/alext.h"

#include "sndfile.h"
#include <inttypes.h>

namespace spty {

	class SoundBuffer
	{
	public:
		static SoundBuffer* get();

		ALuint addSoundEffect(const char* filename);
		bool removeSoundEffect(const ALuint& buffer);

	private:
		SoundBuffer();
		~SoundBuffer();

		std::vector<ALuint> _SoundEffectBuffers;
	};

}