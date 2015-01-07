#include "Textures.hpp"
#include <stdexcept>
#include <iostream>
//way to define in cpp static: c++ legacy
int Textures::TEXTURE_CPT = 0;
int Textures::RAND_UNIVERS = 0;

const int Textures::INDEX_TEXTURE_FOUNDATION = Textures::TEXTURE_CPT++;
const int Textures::INDEX_TEXTURE_DIRT       = Textures::TEXTURE_CPT++;
const int Textures::INDEX_TEXTURE_ROCK       = Textures::TEXTURE_CPT++;
const int Textures::INDEX_TEXTURE_SAND       = Textures::TEXTURE_CPT++;
const int Textures::INDEX_TEXTURE_LIGHT      = Textures::TEXTURE_CPT++;

const int Textures::SIZE_LEVEL_TEXURES       = 6; //textures for damage on cube, same for each cube
const std::vector<std::string> Textures::EXTENSIONS_FILES_TEXTURES {"png","jpg","jpeg"};
const std::vector<std::string> Textures::UNIVERS {"default","candy"};

Textures::~Textures(){
    glDeleteTextures(1,&m_idTextures);
}

Textures::Textures(bool setUp){
    glGenTextures(1,&m_idTextures);

    if(!setUp) //for test ?
        return;

    this->loadFolderPaths();
    this->loadSetImages();
    this->tranformImagesToTextures(Textures::SIZE_LEVEL_TEXURES);
}

void Textures::loadFolderPaths(){
    int indexUnivers = !(Textures::RAND_UNIVERS%Textures::UNIVERS.size()) ? 0 : 1;
    std::string defaultUnivers = Textures::UNIVERS[indexUnivers];
    m_folderPaths.insert(std::pair<int,std::string>(Textures::INDEX_TEXTURE_FOUNDATION,"assets/textures/cubes/"+defaultUnivers+"/foundation/"));
    m_folderPaths.insert(std::pair<int,std::string>(Textures::INDEX_TEXTURE_DIRT,"assets/textures/cubes/"+defaultUnivers+"/dirt/"));
    m_folderPaths.insert(std::pair<int,std::string>(Textures::INDEX_TEXTURE_ROCK,"assets/textures/cubes/"+defaultUnivers+"/rock/"));
    m_folderPaths.insert(std::pair<int,std::string>(Textures::INDEX_TEXTURE_SAND,"assets/textures/cubes/"+defaultUnivers+"/sand/"));
    m_folderPaths.insert(std::pair<int,std::string>(Textures::INDEX_TEXTURE_LIGHT,"assets/textures/cubes/"+defaultUnivers+"/light/"));
}

void Textures::loadSetImages(){
    if(!m_folderPaths.size())
        throw std::logic_error("Textures:loadSetImages() folder paths unset");

    m_pictures.resize(m_folderPaths.size());

    //more readable in loop
    std::vector<std::string>::const_iterator  it_extension_begin = Textures::EXTENSIONS_FILES_TEXTURES.begin(),
                                              it_extension_end   = Textures::EXTENSIONS_FILES_TEXTURES.end();

    //load all images for cubes
    //m_folderPaths already sorted thx to std::pair<int,std::string> => index order respected
    for(std::map<int,std::string>::iterator it=m_folderPaths.begin() ; it != m_folderPaths.end() ; ++it){
        m_pictures[it->first].clear();

        for(int j=1; j<=Textures::SIZE_LEVEL_TEXURES; ++j){
            std::unique_ptr<glimac::Image> imageTmp = nullptr;
            bool found_file = false;

            for(std::vector<std::string>::const_iterator it_extension=it_extension_begin; it_extension != it_extension_end; ++it_extension){
                imageTmp = glimac::loadImage(it->second + std::to_string(j) + "."+ *it_extension);
                found_file = imageTmp ? true : false; //ternary form constrained cause of pointer

                if(found_file)
                    break;
            }
            if(!found_file)
                throw std::invalid_argument("Textures: loadSetImage: no file found for: " + it->second + " image: "+ std::to_string(j));

            m_pictures[it->first].push_back(std::move(imageTmp));
        }
    }
}

//sizeLevel defaut to Textures::SIZE_LEVEL_TEXURES
void Textures::tranformImagesToTextures(int sizeLevel){
    if(!m_pictures.size() || !m_pictures[0].size()){
        //no images loaded
        throw std::logic_error("Textures:tranformImagesToTextures() no images loaded");
    }

    glBindTexture(GL_TEXTURE_2D_ARRAY,m_idTextures);
    //container
    glTexImage3D(
        GL_TEXTURE_2D_ARRAY,
        0,
        GL_RGBA,
        m_pictures[0][0]->getWidth(),
        m_pictures[0][0]->getHeight(),
        sizeLevel * m_pictures.size(), //number of texture
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        NULL
    );

    //fill container array (with z)
    //m_pictures order index respected thx to m_folderPaths
    int cptFill_texture =0;
    for(std::vector<std::vector<std::unique_ptr<glimac::Image>>>::iterator it=m_pictures.begin(); it != m_pictures.end() ; ++it ){
        for(std::vector<std::unique_ptr<glimac::Image>>::iterator it_pictures_levels=it->begin(); it_pictures_levels != it->end() ; ++it_pictures_levels ){
            glTexSubImage3D(
                GL_TEXTURE_2D_ARRAY,
                0,
                0,
                0,
                cptFill_texture++, // Z index
                (*it_pictures_levels)->getWidth(),
                (*it_pictures_levels)->getHeight(),
                1,
                GL_RGBA,
                GL_FLOAT,
                (*it_pictures_levels)->getPixels()
            );
        }
    }

    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void Textures::setUpTexturesTEST(std::string const& texturePath0, std::string const& texturePath1){
    std::unique_ptr<glimac::Image> imageTmp0 = glimac::loadImage(texturePath0);
    if(!imageTmp0)
        throw std::invalid_argument("Textures:setUpTexturesTEST(): bad path for texture");

    std::unique_ptr<glimac::Image> imageTmp1 = glimac::loadImage(texturePath1);
    if(!imageTmp1)
        throw std::invalid_argument("Textures:setUpTexturesTEST(): bad path for texture");

    m_pictures.resize(2);
    m_pictures[0].push_back(std::move(imageTmp0));
    m_pictures[1].push_back(std::move(imageTmp1));
    this->tranformImagesToTextures(1);
}

GLuint Textures::idTexture() const{
    return m_idTextures;
}

void Textures::changeUniverse() noexcept{
    Textures::RAND_UNIVERS ++;
    Textures newUniverse;
    std::swap(newUniverse.m_idTextures, m_idTextures);
}









