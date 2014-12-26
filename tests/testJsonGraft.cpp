#include <glimac/SDLWindowManager.hpp>
#include <iostream>
#include <json/value.h>
#include <json/writer.h>
#include <json/reader.h>

using namespace glimac;

int main(){
    SDLWindowManager windowManager(800, 600, "triforce");

    // ---- create from scratch ----

    Json::Value fromScratch;
    Json::Value array;
    array.append("hello");
    array.append("world");
    fromScratch["hello"] = "world";
    fromScratch["number"] = 2;
    fromScratch["array"] = array;
    fromScratch["object"]["hello"] = "world";
    fromScratch["object"]["hello"] = "lol";


    // write in a nice readible way
    Json::StyledWriter styledWriter;
    std::cout << styledWriter.write(fromScratch);

    // ---- parse from string ----

    // write in a compact way
    Json::FastWriter fastWriter;
    std::string jsonMessage = fastWriter.write(fromScratch);

    Json::Value parsedFromString;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(jsonMessage, parsedFromString);
    if (parsingSuccessful)
    {
        std::cout << styledWriter.write(parsedFromString) << std::endl;
    }

    return 0;
}
