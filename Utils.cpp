#include "Utils.h"

std::string trim(const std::string& value) {
	std::string result = value;
	if (value.starts_with(' ')) {
		result.erase(0, result.find_first_not_of(' '));
	}
	if (value.ends_with(' ')) {
		auto offset = result.find_first_of(' ');
		result.erase(offset, result.size() - offset);
	}
	return result;
}

std::string truncateZero(const std::string& value) {
	std::string result = value;
	while ((result.back() == '0' && result.find('.') != std::string::npos) || result.back() == '.') {
		result.pop_back();
	}
	return result;
}