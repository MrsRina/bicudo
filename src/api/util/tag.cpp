#include "tag.h"

std::map<const std::string, bool> tag::map;

uint32_t tag::size() {
	return map.size();
}

bool tag::get(const std::string &str) {
	auto it = map.find(str);

	if (it != map.end()) {
		return it->second;
	}

	return false;
}

void tag::set(const std::string &str, bool val) {
	map[str] = val;
}

void tag::remove(std::string &str) {
	auto it = map.find(str);

	if (it != map.end()) {
		map.erase(it);
	}
}