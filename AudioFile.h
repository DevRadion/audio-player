#pragma once

#include <vector>
#include <sndfile.h>

#include "Logger.h"

class AudioFile {
public:
    struct WavData {
        int sample_rate;
        int num_channels;
        int bits_per_sample;
        int num_samples;
        std::vector<float> samples;
    };

    WavData* read(char* filename);

    void write(std::string filename, WavData& wav_data);
};
