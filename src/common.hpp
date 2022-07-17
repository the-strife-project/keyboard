#ifndef COMMON_HPP
#define COMMON_HPP

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#include <mutex>
#include <queue>

extern std::Smokers wait;
extern std::queue<char> chars;

void publish();

#endif
