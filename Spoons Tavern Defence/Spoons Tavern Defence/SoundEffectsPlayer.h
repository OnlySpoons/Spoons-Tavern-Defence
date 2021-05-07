#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <glm/ext/vector_float3.hpp>

#include "AL/al.h"
#include "OpenALErrorCheck.h"


namespace spty {

	using SoundEffect = int;

	class SoundEffectsPlayer
	{
	//Variables
	private:
		ALuint source_;
		ALuint buffer_ = 0;

	//Fucntions
	public:
		//Constructors
		SoundEffectsPlayer();
		SoundEffectsPlayer(glm::vec3 position, glm::vec3 velocity, bool loop = false);

		//Destructor
		~SoundEffectsPlayer();

		void play(const ALuint& bufferToPlay);
		void stop();
		void pause();
		void resume();

		void setBufferToPlay(const ALuint& bufferToPlay);
		void setLooping(const bool& loop);
		void setPosition(glm::vec3 position);
		void setVelocity(glm::vec3 velocity);

		bool isPlaying();
		bool isPlaying(const ALuint& buffer);
	};

}