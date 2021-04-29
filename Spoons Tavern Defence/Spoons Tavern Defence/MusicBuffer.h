#pragma once

#include "AL/al.h"
#include "AL/alext.h"
#include "sndfile.h"

#include <cstddef>
#include <malloc.h>

namespace spty {

	class MusicBuffer
	{
	public:
		void Play();
		//void Pause();
		//void Stop();

		void UpdateBufferStream();

		MusicBuffer();
		MusicBuffer(const char* filename);
		~MusicBuffer();

	private:
		ALuint _Source;
		static const int _BUFFER_SAMPLES = 8192;
		static const int _NUM_BUFFERS = 4;
		ALuint _Buffers[_NUM_BUFFERS];
		SNDFILE* _SndFile;
		SF_INFO _SFInfo;
		short* _MemBuffer;
		ALenum _Format;
	};

}