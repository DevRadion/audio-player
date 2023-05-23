#include "audiofile.h"
#include <iostream>

AudioFile::WavData* AudioFile::read(char* filename) {
	SF_INFO sfinfo;
	memset(&sfinfo, 0, sizeof(sfinfo));

	SNDFILE* sndfile = sf_open(filename, SFM_READ, &sfinfo);
	if (!sndfile) {
		Logger::shared().log("Error opening WAV file: " + std::string(filename));
		return nullptr;
	}

	WavData* wav_data = new WavData();
	wav_data->sample_rate = sfinfo.samplerate;
	wav_data->num_channels = sfinfo.channels;
	wav_data->bits_per_sample = sfinfo.format & SF_FORMAT_SUBMASK;
	wav_data->num_samples = sfinfo.frames * wav_data->num_channels;

	int buffer_size = wav_data->num_samples * sizeof(float);
	std::vector<float> buffer(buffer_size / sizeof(float));
	sf_readf_float(sndfile, buffer.data(), sfinfo.frames);

	wav_data->samples = buffer;

	sf_close(sndfile);

	return wav_data;
}

void AudioFile::write(std::string filename, AudioFile::WavData& wav_data) {
	SF_INFO sfinfo;
	memset(&sfinfo, 0, sizeof(sfinfo));

	sfinfo.samplerate = wav_data.sample_rate;
	sfinfo.channels = wav_data.num_channels;
	sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;

	SNDFILE* sndfile = sf_open(filename.c_str(), SFM_WRITE, &sfinfo);
	if (!sndfile) {
		Logger::shared().log("Error opening WAV file: " + filename + ", with sf_error:" + (char)sf_error(sndfile));
		return;
	}

	sf_writef_float(sndfile, wav_data.samples.data(), wav_data.num_samples / wav_data.num_channels);

	sf_close(sndfile);
}