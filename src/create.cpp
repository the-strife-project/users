#include <common.hpp>
#include <shared_memory>
#include <registry>

size_t monotonic = 2;

size_t getCount(std::PID client) {
	IGNORE(client);
	lock.acquire();
	auto ret = monotonic;
	lock.release();
	return ret-1;
}

size_t newUser(std::PID client, std::SMID smid) {
	if(!std::registry::has(client, "USERS_NEW"))
		return 0;

	auto link = std::sm::link(client, smid);
	size_t npages = link.s;
	if(!npages)
		return 0;
	char* buffer = (char*)link.f;
	buffer[PAGE_SIZE - 1] = 0;
	std::string name(buffer);
	std::sm::unlink(smid);

	for(char c : name) {
		bool ok = true;
		// This would be a regex if I had one
		ok |= c >= 'A' && c <= 'Z';
		ok |= c >= 'a' && c <= 'z';
		ok |= c >= '0' && c <= '9'; // hmmm don't like it being first but ok
		ok |= c == '_';
		if(!ok)
			return 0;
	}

	lock.acquire();
	if(a.has(name)) {
		lock.release();
		return 0;
	}

	auto ret = monotonic++;
	a[name] = ret;
	b[ret] = name;

	lock.release();
	return ret;
}
