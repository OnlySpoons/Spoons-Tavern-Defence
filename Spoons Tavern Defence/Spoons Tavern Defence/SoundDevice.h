#pragma once

#include "AL/alc.h"
#include "AL/al.h"

#include <iostream>

namespace spty {

	class SoundDevice 
	{
	public:
		static SoundDevice* get();

	private:
		SoundDevice();
		~SoundDevice();

		ALCdevice* _ALCDevice;
		ALCcontext* _ALCContext;

	};

}