#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/CubeGL.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <vector>
#include "Textures.hpp"
#include "CubeDirt.hpp"
#include "CubeSand.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include <glimac/Skybox.hpp>
#include "CubeFoundation.hpp"
#include "CubeRock.hpp"
#include "PerlinNoise.hpp"

using namespace glimac;

// desired framerate in milliseconds
static const Uint32 FRAMERATE = 1000 / Game::FRAME_PER_SECOND;

int main(int argc, char** argv) {
    int WIDTH = 1350;
    int HEIGHT = 750;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WIDTH, HEIGHT, "testGamePlayer");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        throw std::logic_error("Error glew setup");
    }

    Game::createSingleton(argv[0],"../../game_save/perfo.json","../../game_save/perfo.json");
    Game* game = Game::singletonGame();
    Skybox skybox(argv[0], "cubeMap",*game);

    /********************************************/


//////    for(int i=0; i<200; ++i){
//////        for(int j=0; j<300; ++j){
//////            game->m_cube_list.push_back(CubeFoundation(glm::vec3(i,1,j),Textures::INDEX_TEXTURE_FOUNDATION));
//////        }
//////    }

////    for(int i=50+80; i<60+80; ++i){
////        for(int j=50+80; j<60+80; ++j){
////            for(int k=20; k<60; ++k){
////                if((k + j + i)%10)
////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(i,k,j),Textures::INDEX_TEXTURE_DIRT));
////                else
////                    game->m_cube_list.push_back(CubeSand(glm::vec3(i,k,j),Textures::INDEX_TEXTURE_SAND));
////            }
////        }
////    }


////    for(int i=50+20+80; i<60+20+80; ++i){
////        for(int j=50+80; j<60+80; ++j){
////            for(int k=20; k<25; ++k){
////                if((k + j + i)%10)
////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(i,k,j),Textures::INDEX_TEXTURE_DIRT));
////                else
////                    game->m_cube_list.push_back(CubeSand(glm::vec3(i,k,j),Textures::INDEX_TEXTURE_SAND));
////            }
////        }
////    }

////    for(int i=50+20+80; i<60+20+80; ++i){
////        for(int j=50+20+80; j<60+20+80; ++j){
////            for(int k=60; k<83; ++k){
////                if((k + j + i)%10)
////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(i,k,j),Textures::INDEX_TEXTURE_DIRT));
////                else
////                    game->m_cube_list.push_back(CubeSand(glm::vec3(i,k,j),Textures::INDEX_TEXTURE_SAND));
////            }
////        }
////    }

////    for(int i=50+80; i<55+80; ++i){
////        for(int j=50+20+80; j<55+20+80; ++j){
////            for(int k=20; k<100; ++k){
////                if((k + j + i)%10)
////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(i,k,j),Textures::INDEX_TEXTURE_DIRT));
////                else
////                    game->m_cube_list.push_back(CubeSand(glm::vec3(i,k,j),Textures::INDEX_TEXTURE_SAND));
////            }
////        }
////    }
////    int y=100;
////    int x = 50+80+2;
////    int z=50+20+80-2;
////    while(y>15){
////        if(rand()%40>10)
////            game->m_cube_list.push_back(CubeDirt(glm::vec3(x,y,z),Textures::INDEX_TEXTURE_DIRT));
////        else
////            game->m_cube_list.push_back(CubeRock(glm::vec3(x,y,z),Textures::INDEX_TEXTURE_ROCK));
////        z--;
////        y--;
////    }

////     y=100;
////     x = 50+80+2-2;
////     z=50+20+80+4;
////    while(y>15){
////        if(rand()%40>10)
////            game->m_cube_list.push_back(CubeDirt(glm::vec3(x,y,z),Textures::INDEX_TEXTURE_DIRT));
////        else
////            game->m_cube_list.push_back(CubeFoundation(glm::vec3(x,y,z),Textures::INDEX_TEXTURE_FOUNDATION));

////        x--;
////        y--;
////    }

