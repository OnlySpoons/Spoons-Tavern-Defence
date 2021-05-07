#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include "AL\al.h"
#include "sndfile.h"
#include "AL\alext.h"

#include <inttypes.h>
#include <vector>

namespace spty {

	class SoundEffectsLibrary
	{
	//Variables
	private:

		static std::vector<ALuint> soundEffectBuffers_;

	//Functions
	public:

		static ALuint load(const char* filename);
		static bool unLoad(const ALuint& bufferId);

		static void clearBuffers();

		static void deleteBuffers();
	};

}