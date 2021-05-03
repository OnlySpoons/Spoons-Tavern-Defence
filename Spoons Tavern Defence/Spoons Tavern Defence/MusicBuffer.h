#pragma once

#include "AL/al.h"
#include "AL/alext.h"
#include "sndfile.h"
#include "OpenALErrorCheck.h"

#include <cstddef>
#include <malloc.h>

namespace spty {

	class MusicBuffer
	{
	public:
		void Play();
		void Pause();
		void Stop();
		void Resume();

		void UpdateBufferStream();

		ALint getSource();

		bool isPlaying();

		void SetGain(const float& val);

		MusicBuffer(const char* filename);
		~MusicBuffer();

	private:
		ALuint _source;
		static constexpr int BUFFER_SAMPLES = 8192;
		static constexpr int NUM_BUFFERS = 4;
		ALuint _buffers[NUM_BUFFERS];
		SNDFILE* _sndFile;
		SF_INFO _sfInfo;
		short* _memBuffer;
		ALenum _format;

		MusicBuffer() = delete;
	};

}