////    y=100;
////    x = 50+80+2-3;
////    z=50+20+80-2;
//////   while(y>15){
//////       if(rand()%40>10)
//////           game->m_cube_list.push_back(CubeDirt(glm::vec3(x,y,z),Textures::INDEX_TEXTURE_DIRT));
//////       else
//////           game->m_cube_list.push_back(CubeFoundation(glm::vec3(x,y,z),Textures::INDEX_TEXTURE_FOUNDATION));

//////       x--;
//////       z--;
//////       y--;
//////   }

////    int xStart = 150,yStart = 1, zStart= 150;
////    int rMax = 100; int rMin = 50;

////    x =20+100;
////    bool depass = false;
////    z = +150;
////    for(y=2; y<50; ++y){
////    x=20+100;
////    while(x>=20+100){
////        if(x<40+100 && !depass){
////            ++x;
////        }
////        else{
////            depass = true;
////            --x;
////        }

////        for(int i=0; i < x; ++i){
////                if((i+x+z)%10){
////                    game->m_cube_list.push_back(CubeSand(glm::vec3(z+50,y,i+150),Textures::INDEX_TEXTURE_SAND));
////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(z+50,y,-i+150),Textures::INDEX_TEXTURE_DIRT));
////                }

////                else if((i+x+z)%5){
////                    game->m_cube_list.push_back(CubeRock(glm::vec3(z+50,y,i+150),Textures::INDEX_TEXTURE_ROCK));
////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(z+50,y,-i+150),Textures::INDEX_TEXTURE_DIRT));
////                }
////                else if(!(rand()%40)){
////                    game->m_cube_list.push_back(CubeSand(glm::vec3(z+50,y,i+150),Textures::INDEX_TEXTURE_SAND));
////                    game->m_cube_list.push_back(CubeRock(glm::vec3(z+50,y,-i+150),Textures::INDEX_TEXTURE_ROCK));
////                }
////                else{
////                    game->m_cube_list.push_back(CubeFoundation(glm::vec3(z+50,y,i+150),Textures::INDEX_TEXTURE_FOUNDATION));
////                    game->m_cube_list.push_back(CubeRock(glm::vec3(z+50,y,-i+150),Textures::INDEX_TEXTURE_ROCK));
////                }
////        }

////        z++;
////    }
////    }


////    int xMilieu = 100;
////    int xMax = 100;
////    int cpt=0;
////    int cpt2=0;

////    for(int y = 160; y<170;y+=1){
////        cpt=0;
////        for(int z=67+233; z>0+233; z--){
////            for(int x=xMilieu-xMax+cpt+cpt2; x< (xMilieu - (xMilieu-xMax+cpt+cpt2))*2; ++x){
////                if(!((x+cpt2+cpt)%10) ||!((x+cpt2+cpt)%(cpt2+cpt+xMax)) )
////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(x,y,z),Textures::INDEX_TEXTURE_DIRT));
////                else if(xMax%10 || !(rand()%85))
////                    game->m_cube_list.push_back(CubeRock(glm::vec3(x,y,z),Textures::INDEX_TEXTURE_ROCK));
////                else
////                    game->m_cube_list.push_back(CubeSand(glm::vec3(x,y,z),Textures::INDEX_TEXTURE_SAND));
////            }
////            cpt++;

////        }
////        cpt2++;
////        xMax -= 10;
////    }


//////        depass = false;
//////        z = 0;
//////        cpt = 0;
//////        for(int y=1; y<50; ++y){
//////        z=0;
//////        x=20;
//////        depass = false;
//////        while(x>=20 - cpt){
//////            if(x<40-cpt && !depass){
//////                ++x;
//////            }
//////            else{
//////                depass = true;
//////                --x;
//////            }

//////            for(int i=0; i < x; ++i){
//////                if(!((x+cpt2+cpt)%10) ||!((x+cpt2+cpt)%(cpt2+cpt+xMax)) )
//////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(i+100+150,y,z),Textures::INDEX_TEXTURE_DIRT));
//////                else if(xMax%10 || !(rand()%85))
//////                    game->m_cube_list.push_back(CubeRock(glm::vec3(i+100+150,y,z),Textures::INDEX_TEXTURE_ROCK));
//////                else
//////                    game->m_cube_list.push_back(CubeSand(glm::vec3(i+100+150,y,z),Textures::INDEX_TEXTURE_SAND));

