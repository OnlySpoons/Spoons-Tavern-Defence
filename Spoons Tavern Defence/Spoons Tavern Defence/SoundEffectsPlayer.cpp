#include "SoundEffectsPlayer.h"

namespace spty {

	SoundEffectsPlayer::SoundEffectsPlayer()
	{
		alGenSources(1, &source_);
		alSourcei(source_, AL_BUFFER, buffer_);

		alSourcef(source_, AL_ROLLOFF_FACTOR, 6.0f);
		alSourcef(source_, AL_REFERENCE_DISTANCE, 6.0f);
		alSourcef(source_, AL_MAX_DISTANCE, 50.0f);

		AL_CheckAndThrow();
	}

	SoundEffectsPlayer::SoundEffectsPlayer(glm::vec3 position, glm::vec3 velocity, bool loop)
	{
		alGenSources(1, &source_);
		alSourcei(source_, AL_BUFFER, buffer_);

		alSourcef(source_, AL_ROLLOFF_FACTOR, 6.0f);
		alSourcef(source_, AL_REFERENCE_DISTANCE, 6.0f);
		alSourcef(source_, AL_MAX_DISTANCE, 50.0f);

		AL_CheckAndThrow();

		setPosition(position);
		setVelocity(velocity);
		setLooping(loop);
	}

	SoundEffectsPlayer::~SoundEffectsPlayer()
	{
		stop();
		alSourcei(source_, AL_BUFFER, NULL);
		alDeleteSources(1, &source_);
	}

	void SoundEffectsPlayer::play(const ALuint& bufferToPlay)
	{
		if (isPlaying())
			stop();
		setBufferToPlay(bufferToPlay);
		alSourcePlay(source_);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::stop()
	{
		alSourceStop(source_);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::pause()
	{
		alSourcePause(source_);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::resume()
	{
		alSourcePlay(source_);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::setBufferToPlay(const ALuint& bufferToPlay)
	{
		if (bufferToPlay != buffer_)
		{
			buffer_ = bufferToPlay;
			alSourcei(source_, AL_BUFFER, (ALint)buffer_);
			AL_CheckAndThrow();
		}
	}

	void SoundEffectsPlayer::setLooping(const bool& loop)
	{
		alSourcei(source_, AL_LOOPING, (ALint)loop);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::setPosition(glm::vec3 position)
	{
		alSource3f(source_, AL_POSITION, position.x, position.y, position.z);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::setVelocity(glm::vec3 velocity)
	{
		alSource3f(source_, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
		AL_CheckAndThrow();
	}

	bool SoundEffectsPlayer::isPlaying()
	{
		ALint playState;
		alGetSourcei(source_, AL_SOURCE_STATE, &playState);
		return (playState == AL_PLAYING);
	}

	bool SoundEffectsPlayer::isPlaying(const ALuint& buffer)
	{
		if (buffer != buffer_) return false;

		return isPlaying();
	}

}