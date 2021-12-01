

#ifndef IP_SCENE_H
#define IP_SCENE_H

#include "ShaderProgram.h"
#include "Syntax.h"

namespace ip{
    class Scene {
    private:
        unsigned  int quad_vao{};
        unsigned  int quad_vbo{};
        Expr::Tape tape;
        ShaderProgram shader;
    public:
        Scene();
        ~Scene();
        void update(std::chrono::duration<long, std::ratio<1, 1000000000>> dt, std::chrono::time_point<std::chrono::system_clock> t);
        void render(std::chrono::duration<long, std::ratio<1, 1000000000>> dt, std::chrono::time_point<std::chrono::system_clock> t);
        void onKey(int key, int scancode, int action, int mode);

    };
}

#endif //IP_SCENE_H
