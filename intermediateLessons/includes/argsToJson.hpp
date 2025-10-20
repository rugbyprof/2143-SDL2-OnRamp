#pragma once
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "json.hpp"

using nlohmann::json;

static json infer_type(const std::string& value) {
    // Handle booleans
    if (value == "true" || value == "True" || value == "TRUE") return true;
    if (value == "false" || value == "False" || value == "FALSE") return false;

    // Handle comma-separated values (like RGB)
    if (value.find(',') != std::string::npos) {
        std::vector< int > nums;
        std::stringstream  ss(value);
        std::string        item;
        while (std::getline(ss, item, ',')) {
            try {
                nums.push_back(std::stoi(item));
            } catch (...) {
                throw std::invalid_argument("Invalid numeric value in comma-separated list: " + value);
            }
        }
        return nums;  // becomes JSON array [r,g,b]
    }

    // Try integer
    try {
        size_t idx;
        int    i = std::stoi(value, &idx);
        if (idx == value.size()) return i;
    } catch (...) {
    }

    // Try float
    try {
        size_t idx;
        double d = std::stod(value, &idx);
        if (idx == value.size()) return d;
    } catch (...) {
    }

    // Default → string
    return value;
}

json ArgsToJson(int argc, char* argv[]) {
    json params = json::object();
    for (int i = 1; i < argc; ++i) {
        std::string_view arg{argv[i]};
        auto             separator = arg.find('=');
        if (separator == std::string_view::npos || separator == 0 || separator == arg.size() - 1)
            throw std::invalid_argument("Arguments must be formatted as key=value");
        std::string key{arg.substr(0, separator)};
        std::string value{arg.substr(separator + 1)};
        params[key] = infer_type(value);
    }
    return params;
}

SDL_Color make_SDL_Color_from_json(const json& params, const std::string& key) {
    SDL_Color color = {30, 30, 40, 255};  // default dark gray

    if (params.contains(key)) {
        auto bg = params[key];
        if (bg.is_array() && bg.size() >= 3) {
            color.r = bg[0];
            color.g = bg[1];
            color.b = bg[2];
            if (bg.size() == 4) color.a = bg[3];
        } else {
            std::cerr << "Invalid background format. Use r,g,b or r,g,b,a\n";
        }
    }
    return color;
}