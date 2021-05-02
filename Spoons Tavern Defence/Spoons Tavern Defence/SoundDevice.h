#pragma once

#include "AL/alc.h"
#include "AL/al.h"
#include "OpenALErrorCheck.h"

#include <iostream>
#include <vector>

namespace spty {

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
		static SoundDevice* _instance;

		ALCdevice* _alcDevice;
		ALCcontext* _alcContext; 
	};

}