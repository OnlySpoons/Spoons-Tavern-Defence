#pragma once

#include "AL\al.h"
#include "sndfile.h"
#include "AL\alext.h"

#include <inttypes.h>
#include <vector>

// SoundEffectsLibrary: Singleton class that keeps track of the shorter sounds
// we've loaded into memory. Use the Play function from an instantiation of the
// SoundEffectsPlayer on an ID returned from the load function.

namespace spty {

	class SoundEffectsLibrary
	{
	public:
		static SoundEffectsLibrary* Get();

		ALuint Load(const char* filename);
		bool UnLoad(const ALuint& bufferId);

		SoundEffectsLibrary();
		~SoundEffectsLibrary();
	private:

		std::vector<ALuint> _soundEffectBuffers;
	};

}