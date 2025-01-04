//
// Created by aviruk on 1/4/25.
//

#include <string>
#include "globals.h"

std::string pathjoin(const std::initializer_list<std::string> paths) {
    std::string path;
    for (const auto& p : paths) {
        path.append(p);
        path.push_back('/');
    }
    path.pop_back();
    return path;
}