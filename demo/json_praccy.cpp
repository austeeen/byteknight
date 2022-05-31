#include <iostream>
#include <fstream>

#include "json/json.h"

int main()
{
    const char * fn = "res/instance/basic_game.ist.json";
    std::ifstream is(fn);
    if (!is.is_open()) {
        std::cout << "could not open: " << (std::string) fn << std::endl;
        return 1;
    }
    std::string errors;
    Json::Value root;
    Json::CharReaderBuilder builder;
    Json::parseFromStream(builder, is, &root, &errors);
    Json::Value object_list = root["layers"][2]["objects"];
    Json::Value::ArrayIndex size = object_list.size();
    std::cout << "size: " << size << std::endl;
    for (Json::Value::ArrayIndex i = 0; i < size; i++)
        std::cout << object_list[i]["name"] << std::endl;
    return 0;
}