//////                game->m_cube_list.push_back(CubeFoundation(glm::vec3(-i+100+150,y,z),Textures::INDEX_TEXTURE_FOUNDATION));

//////            }

//////            z++;
//////        }
//////        cpt++;
//////        }

////    for(int i=0; i<200;++i){
////        game->m_cube_list.push_back(CubeSand(glm::vec3(rand()%300,std::max(80,rand()%200),rand()%450),Textures::INDEX_TEXTURE_SAND));
////        game->m_cube_list.push_back(CubeRock(glm::vec3(rand()%300,std::max(80,rand()%200),rand()%450),Textures::INDEX_TEXTURE_ROCK));
////        game->m_cube_list.push_back(CubeDirt(glm::vec3(rand()%400,std::max(80,rand()%200),rand()%450),Textures::INDEX_TEXTURE_DIRT));
////    }

// PerlinNoise p(1,0.0005,6.5,10,50);
////    for (int i = 0; i < 200; ++i) {
////        for (int j = 0; j < 280; ++j) {
////            for(int y=0;y<=abs(p.GetHeight(i,j));++y){
////                if(y<3)
////                    game->m_cube_list.push_back(CubeFoundation(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_FOUNDATION));
////                else if(y < 6)
////                    game->m_cube_list.push_back(CubeRock(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_ROCK));
////                else if(y < 10)
////                    game->m_cube_list.push_back(CubeSand(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_SAND));
////                else
////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_DIRT));
////            }

////        }
////    }

//////    p.SetAmplitude(7);
//////    for (int i = 0; i < 120; ++i) {
//////        for (int j = 200; j < 234; ++j) {
//////            for(int y=0;y<abs(p.GetHeight(i,j));++y){
//////                if(y<3)
//////                    game->m_cube_list.push_back(CubeFoundation(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_FOUNDATION));
//////                else if(y < 6)
//////                    game->m_cube_list.push_back(CubeRock(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_ROCK));
//////                else if(y < 10)
//////                    game->m_cube_list.push_back(CubeSand(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_SAND));
//////                else
//////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_DIRT));
//////            }

//////        }
//////    }

//////    p.SetAmplitude(7);
//////    for (int i = 120; i < 200; ++i) {
//////        for (int j = 160; j < 234; ++j) {
//////            for(int y=0;y<abs(p.GetHeight(i,j));++y){
//////                if(y<3)
//////                    game->m_cube_list.push_back(CubeFoundation(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_FOUNDATION));
//////                else if(y < 6)
//////                    game->m_cube_list.push_back(CubeRock(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_ROCK));
//////                else if(y < 10)
//////                    game->m_cube_list.push_back(CubeSand(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_SAND));
//////                else
//////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_DIRT));
//////            }

//////        }
//////    }

//    p.SetAmplitude(12);
//    for (int i = 1; i <550; ++i) {
//        for (int j = 1; j < 550; ++j) {
////            for(int y=0;y<=abs(p.GetHeight(i,j));++y){
//                int y = abs(p.GetHeight(i,j));
//                int yP = std::min(abs(p.GetHeight(i,j-1)),std::min(abs(p.GetHeight(i+1,j)),std::min(abs(p.GetHeight(i,j+1)),std::min(abs(p.GetHeight(i,j)),abs(p.GetHeight(i-1,j))))));
//                while(y >= yP){
//                    if(y < 5)
//                        game->m_cube_list.push_back(CubeFoundation(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_FOUNDATION));
//                    else if(y<9)
//                        game->m_cube_list.push_back(CubeRock(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_ROCK));
//                    else if(y<15)
//                        game->m_cube_list.push_back(CubeSand(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_SAND));
//                    else
//                        game->m_cube_list.push_back(CubeDirt(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_DIRT));
//                    --y;
//                }

//            }

//        }
////    }

