#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include "AL/al.h"
#include "AL/alext.h"
#include "sndfile.h"
#include "OpenALErrorCheck.h"

#include <cstddef>
#include <malloc.h>

namespace spty {

	class MusicBuffer
	{
		static constexpr int BUFFER_SAMPLES = 8192;
		static constexpr int NUM_BUFFERS = 4;

	//Variables
	private:
		ALuint source_;
		ALuint buffers_[NUM_BUFFERS];
		SNDFILE* sndFile_;
		SF_INFO sfInfo_;
		short* memBuffer_;
		ALenum format_;

	//Functions
	public:
		//Constructors
		MusicBuffer() = delete;
		MusicBuffer(const char* filename);

		//Destructor
		~MusicBuffer();

		void play();
		void pause();
		void stop();
		void resume();

		void updateBufferStream();

		ALint getSource();

		bool isPlaying();

		void setGain(const float& val);
	};

}