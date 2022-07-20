#include "common.hpp"
#include <rpc>
#include <cstdio>
#include <registry>

char getChar(std::PID client) {
	if(!std::registry::has(client, "KEYBOARD"))
		return 0;

	wait.take();

	char ret = chars.front();
	chars.pop();
	return ret;
}

void publish() {
	std::exportProcedure((void*)getChar, 0);
	std::enableRPC();
	if(!std::publish("keyboard"))
		std::exit(2);
}
