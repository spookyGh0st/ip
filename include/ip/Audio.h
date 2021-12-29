

#ifndef IP_AUDIO_H
#define IP_AUDIO_H

#include <sndfile.h>
#include <portaudio.h>
#include <memory>

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


#endif //IP_AUDIO_H
