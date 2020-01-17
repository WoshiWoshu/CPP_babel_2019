/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Record
*/

#include "Record.hpp"

Record::Record()
{
    data.maxFrameIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE;
    data.frameIndex = 0;
    numSamples = totalFrames * NUM_CHANNELS;
    numBytes = numSamples * sizeof(SAMPLE);
    for (i = 0; i < numSamples; i++)
        data.recordedSamples[i] = 0;
    err = Pa_Initialize();
    if (err != paNoError)
        terminateStream(data, err);
    inputParameters.device = Pa_GetDefaultInputDevice();
    if (inputParameters.device == paNoDevice)
        terminateStream(data, err);
    inputParameters.channelCount = 2;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = nullptr;
}

Record::~Record()
{
}

int Record::recordCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
    paData *data = (paData *)userData;
    const SAMPLE *rptr = (const SAMPLE *)inputBuffer;
    SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    long framesToCalc;
    long i;
    int finished;
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

    if (framesLeft < framesPerBuffer) {
        framesToCalc = framesLeft;
        finished = paComplete;
    }
    else {
        framesToCalc = framesPerBuffer;
        finished = paContinue;
    }

    if (inputBuffer == nullptr) {
        for (i = 0; i < framesToCalc; i++) {
            *wptr++ = SAMPLE_SILENCE;
            if (NUM_CHANNELS == 2)
                *wptr++ = SAMPLE_SILENCE;
        }
    }
    else {
        for (i = 0; i < framesToCalc; i++) {
            *wptr++ = *rptr++;
            if (NUM_CHANNELS == 2)
                *wptr++ = *rptr++;
        }
    }
    data->frameIndex += framesToCalc;
    return finished;
}

int Record::playCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
    paData *data = (paData *)userData;
    SAMPLE *rptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    SAMPLE *wptr = (SAMPLE *)outputBuffer;
    unsigned int i;
    int finished;
    unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

    if (framesLeft < framesPerBuffer) {
        for (i = 0; i < framesLeft; i++) {
            *wptr++ = *rptr++;
            if (NUM_CHANNELS == 2)
                *wptr++ = *rptr++;
        }
        for (; i < framesPerBuffer; i++) {
            *wptr++ = 0;
            if (NUM_CHANNELS == 2)
                *wptr++ = 0;
        }
        data->frameIndex += framesLeft;
        finished = paComplete;
    }
    else {
        for (i = 0; i < framesPerBuffer; i++) {
            *wptr++ = *rptr++;
            if (NUM_CHANNELS == 2)
                *wptr++ = *rptr++;
        }
        data->frameIndex += framesPerBuffer;
        finished = paContinue;
    }
    return finished;
}

void Record::terminateStream(paData data, PaError err)
{
    Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "An error occured with portaudio stream " << std::endl;
        std::cerr << "Error number: " << err << std::endl;
        std::cerr << "Error message: " << Pa_GetErrorText(err) << std::endl;
        err = 1;
    }
}

paData Record::recVoice()
{
    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        nullptr,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        recordCallback,
        &data);
    if (err != paNoError)
        terminateStream(data, err);
    err = Pa_StartStream(stream);
    if (err != paNoError)
        terminateStream(data, err);
    fflush(stdout);
    while ((err = Pa_IsStreamActive(stream)) == 1)
        Pa_Sleep(1000);
    if (err < 0)
        err = Pa_CloseStream(stream);
    if (err != paNoError)
        terminateStream(data, err);
    return data;
}

void Record::playVoice(paData new_data)
{
    new_data.frameIndex = 0;
    outputParameters.device = Pa_GetDefaultOutputDevice();
    if (outputParameters.device == paNoDevice)
        terminateStream(new_data, err);
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;
    err = Pa_OpenStream(
        &stream,
        nullptr,
        &outputParameters,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        playCallback,
        &new_data);
    if (err != paNoError)
        terminateStream(new_data, err);
    if (stream) {
        err = Pa_StartStream(stream);
        if (err != paNoError)
            terminateStream(new_data, err);
        while ((err = Pa_IsStreamActive(stream)) == 1)
                Pa_Sleep(100);
        if (err < 0)
            terminateStream(new_data, err);
        err = Pa_CloseStream(stream);
        if (err != paNoError)
            terminateStream(new_data, err);
    }
}
