#include <iostream>
#include "ip/Audio.h"
#include "ip/log.h"

/* This routine will be called by the PortAudio engine when audioPlayback is needed.
 * It may called at interrupt level on some machines so don't do anything
 * that could mess up the system like calling malloc() or free().
*/
int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
               const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {

    /* Cast data passed through stream to our structure. */
    auto *data = (AudioFile*)userData;
    auto *out = (float *) outputBuffer;
    data->read(framesPerBuffer, out);
    return paContinue;
}

void AudioFile::checkSfError(int err) const{
    if (err != SF_ERR_NO_ERROR){
        logError("LibsndFile error:");
        char errorLog[512];
        sf_error_str(sndFile,errorLog,512);
        logError(errorLog);
    }
}

AudioFile::AudioFile(const std::string& path) {
    sndFile = sf_open(path.c_str(),SFM_READ,&sfInfo);
}

AudioFile::~AudioFile() {
    int err = sf_close(sndFile);
    checkSfError(err);
}

// similar to https://pastebin.com/2TuuU4K3
void AudioFile::read(unsigned long framesPerBuffer, float *cursor) {
    unsigned long thisSize = framesPerBuffer;
    unsigned long thisRead;
    while (thisSize > 0)
    {
        // seek to our current file position
        sf_seek(sndFile, int(position), SEEK_SET);

        // are we going to read past the end of the file?
        // if we are, only read to the end of the file
        // and then loop to the beginning of the file
        if (thisSize > (sfInfo.frames - position))
        {
            thisRead = sfInfo.frames - position;
            position = 0;
        }
        else
        {
            // otherwise, we'll just fill up the rest of the output buffer
            thisRead = thisSize;
            // and increment the file position
            position += thisRead;
        }

        /* since our output format and channel interleaving is the same as
    sf_readf_int's requirements */
        /* we'll just read straight into the output buffer */
        sf_readf_float(sndFile, cursor, long(thisRead));
        /* increment the output cursor*/
        // cursor += thisRead;
        /* decrement the number of samples left to process */
        thisSize -= thisRead;
    }
}

void checkPaError(int err){
    if (err != paNoError){
        logError("PortAudio error:");
        logError(Pa_GetErrorText(err));
    }
}

AudioPlayback::AudioPlayback(AudioFile *af)
    :audioFile(af) {
    auto err = Pa_Initialize();
    checkPaError(err);
    err = Pa_OpenDefaultStream(
            &stream,
            0,
            audioFile->sfInfo.channels,
            paFloat32,
            audioFile->sfInfo.samplerate,
            128,
            paCallback,
            audioFile
    );
    checkPaError(err);
}

AudioPlayback::~AudioPlayback() {
    checkPaError(Pa_StopStream(stream));
    checkPaError(Pa_Terminate());
}

void AudioPlayback::play() {
    checkPaError(Pa_StartStream(stream));
}

void AudioPlayback::pause() {
    checkPaError(Pa_StopStream(stream));
}
