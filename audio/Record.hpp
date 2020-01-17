/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Record
*/

#ifndef RECORD_HPP_
#define RECORD_HPP_

#include "portaudio.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS (0.04f)
#define NUM_CHANNELS (2)
#define DITHER_FLAG (0)
#define WRITE_TO_FILE (0)
#define PA_SAMPLE_TYPE paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#define NUM_BYTES (3528)

typedef struct
{
    long frameIndex;
    long maxFrameIndex;
    SAMPLE recordedSamples[NUM_BYTES];
} paData;

class Record {

	public:
		Record();
		~Record();
        static int recordCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData);
        static int playCallback(const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo *timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData);
        paData recVoice();
        void playVoice(paData new_data);
        void terminateStream(paData data, PaError err);

	private:
        PaStreamParameters inputParameters, outputParameters;
        PaStream *stream = nullptr;
        PaError err = paNoError;
        paData data;
        int i, totalFrames, numSamples, numBytes;
        SAMPLE max, val;
        double average;
};

#endif /* !RECORD_HPP_ */
