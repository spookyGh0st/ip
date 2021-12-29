

#ifndef IP_SCENE_H
#define IP_SCENE_H

#include "ShaderProgram.h"
#include "Syntax.h"
#include "Tape.h"
#include "Audio.h"

namespace ip{
    class Quad {
    private:
        unsigned  int quad_vao{};
        unsigned  int quad_vbo{};
    public:
        Quad();
        ~Quad();
        void render() const;
    };

    class Scene {
    private:
        ShaderProgram shader;
        Quad quad;
        Tape tape;
        AudioFile *audioVisualizationFile;
        AudioFile *audioPlaybackFile;
        std::vector<float> audioBuffer {};
        std::string keyPulseL = "pulseL";
        std::string keyPulseR = "pulseR";
    public:
        Scene(AudioFile *audioVisualization, AudioFile *audioPlaybackCursor);
        ~Scene();
        void update(std::chrono::duration<long, std::ratio<1, 1000000000>> dt, std::chrono::time_point<std::chrono::system_clock> t);
        void render(std::chrono::duration<long, std::ratio<1, 1000000000>> dt, std::chrono::time_point<std::chrono::system_clock> t);
        void onKey(int key, int scancode, int action, int mode);

        void setResolution(int width, int height);
    };
}

#endif //IP_SCENE_H
