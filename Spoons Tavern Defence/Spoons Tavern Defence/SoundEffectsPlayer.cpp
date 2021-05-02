#include "SoundEffectsPlayer.h"

namespace spty {

	SoundEffectsPlayer::SoundEffectsPlayer()
	{
		alGenSources(1, &_source);
		alSourcei(_source, AL_BUFFER, _buffer);
		AL_CheckAndThrow();
	}

	SoundEffectsPlayer::~SoundEffectsPlayer()
	{
		alSourceStop(_source);
		alDeleteSources(1, &_source);

		alDeleteBuffers(1, &_buffer);
	}

	void SoundEffectsPlayer::Play(const ALuint& bufferToPlay)
	{
		if (bufferToPlay != _buffer)
		{
			_buffer = bufferToPlay;
			alSourcei(_source, AL_BUFFER, (ALint)_buffer);
			AL_CheckAndThrow();
		}
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

	void SoundEffectsPlayer::SetPosition(const float& x, const float& y, const float& z)
	{
		alSource3f(_source, AL_POSITION, x, y, z);
		AL_CheckAndThrow();
	}

	bool SoundEffectsPlayer::isPlaying()
	{
		ALint playState;
		alGetSourcei(_source, AL_SOURCE_STATE, &playState);
		return (playState == AL_PLAYING);
	}

}