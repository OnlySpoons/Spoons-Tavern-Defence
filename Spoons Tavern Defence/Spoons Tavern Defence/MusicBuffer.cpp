#include "MusicBuffer.h"

namespace spty {

	void MusicBuffer::Play()
	{
		ALsizei i;

		//Clear any AL errors
		alGetError();

		//Rewind source position and clear buffer queue
		alSourceRewind(_source);
		alSourcei(_source, AL_BUFFER, 0);

		//Fill buffer queue
		for (i = 0; i < NUM_BUFFERS; i++)
		{
			//Get data to give to buffer
			sf_count_t slen = sf_readf_short(_sndFile, _memBuffer, BUFFER_SAMPLES);
			if (slen < 1)
				break;

			slen *= _sfInfo.channels * (sf_count_t)sizeof(short);
			alBufferData(_buffers[i], _format, _memBuffer, (ALsizei)slen, _sfInfo.samplerate);
		}
		if (alGetError() != AL_NO_ERROR)
		{
			throw("Error buffering for playback!");
		}

		//Queue and start playback
		alSourceQueueBuffers(_source, i, _buffers);
		alSourcePlay(_source);
		if (alGetError() != AL_NO_ERROR)
		{
			throw("Error starting playback!");
		}
	}

	void MusicBuffer::Pause()
	{
		alSourcePause(_source);
		AL_CheckAndThrow();
	}

	void MusicBuffer::Stop()
	{
		alSourceStop(_source);
		AL_CheckAndThrow();
	}

	void MusicBuffer::Resume()
	{
		alSourcePlay(_source);
		AL_CheckAndThrow();
	}

	void MusicBuffer::UpdateBufferStream()
	{
		ALint processed, state;

		//Clear error
		alGetError();

		//Get source info
		alGetSourcei(_source, AL_SOURCE_STATE, &state);
		alGetSourcei(_source, AL_BUFFERS_PROCESSED, &processed);
		AL_CheckAndThrow();

		//Unqueue and handle each processed buffer
		while (processed > 0)
		{
			ALuint bufid;
			sf_count_t slen;

			alSourceUnqueueBuffers(_source, 1, &bufid);
			processed--;

			//Read next chunk of data, refull buffer and queue it on source
			slen = sf_readf_short(_sndFile, _memBuffer, BUFFER_SAMPLES);
			if (slen > 0)
			{
				slen *= _sfInfo.channels * (sf_count_t)sizeof(short);
				alBufferData(bufid, _format, _memBuffer, (ALsizei)slen, _sfInfo.samplerate);
				alSourceQueueBuffers(_source, 1, &bufid);
			}
			if (alGetError() != AL_NO_ERROR)
			{
				throw("Error buffering music data!");
			}
		}

		//Make sure source hasen't underrun
		if (state != AL_PLAYING && state != AL_PAUSED)
		{
			ALint queued;

			//If no bufferes are queued, playback is finished
			alGetSourcei(_source, AL_BUFFERS_QUEUED, &queued);
			if (queued == 0)
				return;

			alSourcePlay(_source);
			AL_CheckAndThrow();
		}
	}

	ALint MusicBuffer::getSource()
	{
		return _source;
	}

	bool MusicBuffer::isPlaying()
	{
		ALint state;
		alGetSourcei(_source, AL_SOURCE_STATE, &state);
		AL_CheckAndThrow();
		return (state == AL_PLAYING);
	}

	void MusicBuffer::SetGain(const float& val)
	{
		float newval = val;
		if (newval < 0)
			newval = 0;
		alSourcef(_source, AL_GAIN, val);
		AL_CheckAndThrow();
	}

	MusicBuffer::MusicBuffer(const char* filename) 
		: _format(0)
	{
		alGenSources(1, &_source);
		alGenBuffers(NUM_BUFFERS, _buffers);

		std::size_t frameSize;

		_sndFile = sf_open(filename, SFM_READ, &_sfInfo);
		if (!_sndFile)
		{
			throw("Could not open provided music file - check path!");
		}

		//Get sound format and figure out the OpenAL format
		if (_sfInfo.channels == 1)
			_format = AL_FORMAT_MONO16;
		else if (_sfInfo.channels == 2)
			_format = AL_FORMAT_STEREO16;
		else if (_sfInfo.channels == 3)
		{
			if (sf_command(_sndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				_format = AL_FORMAT_BFORMAT2D_16;
		}
		else if (_sfInfo.channels == 4)
		{
			if (sf_command(_sndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				_format = AL_FORMAT_BFORMAT3D_16;
		}
		if (!_format)
		{
			sf_close(_sndFile);
			_sndFile = NULL;
			throw("Unsupported channel count from file!");
		}

		frameSize = ((size_t)BUFFER_SAMPLES * (size_t)_sfInfo.channels) * sizeof(short);
		_memBuffer = static_cast<short*>(malloc(frameSize));
	}

	MusicBuffer::~MusicBuffer()
	{
		alSourceStop(_source);
		alDeleteSources(1, &_source);

		if (_sndFile)
			sf_close(_sndFile);

		_sndFile = nullptr;
		free(_memBuffer);
		alDeleteBuffers(NUM_BUFFERS, _buffers);
	}

}