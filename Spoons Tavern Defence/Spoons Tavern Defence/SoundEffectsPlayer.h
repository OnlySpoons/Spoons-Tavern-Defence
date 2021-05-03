#pragma once
#include <glm/ext/vector_float3.hpp>

#include "AL/al.h"
#include "OpenALErrorCheck.h"


namespace spty {

	class SoundEffectsPlayer
	{
	public:
		SoundEffectsPlayer();

		SoundEffectsPlayer(glm::vec3 position, glm::vec3 velocity, bool loop = false);

		~SoundEffectsPlayer();

		void Play(const ALuint& bufferToPlay);
		void Stop();
		void Pause();
		void Resume();

		void SetBufferToPlay(const ALuint& bufferToPlay);
		void SetLooping(const bool& loop);
		void SetPosition(glm::vec3 position);
		void SetVelocity(glm::vec3 velocity);

		bool isPlaying();
		bool isPlaying(const ALuint& buffer);

	private:
		ALuint _source;
		ALuint _buffer = 0;
	};

}