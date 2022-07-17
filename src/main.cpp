#include <cstdio>
#include "common.hpp"
#include <driver>
#include <mutex>
#include "layout.hpp"

std::Smokers wait;
std::queue<char> chars; // Horrific!

inline void append(char c) {
	chars.push(c);
	wait.give();
}

extern "C" void _start() {
	if(std::allowIO() != 0) {
		std::printf("[keyboard] Couldn't allow IO\n");
		std::exit(1);
	}

	wait = std::Smokers();
	publish();

	// Discard already pressed keys
	std::in8(KEYBOARD_STATUS_PORT);
	std::in8(KEYBOARD_DATA_PORT);

	while(true) {
		// Poll until there's a key press
		// This is a monumentally bad idea but I'm running short of time
		while(true) {
			uint8_t status = std::in8(KEYBOARD_STATUS_PORT);
			if(status & 0x01)
				break;
			asm volatile("pause");
		}

		uint8_t keycode = std::in8(KEYBOARD_DATA_PORT);
		if(keycode >= 128)
			continue; // Key release

		if(keycode == 0x0E) {
			append('\b');
		} else if(keycode < 0x58) {
			char c = KB_LAYOUT[keycode];
			if(c)
				append(c);
		}
	}
}
