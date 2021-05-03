#include "SoundDevice.h"

namespace spty {

	SoundDevice* SoundDevice::_instance = nullptr;

	SoundDevice* SoundDevice::get()
	{
		init();
		return _instance;
	}

	void SoundDevice::init()
	{
		if (_instance == nullptr)
			_instance = new SoundDevice();
	}

	glm::vec3 SoundDevice::GetLocation()
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
	float SoundDevice::GetOrientation()
	{
		float ori;
		alGetListenerfv(AL_ORIENTATION, &ori);
		AL_CheckAndThrow();
		return ori;
	}

	float SoundDevice::GetGain()
	{
		float curr_gain;
		alGetListenerf(AL_GAIN, &curr_gain);
		AL_CheckAndThrow();
		return curr_gain;
	}

	/// <summary>
	/// Sets the Attunation Model.
	/// </summary>
	/// <param name="key">
	///#define AL_INVERSE_DISTANCE                      0xD001
	///#define AL_INVERSE_DISTANCE_CLAMPED              0xD002
	///#define AL_LINEAR_DISTANCE                       0xD003
	///#define AL_LINEAR_DISTANCE_CLAMPED               0xD004
	///#define AL_EXPONENT_DISTANCE                     0xD005
	///#define AL_EXPONENT_DISTANCE_CLAMPED             0xD006
	/// </param>
	void SoundDevice::SetAttunation(int key)
	{
		if (key < 0xD001 || key > 0xD006)
			throw("bad attunation key");

		alDistanceModel(key);
		AL_CheckAndThrow();
	}

	void SoundDevice::SetLocation(glm::vec3 position)
	{
		alListener3f(AL_POSITION, position.x, position.y, position.z);
		AL_CheckAndThrow();
	}

	void SoundDevice::SetOrientation(glm::vec3 at, glm::vec3 up)
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

	void SoundDevice::SetGain(const float& val)
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
		_alcDevice = alcOpenDevice(nullptr); //nullptr = current device
		if (!_alcDevice)
			throw("Failed to get sound device!");

		//Create context
		_alcContext = alcCreateContext(_alcDevice, nullptr);
		if (!_alcContext)
			throw("Failed to set sound context!");

		//Make context current
		if (!alcMakeContextCurrent(_alcContext))
			throw("Failed to make sound context current!");

		const ALCchar* name = nullptr;
		if (alcIsExtensionPresent(_alcDevice, "ALC_ENUMERATE_ALL_EXT"))
			name = alcGetString(_alcDevice, ALC_ALL_DEVICES_SPECIFIER);
		if (!name || alcGetError(_alcDevice) != AL_NO_ERROR)
			name = alcGetString(_alcDevice, ALC_DEVICE_SPECIFIER);

		printf("Opened \"%s\"\n", name);
	}

	SoundDevice::~SoundDevice()
	{
		//Thomas: might not need this line
		_alcDevice = alcGetContextsDevice(_alcContext);

		alcMakeContextCurrent(nullptr);
		alcDestroyContext(_alcContext);
		alcCloseDevice(_alcDevice);
	}

}