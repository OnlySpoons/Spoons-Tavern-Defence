#include "SoundBuffer.h"

namespace spty {



	SoundBuffer* SoundBuffer::get()
	{
		static SoundBuffer* sndBuffer = new SoundBuffer();
		return sndBuffer;
	}

	ALuint SoundBuffer::addSoundEffect(const char* filename)
	{
		ALenum err, format;
		ALuint buffer;
		SNDFILE* sndfile;
		SF_INFO sfinfo;
		short* memBuffer;
		sf_count_t numFrames;
		ALsizei numBytes;

		//Open audio file and check that it's usable
		sndfile = sf_open(filename, SFM_READ, &sfinfo);
		if (!sndfile)
		{
			fprintf(stderr, "Could not open audio in %s: %s\n", filename, sf_strerror(sndfile));
			return 0;
		}
		if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
		{
			fprintf(stderr, "Bad sample count in %s (% " PRId64 ")\n", filename, sfinfo.frames);
			sf_close(sndfile);
			return 0;
		}

		//Get the sound format and figure out the OpenAL format
		format = AL_NONE;
		if (sfinfo.channels == 1)
			format = AL_FORMAT_MONO16;
		else if (sfinfo.channels == 2)
			format = AL_FORMAT_STEREO16;
		else if (sfinfo.channels == 3)
		{
			if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				format = AL_FORMAT_BFORMAT2D_16;
		}
		else if (sfinfo.channels == 4)
		{
			if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				format = AL_FORMAT_BFORMAT3D_16;
		}
		if (!format)
		{
			fprintf(stderr, "Unsupported channel count: %d\n", sfinfo.channels);
			sf_close(sndfile);
			return 0;
		}

		//Decode the whole audio file to a buffer
		memBuffer = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

		numFrames = sf_readf_short(sndfile, memBuffer, sfinfo.frames);
		if (numFrames < 1)
		{
			free(memBuffer);
			sf_close(sndfile);
			fprintf(stderr, "Failed to read samples in %s (%" PRId64 ")\n", filename, numFrames);
			return 0;
		}
		numBytes = (ALsizei)(numFrames * sfinfo.channels) * (ALsizei)sizeof(short);

		//Buffer audio data into a new buffer object then free data and close file
		buffer = 0;
		alGenBuffers(1, &buffer);
		alBufferData(buffer, format, memBuffer, numBytes, sfinfo.samplerate);

		free(memBuffer);
		sf_close(sndfile);

		//Check and handle errors
		err = alGetError();
		if (err != AL_NO_ERROR)
		{
			fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
			if (buffer && alIsBuffer(buffer))
				alDeleteBuffers(1, & buffer); 
			return 0;
		}

		_SoundEffectBuffers.push_back(buffer);

		return buffer;
	}

	bool SoundBuffer::removeSoundEffect(const ALuint& buffer)
	{
		auto it = _SoundEffectBuffers.begin();
		while (it != _SoundEffectBuffers.end())
		{
			if (*it == buffer)
			{
				alDeleteBuffers(1, &*it);

				it = _SoundEffectBuffers.erase(it);

				return true;
			}
			else
			{
				++it;
			}
		}
		return false;
	}

	SoundBuffer::SoundBuffer()
	{
		_SoundEffectBuffers.clear();
	}

	SoundBuffer::~SoundBuffer()
	{
		alDeleteBuffers(_SoundEffectBuffers.size(), _SoundEffectBuffers.data());
		_SoundEffectBuffers.clear();
	}

}