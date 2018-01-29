#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

#define JSON_FILE "settings.json"

int basic_array()
{
    json jmsg;
    json jarray = json::array();

    for (int i = 0; i < 3; i++) {
        json blink;
        blink["left"] = 7;
        blink["right"] = 8;

        json person;
        person["id"] = i;
        person["name"] = "John";
        person["blink_score"] = blink;
        person["smile_score"] = 5.6;

        jarray.push_back(person);
    }

    jmsg["title"] = "face info";
    jmsg["info"] = jarray;

    std::cout << jmsg.dump() << std::endl;

    return 0;
}

int read_from_file()
{
    std::ifstream j_file(JSON_FILE);
    if (j_file.is_open()) {
        json jmsg;
        j_file >> jmsg;
        std::cout << jmsg.dump() << std::endl << std::endl;

        for (const auto& kv : jmsg.get<json::object_t>()) {
            auto& key = kv.first;
            auto& value = kv.second;
            std::cout << "key: " << key << std::endl;
            std::cout << "value: " << value << std::endl;
        }

        std::cout << std::endl;

        std::string mode_value = jmsg.value("mode", "NOT_EXISTED");
        std::cout << "mode_value: " << mode_value << std::endl;
        int port_value = jmsg.value("facepost_port", 8998);
        std::cout << "port_value: " << port_value << std::endl;
        std::string non_existing_value = jmsg.value("non-existing", "NON-NOT_EXISTED");
        std::cout << "non_existing_value: " << non_existing_value << std::endl;
    } else {
        std::cout << "failed to read file" << std::endl;
    }

    return 0;
}

int main()
{
    std::cout << ">> basic_array" << std::endl;
    basic_array();
    std::cout << "<< basic_array" << std::endl << std::endl;

    std::cout << ">> read_from_file" << std::endl;
    read_from_file();
    std::cout << "<< read_from_file" << std::endl << std::endl;

    return 0;
}
