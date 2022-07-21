#ifndef COMMON_HPP
#define COMMON_HPP

#include <mutex>
#include <unordered_map>

extern std::mutex lock;
extern std::unordered_map<std::string, size_t> a;
extern std::unordered_map<size_t, std::string> b;

size_t getUID(std::PID client, std::SMID smid);
bool getName(std::PID client, std::SMID smid, size_t uid);
size_t newUser(std::PID client, std::SMID smid);

#endif
