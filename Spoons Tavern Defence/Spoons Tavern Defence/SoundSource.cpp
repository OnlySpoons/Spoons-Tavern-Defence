#include "SoundSource.h"

#include <iostream>

namespace spty {

	SoundSource::SoundSource()
	{
		alGenSources(1, &_Source);
		alSourcef(_Source, AL_PITCH, _Pitch);
		alSourcef(_Source, AL_GAIN, _Gain);
		alSource3f(_Source, AL_POSITION, _Position[0], _Position[1], _Position[2]);
		alSource3f(_Source, AL_VELOCITY, _Velocity[0], _Velocity[1], _Velocity[2]);
		alSourcei(_Source, AL_LOOPING, _isLooping);
		alSourcei(_Source, AL_PITCH, _Buffer);
	}

	SoundSource::~SoundSource()
	{
		alDeleteSources(1, &_Source);
	}

	void SoundSource::Play(const ALuint bufferToPlay)
	{
		std::cout << "Playing sound!" << std::endl;
		if (bufferToPlay != _Buffer)
		{
			_Buffer = bufferToPlay;
			alSourcei(_Source, AL_BUFFER, (ALint)_Buffer);
		}

		alSourcePlay(_Source);
	}
	
}