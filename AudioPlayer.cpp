#include "audioplayer.h"
#include "Utils.h"
#include "NotificationManager.h"
#include <string>
#include <samplerate.h>
#include <vector>
#include <algorithm>

AudioPlayer::AudioPlayer()
{
	volume = 1;
}

void setVolumeOfSamples(float* samples, int sampleCount, float scalingFactor)
{
	// Find the maximum absolute value in the samples
	float maxSample = *std::max_element(samples, samples + sampleCount, [](float a, float b) {
		return std::abs(a) < std::abs(b);
		});

	// Calculate the scaling factor to avoid clipping
	float scaleFactor = scalingFactor / maxSample;

	// Apply gain normalization by multiplying each sample by the scaling factor
	std::transform(samples, samples + sampleCount, samples, [scaleFactor](float sample) {
		return sample * scaleFactor;
		});
}

int AudioPlayer::paCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
{
	float* out = (float*)outputBuffer;
	AudioCallbackData* data = (AudioCallbackData*)userData;

	for (unsigned int i = 0; i < framesPerBuffer; i++) {
		if (data->iterator + i < data->buffer.size()) {
			*out++ = data->buffer[data->iterator + i] * (*data->volume);
		}
		else {
			*out++ = 0;
		}
	}

	data->iterator += framesPerBuffer;
	if (data->iterator <= data->buffer.size() + framesPerBuffer)
	{
		NotificationManager::Instance->notify(UPDATE_TIMELINE, (void*)data->iterator);
	}

	return paContinue;
}

void AudioPlayer::setVolume(float volume)
{
	this->volume = volume;
}

void AudioPlayer::play(AudioFile::WavData* wavData, int sampleRate, int framesPerBuffer, bool useResampling)
{
	if (Pa_IsStreamActive(stream) && stream != nullptr) return;
	data = AudioCallbackData();

	Pa_Initialize();

	PaStreamParameters outputParameters;
	// Change to selected device id...
	outputParameters.device = Pa_GetDefaultOutputDevice();
	if (outputParameters.device == paNoDevice)
	{
		Logger::shared().log("Error: No default output device.");
	}

	outputParameters.channelCount = 1;
	outputParameters.sampleFormat = paFloat32;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	if (useResampling)
	{
		wavData->samples = resampleAudioBuffer(wavData->samples, wavData->sample_rate, sampleRate);
	}

	data.buffer = wavData->samples;
	data.iterator = 0;
	data.sampleRate = wavData->sample_rate;
	data.volume = &volume;

	Pa_OpenStream(
		&stream,
		NULL,
		&outputParameters,
		sampleRate,
		framesPerBuffer,
		paClipOff,
		paCallback,
		&data
	);

	Pa_StartStream(stream);

	while (Pa_IsStreamActive(stream))
	{
		Pa_Sleep(100);
	}
}

void AudioPlayer::pause()
{
	if (Pa_IsStreamStopped(stream)) return;
	checkNullptr(stream, "stream");
	Pa_StopStream(stream);
}

void AudioPlayer::resume()
{
	if (!Pa_IsStreamStopped(stream)) return;
	checkNullptr(stream, "stream");
	Pa_StartStream(stream);
}

void AudioPlayer::setTimeTo(int sample)
{
	data.iterator = sample * data.sampleRate;
}

void AudioPlayer::terminate()
{
	checkNullptr(stream, "stream");
	Pa_StopStream(stream);
	Pa_CloseStream(stream);

	Pa_Terminate();

	stream = nullptr;
}

std::vector<float> AudioPlayer::resampleAudioBuffer(const std::vector<float>& inputBuffer, double inputSampleRate, double outputSampleRate)
{
	if (inputSampleRate == outputSampleRate)
	{
		log("Received the same outputSampleRate as a inputSampleRate: " + std::to_string(inputSampleRate));
		return inputBuffer;
	}

	const int inputSize = static_cast<int>(inputBuffer.size());
	const int outputSize = static_cast<int>((inputSize * outputSampleRate) / inputSampleRate);

	std::vector<float> outputBuffer(outputSize);

	SRC_DATA convertData;
	convertData.data_in = const_cast<float*>(inputBuffer.data());
	convertData.input_frames = inputSize;
	convertData.data_out = outputBuffer.data();
	convertData.output_frames = outputSize;
	convertData.src_ratio = outputSampleRate / inputSampleRate;

	int error = src_simple(&convertData, SRC_SINC_BEST_QUALITY, 1);
	if (error != 0)
	{
		log("Error while resampling: " + std::to_string(error));
		return inputBuffer;
	}

	outputBuffer.resize(convertData.output_frames_gen);

	return outputBuffer;
}