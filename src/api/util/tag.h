#pragma once

#ifndef TAG_H
#define TAG_H

#include <iostream>
#include <string>
#include <map>

/**
 * Handle and redirect_data flags (input, states...).
 **/
struct tag {
protected:
	static std::map<const std::string, bool> map;
public:
	static bool get(const std::string &str);
	static void set(const std::string &str, bool val);
	static void remove(std::string &str);
	static uint32_t size();
};

#endif