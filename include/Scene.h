

#ifndef IP_SCENE_H
#define IP_SCENE_H

#include "ShaderProgram.h"
#include "Syntax.h"
#include "Tape.h"
#include "Audio.h"
#include "Quad.h"
#include "Camera.h"
#include "Texture.h"

namespace ip{
    class Scene {
    private:
        ShaderProgram shader;
        Quad quad;
        Tape tape;
        AudioSync *audioS;
        std::string keyPulseL = "pulseL";
        std::string keyPulseR = "pulseR";
        Camera camera {};
        WoodTexture woodTexture {};
        DuckTexture duckTexture {};
    public:
        explicit Scene(AudioSync *audioS);
        ~Scene();
        void update(float dt, float t);
        void render(float dt, float t);
        void onKey(int key, int scancode, int action, int mode);

        void setResolution(float width, float height);
    };
}

#endif //IP_SCENE_H
