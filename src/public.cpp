#include "common.hpp"
#include <rpc>
#include <cstdio>

char getChar(std::PID client) {
	IGNORE(client);

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
