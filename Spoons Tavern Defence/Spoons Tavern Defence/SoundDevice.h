#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <iostream>
#include <vector>
#include <glm/ext/vector_float3.hpp>

#include "AL/alc.h"
#include "AL/al.h"
#include "OpenALErrorCheck.h"


namespace spty {

	enum AttenuationModel
	{
		Inverse = AL_INVERSE_DISTANCE,
		ClampedInverse = AL_INVERSE_DISTANCE_CLAMPED,
		Linear = AL_LINEAR_DISTANCE,
		ClampedLinear = AL_LINEAR_DISTANCE_CLAMPED,
		Emponent = AL_EXPONENT_DISTANCE,
		ClampedExponent = AL_EXPONENT_DISTANCE_CLAMPED,
	};

	class SoundDevice
	{
	//Variables
	private:
		static SoundDevice* instance_;

		ALCdevice* alcDevice_;
		ALCcontext* alcContext_;

	//Functions
	public:
		//Constructor
		SoundDevice();

		//Destructor
		~SoundDevice();

		static void init();
		static SoundDevice* get();

		glm::vec3 getLocation();
		float getOrientation();
		float getGain();

		void setAttunationModel(int key);
		void setLocation(glm::vec3 position);
		void setOrientation(glm::vec3 at, glm::vec3 up);
		void setGain(const float& val);

	};

}