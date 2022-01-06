

#ifndef IP_SCENE_H
#define IP_SCENE_H

#include "ShaderProgram.h"
#include "Syntax.h"
#include "Tape.h"
#include "Audio.h"
#include "Quad.h"

namespace ip{

    class Scene {
    private:
        ShaderProgram shader;
        Quad quad;
        Tape tape;
        AudioSync *audioS;
        std::string keyPulseL = "pulseL";
        std::string keyPulseR = "pulseR";
    public:
        Scene(AudioSync *audioS);
        ~Scene();
        void update(std::chrono::duration<long, std::ratio<1, 1000000000>> dt, std::chrono::time_point<std::chrono::system_clock> t);
        void render(std::chrono::duration<long, std::ratio<1, 1000000000>> dt, std::chrono::time_point<std::chrono::system_clock> t);
        void onKey(int key, int scancode, int action, int mode);

        void setResolution(int width, int height);
    };
}

#endif //IP_SCENE_H
