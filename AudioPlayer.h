#pragma once

#include <portaudio.h>
#include <vector>
#include <iostream>

#include "AudioFile.h"

public ref struct AudioDevice {
    int id;
    System::String^ name;
    int sampleRate;
};

public class AudioPlayer {
public:

    AudioPlayer();

    void play(AudioFile::WavData* wavData, int sampleRate, int framesPerBuffer, bool useResampling);

    void setVolume(float volume);

    void setTimeTo(int sample);

    void pause();

    void resume();

    void terminate();

private:

    static int paCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);

    std::vector<float> resampleAudioBuffer(const std::vector<float>& inputBuffer, double inputSampleRate, double outputSampleRate);

    struct AudioCallbackData {
        std::vector<float> buffer;
        int iterator;
        int sampleRate;
        float* volume;
    };

    AudioCallbackData data;
    AudioFile audioFile;
    PaStream* stream;

    float volume;
};