#pragma once

#include <windows.h>
#include <string>
#include <locale>
#include <codecvt>
#include <msclr/marshal.h>

#include "AudioPlayer.h"
#include "AudioFile.h"

using namespace System::Collections::Generic;

#pragma comment(lib, "winmm.lib")

public ref class AudioManager
{
private:
    AudioPlayer* player;
    AudioDevice^ defaultAudioDevice;
    List<AudioDevice^>^ availableDevicesList;

    AudioFile::WavData* currentWav = nullptr;
    bool isFirstPlayedFile = true;
public:
    AudioManager();

    bool useResampling;

    void play();

    void pause();

    void terminate();

    void setTimeTo(int sample);

    bool openFile(System::String^ filePath);

    int getNumOfAudioSamples();

    int getSampleRate();

    void setVolume(float volume);

    List<AudioDevice^>^ getAudioDeviceList();

    void setDefaultAudioDeviceId(int deviceId);

    List<AudioDevice^>^ getAvailableAudioDevicesList();

};