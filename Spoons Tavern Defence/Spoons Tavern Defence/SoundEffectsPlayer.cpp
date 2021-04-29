#include "SoundEffectsPlayer.h"

namespace spty {

	SoundEffectsPlayer::SoundEffectsPlayer()
	{
		alGenSources(1, &_Source);
		alSourcei(_Source, AL_BUFFER, _Buffer);
		AL_CheckAndThrow();
	}

	SoundEffectsPlayer::~SoundEffectsPlayer()
	{
		alDeleteSources(1, &_Source);
	}

	void SoundEffectsPlayer::Play(const ALuint& bufferToPlay)
	{
		if (bufferToPlay != _Buffer)
		{
			_Buffer = bufferToPlay;
			alSourcei(_Source, AL_BUFFER, (ALint)_Buffer);
			AL_CheckAndThrow();
		}
		alSourcePlay(_Source);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::Stop()
	{
		alSourceStop(_Source);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::Pause()
	{
		alSourcePause(_Source);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::Resume()
	{
		alSourcePlay(_Source);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::SetBufferToPlay(const ALuint& bufferToPlay)
	{
		if (bufferToPlay != _Buffer)
		{
			_Buffer = bufferToPlay;
			alSourcei(_Source, AL_BUFFER, (ALint)_Buffer);
			AL_CheckAndThrow();
		}
	}

	void SoundEffectsPlayer::SetLooping(const bool& loop)
	{
		alSourcei(_Source, AL_LOOPING, (ALint)loop);
		AL_CheckAndThrow();
	}

	void SoundEffectsPlayer::SetPosition(const float& x, const float& y, const float& z)
	{
		alSource3f(_Source, AL_POSITION, x, y, z);
		AL_CheckAndThrow();
	}

	bool SoundEffectsPlayer::isPlaying()
	{
		ALint playState;
		alGetSourcei(_Source, AL_SOURCE_STATE, &playState);
		return (playState == AL_PLAYING);
	}

}