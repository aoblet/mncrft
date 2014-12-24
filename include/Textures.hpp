#pragma once
#include <GL/glew.h>
#include <glimac/Image.hpp>
#include <vector>
#include <string>
#include <map>

class Textures{
        std::vector< std::vector<std::unique_ptr<glimac::Image>> > m_pictures; //vector of vector<Image>
        /*m_pictures->  typeTexture1
                            1.png
                            2.png ....
                            Textures::SIZE_LEVEL_TEXTURES
                        typeTexture2
                            1.png ...
        */

        GLuint m_idTextures; //all textures following each other
        std::map<int,std::string> m_folderPaths; //set in constructor
        void loadFolderPaths();
        static int TEXTURE_CPT;

    public:
        static const int INDEX_TEXTURE_FOUNDATION ;
        static const int INDEX_TEXTURE_DIRT       ;
        static const int INDEX_TEXTURE_ROCK       ;
        static const int INDEX_TEXTURE_SAND       ;
        static const int INDEX_TEXTURE_LIGHT      ;
        static const int SIZE_LEVEL_TEXURES       ; //textures for damage on cube, same for each cube! IMPORTANT

        static const std::vector<std::string> EXTENSIONS_FILES_TEXTURES;

        GLuint idTexture() const;

        void loadSetImages();
        void tranformImagesToTextures(int sizeLevel = Textures::SIZE_LEVEL_TEXURES); //customizable for test
        void setUpTexturesTEST(std::string const& texturePath0, std::string const& texturePath1);//1 texture ONLY

        ~Textures();
        Textures(bool setUp=true);
};

