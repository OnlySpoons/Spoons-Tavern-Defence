#pragma once

#include <AL/alc.h>
#include <AL/al.h>
#include <iostream>

namespace spty {

	static const char* openAlErrorToString(int err) {
		switch (err) {
		case AL_NO_ERROR: return "AL_NO_ERROR";
		case AL_INVALID_ENUM: return "AL_INVALID_ENUM";
		case AL_INVALID_VALUE: return "AL_INVALID_VALUE";
		case AL_INVALID_OPERATION: return "AL_INVALID_OPERATION";
		case AL_OUT_OF_MEMORY: return "AL_OUT_OF_MEMORY";
			/* ... */
		default:
			return "Unknown error code";
		}
	}

	static void ALC_CheckAndThrow(ALCdevice* device)
	{
		if (alcGetError(device) != ALC_NO_ERROR)
		{
			throw("Error with alcDevice!");
		}
	}


	static void AL_CheckAndThrow()
	{
		int err = alGetError();
		if (err != AL_NO_ERROR)
		{
			throw( openAlErrorToString( err ) );
		}
	}

}