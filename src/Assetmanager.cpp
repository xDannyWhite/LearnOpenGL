#include "Assetmanager.hpp"

std::string Assetmanager::LoadFile(const std::string &path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}