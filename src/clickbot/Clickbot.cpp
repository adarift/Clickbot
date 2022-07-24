#include "Clickbot.hpp"
#include <vector>
#include <filesystem>
#include <random>
#include "../hk/PlayLayer.hpp"

namespace fs = std::filesystem;

namespace Clickbot
{
    std::string pickRandomClick()
    {
        std::vector<std::string> clicks;
        std::vector<std::string> out;
        std::string path = "clicks\\clicks";
        for (const auto & entry : fs::directory_iterator(path))
        {
            clicks.push_back(entry.path().string());
        }
        std::sample(
            clicks.begin(),
            clicks.end(),
            std::back_inserter(out),
            1,
            std::mt19937{std::random_device{}()}
        );
        return out[0];
    }
    std::string pickRandomRelease()
    {
        std::vector<std::string> releases;
        std::vector<std::string> out;
        std::string path = "clicks\\releases";
        for (const auto & entry : fs::directory_iterator(path))
            releases.push_back(entry.path().string());
        std::sample(
            releases.begin(),
            releases.end(),
            std::back_inserter(out),
            1,
            std::mt19937{std::random_device{}()}
        );
        return out[0];
    }
}