#include "MusicBuffer.h"

namespace spty {

	void MusicBuffer::Play()
	{
		ALsizei i;

		//Clear any AL errors
		alGetError();

		//Rewind source position and clear buffer queue
		alSourceRewind(_Source);
		alSourcei(_Source, AL_BUFFER, 0);

		//Fill buffer queue
		for (i = 0; i < _NUM_BUFFERS; i++)
		{
			//Get data to give to buffer
			sf_count_t slen = sf_readf_short(_SndFile, _MemBuffer, _BUFFER_SAMPLES);
			if (slen < 1)
				break;

			slen *= _SFInfo.channels * (sf_count_t)sizeof(short);
			alBufferData(_Buffers[i], _Format, _MemBuffer, (ALsizei)slen, _SFInfo.samplerate);
		}
		if (alGetError() != AL_NO_ERROR)
		{
			throw("Error buffering for playback!");
		}

		//Queue and start playback
		alSourceQueueBuffers(_Source, i, _Buffers);
		alSourcePlay(_Source);
		if (alGetError() != AL_NO_ERROR)
		{
			throw("Error starting playback!");
		}
	}

	//void MusicBuffer::Pause()
	//{

	//}

	//void MusicBuffer::Stop()
	//{

	//}

	void MusicBuffer::UpdateBufferStream()
	{
		ALint processed, state;

		//Clear error
		alGetError();

		//Get source info
		alGetSourcei(_Source, AL_SOURCE_STATE, &state);
		alGetSourcei(_Source, AL_BUFFERS_PROCESSED, &processed);
		if (alGetError() != AL_NO_ERROR)
		{
			throw("Error checking music source state!");
		}

		//Unqueue and handle each processed buffer
		while (processed > 0)
		{
			ALuint bufid;
			sf_count_t slen;

			alSourceUnqueueBuffers(_Source, 1, &bufid);
			processed--;

			//Read next chunk of data, refull buffer and queue it on source
			slen = sf_readf_short(_SndFile, _MemBuffer, _BUFFER_SAMPLES);
			if (slen > 0)
			{
				slen *= _SFInfo.channels * (sf_count_t)sizeof(short);
				alBufferData(bufid, _Format, _MemBuffer, (ALsizei)slen, _SFInfo.samplerate);
				alSourceQueueBuffers(_Source, 1, &bufid);
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
			alGetSourcei(_Source, AL_BUFFERS_QUEUED, &queued);
			if (queued == 0)
				return;

			alSourcePlay(_Source);
			if (alGetError() != AL_NO_ERROR)
			{
				throw("Error restarting music playback!");
			}
		}
	}

	MusicBuffer::MusicBuffer() 
		: _Source(0), _Buffers(), _SndFile(), _SFInfo(), _MemBuffer(), _Format()
	{}

	MusicBuffer::MusicBuffer(const char* filename) : _Format()
	{
		alGenSources(1, &_Source);
		alGenBuffers(_NUM_BUFFERS, _Buffers);

		std::size_t frameSize;

		_SndFile = sf_open(filename, SFM_READ, &_SFInfo);
		if (!_SndFile)
		{
			throw("Could not open provided music file - check path!");
		}

		//Get sound format and figure out the OpenAL format
		if (_SFInfo.channels == 1)
			_Format = AL_FORMAT_MONO16;
		else if (_SFInfo.channels == 2)
			_Format = AL_FORMAT_STEREO16;
		else if (_SFInfo.channels == 3)
		{
			if (sf_command(_SndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				_Format = AL_FORMAT_BFORMAT2D_16;
		}
		else if (_SFInfo.channels == 4)
		{
			if (sf_command(_SndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				_Format = AL_FORMAT_BFORMAT3D_16;
		}
		if (!_Format)
		{
			sf_close(_SndFile);
			_SndFile = NULL;
			throw("Unsupported channel count from file!");
		}

		frameSize = ((size_t)_BUFFER_SAMPLES * (size_t)_SFInfo.channels) * sizeof(short);
		_MemBuffer = static_cast<short*>(malloc(frameSize));
	}

	MusicBuffer::~MusicBuffer()
	{
		alDeleteSources(1, &_Source);

		if (_SndFile)
			sf_close(_SndFile);

		_SndFile = nullptr;

		free(_MemBuffer);

		alDeleteBuffers(_NUM_BUFFERS, _Buffers);
	}

}