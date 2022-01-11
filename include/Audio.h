

#ifndef IP_AUDIO_H
#define IP_AUDIO_H

#include <sndfile.h>
#include <portaudio.h>
#include <memory>
#include <vector>
#include <chrono>
#include "kissfft/kiss_fftr.h"

static int paCallback(
        const void *inputBuffer,
        void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData
);

class AudioFile{
public:
    explicit AudioFile(const std::string& path);
    ~AudioFile();

    SNDFILE *sndFile;
    SF_INFO sfInfo;
    unsigned long position { 0 };

    void checkSfError(int err) const;
    void read(unsigned long framesPerBuffer, float *cursor);
};

class AudioPlayback {
public:
    explicit AudioPlayback(AudioFile *audioFile);
    ~AudioPlayback();
    void play();
    void pause();
private:
    PaStream *stream{};
    AudioFile *audioFile ;
};

#define NFFT 64

struct AudioData{
    float leftTotal;
    float rightTotal;
    float spectogram[NFFT/2];
};

class AudioSync {
public:
    explicit AudioSync(const std::string& path);
    ~AudioSync();
    AudioFile audioPlaybackFile;
    AudioFile audioVisualizerFile;
    AudioPlayback audioPlayback;
    kiss_fftr_cfg kissFftrCfg;
    AudioData read(float dt);
private:
    std::vector<float> audioBuffer {};
    float timedata[NFFT];

    kiss_fft_cpx fftOut[NFFT];
};


#endif //IP_AUDIO_H
