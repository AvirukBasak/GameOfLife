//
// Created by aviruk on 1/9/25.
//

#include "utils.h"

std::string Utils::pathjoin(const std::initializer_list<std::string> paths) {
    std::string path;
    for (const std::string &p: paths) {
        path.append(p);
        path.push_back('/');
    }
    path.pop_back();
    return path;
}
