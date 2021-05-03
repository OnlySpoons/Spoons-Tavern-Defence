#pragma once
#include <iostream>
#include <vector>
#include <glm/ext/vector_float3.hpp>

#include "AL/alc.h"
#include "AL/al.h"
#include "OpenALErrorCheck.h"


namespace spty {

	class SoundDevice 
	{
	public:
		static void init();
		static SoundDevice* get();

		glm::vec3 GetLocation();
		float GetOrientation();
		float GetGain();

		void SetAttunation( int key );
		void SetLocation( glm::vec3 position );
		void SetOrientation( glm::vec3 at, glm::vec3 up );
		void SetGain( const float& val );

		SoundDevice();
		~SoundDevice();
	private:
		static SoundDevice* _instance;

		ALCdevice* _alcDevice;
		ALCcontext* _alcContext; 
	};

}