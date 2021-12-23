#include "ip/test.h"


std::unique_ptr<Expr> testParsing() {
    std::string expr { "sqrt(x^2+y^2+z^2)+1" };
    auto p = ip::Parser(expr);
    auto e { p.parse() };
    std::cout << e->draw() << "\n";
    return e;
}

void testTape() {
    //auto exprStr { "min(1++2,5"};
    auto exprStr { "min(y,sqrt(x^2+(y-1)^2+(z-6)^2)-1)" };
    auto expr = ip::Parser(exprStr).parse();
    auto tg = TapeGenerator(std::move(expr));
    auto tape = tg.generate();
    std::cout << "op\tout\tiA\tiB" << std::endl;
    for (auto & i : tape.instructions) {
        std::cout << i.print() << std::endl;
    }
    auto te { TapeEmulator(tape,-0.2,1.0,5.0)};
    std::cout << "\n Output: "+std::to_string(te.emulate()) <<std::endl;
};

typedef struct
{
    float left_phase;
    float right_phase;
} paTestData;
/* This routine will be called by the PortAudio engine when audio is needed.
 * It may called at interrupt level on some machines so don't do anything
 * that could mess up the system like calling malloc() or free().
*/
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    /* Cast data passed through stream to our structure. */
    auto *data = (paTestData*)userData;
    auto *out = (float*)outputBuffer;
    unsigned int i;
    (void) inputBuffer; /* Prevent unused variable warning. */

    for( i=0; i<framesPerBuffer; i++ )
    {
        *out++ = data->left_phase;  /* left */
        *out++ = data->right_phase;  /* right */
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
        data->left_phase += 0.01f;
        /* When signal reaches top, drop back down. */
        if( data->left_phase >= 1.0f ) data->left_phase -= 2.0f;
        /* higher pitch so we can distinguish left and right. */
        data->right_phase += 0.03f;
        if( data->right_phase >= 1.0f ) data->right_phase -= 2.0f;
    }
    return 0;
}


void testAudio(){
    auto err = Pa_Initialize();
    if (err != paNoError){
        std::cout << "PortAudio error:\n" << Pa_GetErrorText(err);
    }
    PaStream *stream;
    paTestData data;
    data.left_phase = data.right_phase = 0.0;
    err = Pa_OpenDefaultStream(
            &stream,
            0,
            2,
            paFloat32,
            44100,
            256,
            patestCallback,
            &data
            );

    if (err != paNoError){
        std::cout << "PortAudio error:\n" << Pa_GetErrorText(err);
    }

    err = Pa_StartStream(stream);
    if (err != paNoError){
        std::cout << "PortAudio error:\n" << Pa_GetErrorText(err);
    }
    /* Sleep for several seconds. */
    Pa_Sleep(500*1000);

    err = Pa_StopStream(stream);
    if (err != paNoError){
        std::cout << "PortAudio error:\n" << Pa_GetErrorText(err);
    }

    err = Pa_Terminate();
    if (err != paNoError){
        std::cout << "PortAudio error:\n" << Pa_GetErrorText(err);
    }
}


