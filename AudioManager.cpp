#include "AudioManager.h"
#include "Utils.h"

using namespace System;
using namespace System::Threading;

using namespace std;
using namespace msclr::interop;

AudioManager::AudioManager()
{
    player = new AudioPlayer();
    useResampling = false;
}

void AudioManager::setDefaultAudioDeviceId(int deviceId)
{
    List<AudioDevice^>^ audioDevicesList = getAvailableAudioDevicesList();
    this->defaultAudioDevice = audioDevicesList[deviceId];
}

List<AudioDevice^>^ AudioManager::getAvailableAudioDevicesList()
{
    return availableDevicesList;
}

char* convertStringToChar(System::String^ str)
{
    marshal_context context;
    const char* chars = context.marshal_as<const char*>(str);
    char* copy = _strdup(chars);
    return copy;
}

bool AudioManager::openFile(System::String^ filePath)
{
    delete currentWav;

    AudioFile* audioFile = new AudioFile();
    char* charFilePath = convertStringToChar(filePath);
    currentWav = audioFile->read(charFilePath);

    bool isSuccess = currentWav != nullptr;
    if (!isSuccess)
    {
        log("Error when reading file! File: " + std::string(charFilePath));
        return false;
    }
    isFirstPlayedFile = true;
    return isSuccess;
}

int AudioManager::getNumOfAudioSamples()
{
    return currentWav->num_samples;
}

int AudioManager::getSampleRate()
{
    return currentWav->sample_rate;
}

void AudioManager::setTimeTo(int sample)
{
    player->setTimeTo(sample);
}

void AudioManager::setVolume(float volume)
{
    player->setVolume(volume);
}

void AudioManager::play()
{
    checkNullptr(currentWav, "currentWav");
    if (isFirstPlayedFile)
    {
        int sampleRate = defaultAudioDevice->sampleRate;
        player->play(currentWav, sampleRate, 64, useResampling);
        isFirstPlayedFile = false;
    }
    else 
    {
        player->resume();
    }
}

void AudioManager::pause()
{
    player->pause();
}

void AudioManager::terminate()
{
    player->terminate();
}

List<AudioDevice^>^ AudioManager::getAudioDeviceList()
{
    UINT numOutputDevices = waveOutGetNumDevs();
    List<AudioDevice^>^ devices = gcnew List<AudioDevice^>;

    for (UINT i = 0; i < numOutputDevices; ++i) {
        WAVEOUTCAPS caps;
        MMRESULT result = waveOutGetDevCaps(i, &caps, sizeof(WAVEOUTCAPS));
        if (result == MMSYSERR_NOERROR) {
            AudioDevice^ device = gcnew AudioDevice();
            device->id = i;

            wstring wstr(caps.szPname);
            wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::string str = converter.to_bytes(wstr);
            device->name = gcnew System::String(str.c_str());

            WAVEFORMATEX waveFormat;
            waveFormat.wFormatTag = WAVE_FORMAT_PCM;
            waveFormat.nChannels = 2;
            waveFormat.nSamplesPerSec = 44100;
            waveFormat.nAvgBytesPerSec = 44100 * 2 * 2;
            waveFormat.nBlockAlign = 2 * 2;
            waveFormat.wBitsPerSample = 16;
            waveFormat.cbSize = 0;

            HWAVEOUT hwo;
            MMRESULT openResult = waveOutOpen(&hwo, i, &waveFormat, 0, 0, CALLBACK_NULL);
            if (openResult == MMSYSERR_NOERROR) {
                MMRESULT formatResult = waveOutGetDevCaps(i, &caps, sizeof(WAVEOUTCAPS));
                if (formatResult == MMSYSERR_NOERROR) {
                    device->sampleRate = caps.dwFormats & WAVE_FORMAT_96M08 ||
                                                caps.dwFormats & WAVE_FORMAT_96S08 ||
                                                caps.dwFormats & WAVE_FORMAT_96M16 ||
                                                caps.dwFormats & WAVE_FORMAT_96S16 ? 96000 : 44100;
                }

                waveOutClose(hwo);
            }

            devices->Add(device);
        }
    }

    this->availableDevicesList = devices;
    return devices;
}

