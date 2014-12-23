#pragma once
#include <string>
#include <fstream> //fstream performance equals to File style C => use \n instead of std::endl(it flushes)
#include <iostream>

class File{
   public:
        static bool write(std::string const& filePath, std::string const& content);
        static bool read(std::string const& filePath, std::string & content);
        bool lool(){return true;}
};