//////    p.SetAmplitude(8);
//////    for (int i = 161; i < 200; ++i) {
//////        for (int j = 130; j < 300; ++j) {
//////            for(int y=0;y<abs(p.GetHeight(i,j));++y){
//////                if(y<3)
//////                    game->m_cube_list.push_back(CubeFoundation(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_FOUNDATION));
//////                else if(y < 6)
//////                    game->m_cube_list.push_back(CubeRock(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_ROCK));
//////                else if(y < 10)
//////                    game->m_cube_list.push_back(CubeSand(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_SAND));
//////                else
//////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_DIRT));
//////            }
//////        }
//////    }



//////    for (int i = 0; i < 100; ++i) {
//////        for (int j = 100; j < 300; ++j) {
//////            for(int y=0;y<abs(p.GetHeight(i,j));++y){
//////                if(y<3)
//////                    game->m_cube_list.push_back(CubeFoundation(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_FOUNDATION));
//////                else if(y < 6)
//////                    game->m_cube_list.push_back(CubeRock(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_ROCK));
//////                else if(y < 10)
//////                    game->m_cube_list.push_back(CubeSand(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_SAND));
//////                else
//////                    game->m_cube_list.push_back(CubeDirt(glm::vec3(i,y,j),Textures::INDEX_TEXTURE_DIRT));
//////            }

//////        }
//////    }
//    game->utils().updateVboCubeData(0, game->m_cube_list.size());
    /********************************************/

    std::cout << game->m_cube_list.size() << std::endl;
    Player& player1 = game->player();

    glm::mat4 matrixView(player1.camera().getViewMatrix());
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),(float)(WIDTH)/HEIGHT ,0.1f, 1000.f);

    int sizeCubeGL = game->m_cubeGL_model.sizeVertices();
    Uint32 startTime;
    Uint32 elapsedTime;
    glm::ivec2 mouseCurrenPosition;

    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(game->m_vao_cubeData);
    glBindBuffer(GL_UNIFORM_BUFFER, game->m_ProgramShader_main.m_ubo_matricesGlobales);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(ProjMatrix));

    bool done = false;

    while(!done) {
        startTime = SDL_GetTicks();

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                done = true; // Leave the loop after this iteration
            }

            if(e.type == SDL_MOUSEBUTTONDOWN && (e.button.button == SDL_BUTTON_WHEELDOWN || e.button.button == SDL_BUTTON_WHEELUP))
                player1.gameInteraction().handleChoiceCubeType(e);
            if(e.type == SDL_RESIZABLE){
                WIDTH = e.resize.w;
                HEIGHT = e.resize.h;
                ProjMatrix = glm::perspective(glm::radians(70.f),(float)(WIDTH)/HEIGHT ,0.1f, 1000.f);
                glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(ProjMatrix));

            }

            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_o)
                windowManager.toogleCursorMode();

            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b){
                ProjMatrix = glm::perspective(glm::radians(120.f),(float)(WIDTH)/HEIGHT ,0.1f, 1000.f);
                glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(ProjMatrix));
            }

            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n){
                ProjMatrix = glm::perspective(glm::radians(70.f),(float)(WIDTH)/HEIGHT ,0.1f, 1000.f);
                glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(ProjMatrix));
            }
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_t){
                game->textures().changeUniverse();
                skybox.changeUniverse();
            }
        }

        player1.handleMove(windowManager);
        player1.gameInteraction().handleInteraction(windowManager);

        mouseCurrenPosition = windowManager.getMouseMotionRelative();
        player1.camera().rotateLeft(-(mouseCurrenPosition.x)/3.);
        player1.camera().rotateUp(-( mouseCurrenPosition.y)/3.);


        matrixView = player1.camera().getViewMatrix();
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(ProjMatrix*matrixView)); //mvp
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(matrixView));//view
        glUniform3fv(game->m_ProgramShader_main.m_uLights,CubeLight::MAX_LIGHT,&(game->m_uLightsArray[0][0]));


        glClearColor(0.45,0.6,0.9,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        skybox.renderSkybox();
        game->renderGame();

        // Update the display
        windowManager.swapBuffers();

        // calculating elapsed time && wait if necessary
        elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE) {
        std::cout << "FPS" << std::endl;
          SDL_Delay(FRAMERATE - elapsedTime);
        }
    }
    return EXIT_SUCCESS;
}
