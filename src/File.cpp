#include "File.hpp"
#include <sstream>

bool File::read(const std::string& filePath, std::string& content){
    try{
        std::ifstream file(filePath);
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit); //set what we want to throw exceptions

        //get content
        std::stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
    }
    catch(std::ifstream::failure const& e){
        std::cerr << "Exception occurs in File::read: " << e.what() << std::endl;
        return false;
    }
    return true;
}


bool File::write(const std::string &filePath, std::string const& content){
    try{
        std::ofstream file(filePath);
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit); //set what we want to throw exceptions

        std::stringstream buffer(content,std::ios_base::out);
        file << buffer.str();
    }
    catch(std::ifstream::failure const& e){
        std::cerr << "Exception occurs in File::write: " << e.what() << std::endl;
        return false;
    }
    return true;
}
