#include "SoundEffectsPlayer.h"

namespace spty {

	SoundEffectsPlayer::SoundEffectsPlayer()
	{
		alGenSources(1, &_source);
		alSourcei(_source, AL_BUFFER, _buffer);
		
		alSourcef(_source, AL_ROLLOFF_FACTOR, 6.0f);
		alSourcef(_source, AL_REFERENCE_DISTANCE, 6.0f);
		alSourcef(_source, AL_MAX_DISTANCE, 50.0f);

		AL_CheckAndThrow();
	}

	SoundEffectsPlayer::SoundEffectsPlayer(glm::vec3 position, glm::vec3 velocity, bool loop)
	{
		alGenSources(1, &_source);
		alSourcei(_source, AL_BUFFER, _buffer);

		alSourcef(_source, AL_ROLLOFF_FACTOR, 6.0f);
		alSourcef(_source, AL_REFERENCE_DISTANCE, 6.0f);
		alSourcef(_source, AL_MAX_DISTANCE, 50.0f);

		AL_CheckAndThrow();

		SetPosition(position);
		SetVelocity(velocity);
		SetLooping(loop);
	}

	SoundEffectsPlayer::~SoundEffectsPlayer()
	{
		Stop();
		alSourcei(_source, AL_BUFFER, NULL);
		alDeleteSources(1, &_source);
	}

	void SoundEffectsPlayer::Play(const ALuint& bufferToPlay)
	{
		if (isPlaying())
			Stop();
		SetBufferToPlay(bufferToPlay);
		alSourcePlay(_source);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::Stop()
	{
		alSourceStop(_source);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::Pause()
	{
		alSourcePause(_source);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::Resume()
	{
		alSourcePlay(_source);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::SetBufferToPlay(const ALuint& bufferToPlay)
	{
		if (bufferToPlay != _buffer)
		{
			_buffer = bufferToPlay;
			alSourcei(_source, AL_BUFFER, (ALint)_buffer);
			AL_CheckAndThrow();
		}
	}

	void SoundEffectsPlayer::SetLooping(const bool& loop)
	{
		alSourcei(_source, AL_LOOPING, (ALint)loop);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::SetPosition(glm::vec3 position)
	{
		alSource3f(_source, AL_POSITION, position.x, position.y, position.z);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::SetVelocity(glm::vec3 velocity)
	{
		alSource3f(_source, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
		AL_CheckAndThrow();
	}

	bool SoundEffectsPlayer::isPlaying()
	{
		ALint playState;
		alGetSourcei(_source, AL_SOURCE_STATE, &playState);
		return (playState == AL_PLAYING);
	}

	bool SoundEffectsPlayer::isPlaying(const ALuint& buffer)
	{
		if (buffer == _buffer)
		{
			return isPlaying();
		}
	}

}