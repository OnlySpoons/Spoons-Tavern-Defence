#include "SoundDevice.h"

namespace spty {

	SoundDevice* SoundDevice::instance_ = nullptr;

	SoundDevice* SoundDevice::get()
	{
		init();
		return instance_;
	}

	void SoundDevice::init()
	{
		if (instance_ == nullptr)
			instance_ = new SoundDevice();
	}

	glm::vec3 SoundDevice::getLocation()
	{
		float x, y, z;
		alGetListener3f(AL_POSITION, &x, &y, &z);
		AL_CheckAndThrow();
		return glm::vec3(x, y, z);
	}

	/// <summary>
	/// Gets the current listener Orientation as 'at' and 'up'
	/// </summary>
	/// <param name="ori"> Return value: Must be a float array with 6 slots available ex: float myvar[6]</param>
	float SoundDevice::getOrientation()
	{
		float ori;
		alGetListenerfv(AL_ORIENTATION, &ori);
		AL_CheckAndThrow();
		return ori;
	}

	float SoundDevice::getGain()
	{
		float curr_gain;
		alGetListenerf(AL_GAIN, &curr_gain);
		AL_CheckAndThrow();
		return curr_gain;
	}

	void SoundDevice::setAttunationModel(int key)
	{
		if (key < 0xD001 || key > 0xD006)
			throw("bad attunation key");

		alDistanceModel(key);
		AL_CheckAndThrow();
	}

	void SoundDevice::setLocation(glm::vec3 position)
	{
		alListener3f(AL_POSITION, position.x, position.y, position.z);
		AL_CheckAndThrow();
	}

	void SoundDevice::setOrientation(glm::vec3 at, glm::vec3 up)
	{
		std::vector<float> ori;
		ori.push_back(at.x);
		ori.push_back(at.y);
		ori.push_back(at.z);
		ori.push_back(up.x);
		ori.push_back(up.y);
		ori.push_back(up.z);
		alListenerfv(AL_ORIENTATION, ori.data());
		AL_CheckAndThrow();
	}

	void SoundDevice::setGain(const float& val)
	{
		// clamp between 0 and 5
		float newVol = val;
		if (newVol < 0.f)
			newVol = 0.f;
		else if (newVol > 5.f)
			newVol = 5.f;

		alListenerf(AL_GAIN, newVol);
		AL_CheckAndThrow();
	}

	SoundDevice::SoundDevice()
	{
		//Create device
		alcDevice_ = alcOpenDevice(nullptr); //nullptr = current device
		if (!alcDevice_)
			throw("Failed to get sound device!");

		//Create context
		alcContext_ = alcCreateContext(alcDevice_, nullptr);
		if (!alcContext_)
			throw("Failed to set sound context!");

		//Make context current
		if (!alcMakeContextCurrent(alcContext_))
			throw("Failed to make sound context current!");

		const ALCchar* name = nullptr;
		if (alcIsExtensionPresent(alcDevice_, "ALC_ENUMERATE_ALL_EXT"))
			name = alcGetString(alcDevice_, ALC_ALL_DEVICES_SPECIFIER);
		if (!name || alcGetError(alcDevice_) != AL_NO_ERROR)
			name = alcGetString(alcDevice_, ALC_DEVICE_SPECIFIER);

		printf("Opened %s\n", name);
	}

	SoundDevice::~SoundDevice()
	{
		//Thomas: might not need this line
		alcDevice_ = alcGetContextsDevice(alcContext_);

		alcMakeContextCurrent(nullptr);
		alcDestroyContext(alcContext_);
		alcCloseDevice(alcDevice_);
	}

}