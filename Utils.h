#pragma once
#include <string>

std::string trim(const std::string& value);
std::string truncateZero(const std::string& value);
std::string fillSpaceLeft(const std::string& value, int requiredLength);