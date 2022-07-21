#include <common.hpp>
#include <shared_memory>

size_t getUID(std::PID client, std::SMID smid) {
	auto link = std::sm::link(client, smid);
	size_t npages = link.s;
	if(!npages)
		return 0;
	char* buffer = (char*)link.f;
	buffer[PAGE_SIZE - 1] = 0;
	std::string name(buffer);
	std::sm::unlink(smid);

	lock.acquire();
	size_t ret = 0;
	auto it = a.find(name);
	if(it != a.end())
		ret = (*it).s;
	lock.release();

	return ret;
}

bool getName(std::PID client, std::SMID smid, size_t uid) {
	auto link = std::sm::link(client, smid);
	size_t npages = link.s;
	if(!npages)
		return false;
	char* buffer = (char*)link.f;

	lock.acquire();
	auto it = b.find(uid);
	if(it == b.end()) {
		lock.release();
		std::sm::unlink(smid);
		return false;
	}
	std::string& name = (*it).s;
	memcpy(buffer, name.c_str(), name.size());
	buffer[name.size()] = 0;
	lock.release();

	std::sm::unlink(smid);
	return true;
}
