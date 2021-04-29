#include "SoundDevice.h"

namespace spty {

	SoundDevice* SoundDevice::get()
	{
		static SoundDevice* sndDevice = new SoundDevice();
		return sndDevice;
	}

	SoundDevice::SoundDevice()
	{
		_ALCDevice = alcOpenDevice(nullptr);
		if (!_ALCDevice)
			throw("Failed to get sound device!");

		_ALCContext = alcCreateContext(_ALCDevice, nullptr);
		if (!_ALCContext)
			throw("Failed to set sound context!");

		if (!alcMakeContextCurrent(_ALCContext))
			throw("Failed to make sound context current!");

		const ALCchar* name = nullptr;
		if (alcIsExtensionPresent(_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
			name = alcGetString(_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
		if (!name || alcGetError(_ALCDevice) != AL_NO_ERROR)
			name = alcGetString(_ALCDevice, ALC_DEVICE_SPECIFIER);

		printf("Opened \"%s\"\n", name);
	}

	SoundDevice::~SoundDevice()
	{
		if (!alcMakeContextCurrent(nullptr))
			throw("Failed to set sound context to nullptr");

		alcDestroyContext(_ALCContext);
		if (_ALCContext)
			throw("Failed to unset sound context during close!");

		if (!alcCloseDevice(_ALCDevice))
			throw("Failed to close sound device!");
	}

}