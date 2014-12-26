#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <json/value.h>
#include <json/writer.h>
#include <json/reader.h>
#include <iostream>
#include "Level.hpp"

using namespace glimac;

int main(){
    SDLWindowManager windowManager(800, 600, "triforce");
    Level levelTest;
    levelTest.test_cubesToJson(true);
    levelTest.test_jsonToCubes("../../tests/outputJson/test.json");
    return 0;
}
