#include "ip/Display.h"
#include "ip/test.h"
#include "ip/Audio.h"


#define N 16
void TestFftReal(const char* title, const kiss_fft_scalar in[N], kiss_fft_cpx out[N / 2 + 1])
{
    kiss_fftr_cfg cfg;

    printf("%s\n", title);

    if ((cfg = kiss_fftr_alloc(N, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
    {
        size_t i;

        kiss_fftr(cfg, in, out);
        free(cfg);

        for (i = 0; i < N; i++)
        {
            printf(" in[%2zu] = %+f    ",
                   i, in[i]);
            if (i < N / 2 + 1){
                float k = 2;
                float v = out[i].r * (cos(i*k) + out[i].i*sin(i*k));
                printf("out[%2zu] = %+f ", i, v);
            }
            printf("\n");
        }
    }
    else
    {
        printf("not enough memory?\n");
        exit(-1);
    }
}

// int main(void)
// {
//     kiss_fft_scalar in[N];
//     kiss_fft_cpx out[N / 2 + 1];
//     size_t i;
//
//     for (i = 0; i < N; i++)
//         in[i] = 0;
//     TestFftReal("Zeroes (real)", in, out);
//
//     for (i = 0; i < N; i++)
//         in[i] = 1;
//     TestFftReal("Ones (real)", in, out);
//
//     for (i = 0; i < N; i++)
//         in[i] = sin(2 * M_PI * 4 * i / N);
//     TestFftReal("SineWave (real)", in, out);
//
//     return 0;
// }

int main() {

    auto start = std::chrono::steady_clock::now();
    glfwInit();

    auto display = Display();
    auto startupTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-start).count();
    std::cout << "Startup complete in " << startupTime << "milliseconds" << std::endl;

    while(!display.shouldClose()) {
        display.update();
    }

    return 0;
}



