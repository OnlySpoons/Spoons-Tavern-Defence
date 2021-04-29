#pragma once

#include "AL/alc.h"
#include "AL/al.h"
#include "OpenALErrorCheck.h"

#include <iostream>
#include <vector>

namespace spty {

#define SD_INIT SoundDevice::init();
#define LISTENER SoundDevice::get()

	class SoundDevice 
	{
	public:
		static void init();
		static SoundDevice* get();

		void GetLocation(float& x, float& y, float& z);
		void GetOrientation(float& ori);
		float GetGain();

		void SetAttunation(int key);
		void SetLocation(const float& x, const float& y, const float& z);
		void SetOrientation(
			const float& atx, const float& aty, const float& atz,
			const float& upx, const float& upy, const float& upz);
		void SetGain(const float& val);

		SoundDevice();
		~SoundDevice();
	private:

		ALCdevice* _ALCDevice;
		ALCcontext* _ALCContext;
	};

}