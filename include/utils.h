//
// Created by aviruk on 1/9/25.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils final {
public:
    Utils() = delete;

    static std::string pathjoin(std::initializer_list<std::string> paths);
};

#endif //UTILS_H
