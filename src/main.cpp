#include <rpc>
#include <common.hpp>
#include <rpc>

std::mutex lock;
std::unordered_map<std::string, size_t> a;
std::unordered_map<size_t, std::string> b;

extern "C" void _start() {
	a["system"] = 1;
	b[1] = "system";

	std::exportProcedure((void*)getUID, 1);
	std::exportProcedure((void*)getName, 2);
	std::exportProcedure((void*)getCount, 0);
	std::exportProcedure((void*)newUser, 1);
	std::enableRPC();
	if(!std::publish("users"))
		std::exit(1);
	std::halt();
}
