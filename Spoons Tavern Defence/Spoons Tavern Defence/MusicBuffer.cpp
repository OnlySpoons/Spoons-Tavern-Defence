#include "MusicBuffer.h"

namespace spty {

	void MusicBuffer::play()
	{
		ALsizei i;

		//Clear any AL errors
		alGetError();

		//Rewind source position and clear buffer queue
		alSourceRewind(source_);
		alSourcei(source_, AL_BUFFER, 0);

		//Fill buffer queue
		for (i = 0; i < NUM_BUFFERS; i++)
		{
			//Get data to give to buffer
			sf_count_t slen = sf_readf_short(sndFile_, memBuffer_, BUFFER_SAMPLES);
			if (slen < 1)
				break;

			slen *= sfInfo_.channels * (sf_count_t)sizeof(short);
			alBufferData(buffers_[i], format_, memBuffer_, (ALsizei)slen, sfInfo_.samplerate);
		}

		if (alGetError() != AL_NO_ERROR)
		{
			throw("Error buffering for playback!");
		}

		//Queue and start playback
		alSourceQueueBuffers(source_, i, buffers_);
		alSourcePlay(source_);
		if (alGetError() != AL_NO_ERROR)
		{
			throw("Error starting playback!");
		}
	}

	void MusicBuffer::pause()
	{
		alSourcePause(source_);
		AL_CheckAndThrow();
	}

	void MusicBuffer::stop()
	{
		alSourceStop(source_);
		AL_CheckAndThrow();
	}

	void MusicBuffer::resume()
	{
		alSourcePlay(source_);
		AL_CheckAndThrow();
	}

	void MusicBuffer::updateBufferStream()
	{
		ALint processed, state;

		//Clear error
		alGetError();

		//Get source info
		alGetSourcei(source_, AL_SOURCE_STATE, &state);
		alGetSourcei(source_, AL_BUFFERS_PROCESSED, &processed);
		AL_CheckAndThrow();

		//Unqueue and handle each processed buffer
		while (processed > 0)
		{
			ALuint bufid;
			sf_count_t slen;

			alSourceUnqueueBuffers(source_, 1, &bufid);
			processed--;

			//Read next chunk of data, refull buffer and queue it on source
			slen = sf_readf_short(sndFile_, memBuffer_, BUFFER_SAMPLES);
			if (slen > 0)
			{
				slen *= sfInfo_.channels * (sf_count_t)sizeof(short);
				alBufferData(bufid, format_, memBuffer_, (ALsizei)slen, sfInfo_.samplerate);
				alSourceQueueBuffers(source_, 1, &bufid);
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
			alGetSourcei(source_, AL_BUFFERS_QUEUED, &queued);
			if (queued == 0)
				return;

			alSourcePlay(source_);
			AL_CheckAndThrow();
		}
	}

	ALint MusicBuffer::getSource()
	{
		return source_;
	}

	bool MusicBuffer::isPlaying()
	{
		ALint state;
		alGetSourcei(source_, AL_SOURCE_STATE, &state);
		AL_CheckAndThrow();
		return (state == AL_PLAYING);
	}

	void MusicBuffer::setGain(const float& val)
	{
		float newval = val;
		if (newval < 0)
			newval = 0;
		alSourcef(source_, AL_GAIN, val);
		AL_CheckAndThrow();
	}

	MusicBuffer::MusicBuffer(const char* filename)
		: format_(0)
	{
		alGenSources(1, &source_);
		alGenBuffers(NUM_BUFFERS, buffers_);

		std::size_t frameSize;

		sndFile_ = sf_open(filename, SFM_READ, &sfInfo_);
		if (!sndFile_)
		{
			throw("Could not open provided music file - check path!");
		}

		//Get sound format and figure out the OpenAL format
		if (sfInfo_.channels == 1)
			format_ = AL_FORMAT_MONO16;
		else if (sfInfo_.channels == 2)
			format_ = AL_FORMAT_STEREO16;
		else if (sfInfo_.channels == 3)
		{
			if (sf_command(sndFile_, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				format_ = AL_FORMAT_BFORMAT2D_16;
		}
		else if (sfInfo_.channels == 4)
		{
			if (sf_command(sndFile_, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				format_ = AL_FORMAT_BFORMAT3D_16;
		}
		if (!format_)
		{
			sf_close(sndFile_);
			sndFile_ = NULL;
			throw("Unsupported channel count from file!");
		}

		frameSize = ((size_t)BUFFER_SAMPLES * (size_t)sfInfo_.channels) * sizeof(short);
		memBuffer_ = static_cast<short*>(malloc(frameSize));
	}

	MusicBuffer::~MusicBuffer()
	{
		alSourceStop(source_);
		alDeleteSources(1, &source_);

		if (sndFile_)
			sf_close(sndFile_);

		sndFile_ = nullptr;
		free(memBuffer_);
		alDeleteBuffers(NUM_BUFFERS, buffers_);
	}

}