#include "Logger.h"

Logger::Logger() {
	openLogFile("logs.txt");
}

Logger::~Logger() {
	closeLogFile();
}

void Logger::logMsg(std::string_view message, const char* file, int line, const char* function)
{
	std::string timestamp = getTimestamp();
	std::cout << "[" << timestamp << "] " << message << std::endl;
	if (fileStream.is_open()) {
		fileStream << "[" << timestamp << "] | "
			<< "File: "
			<< file << "("
			<< line << ") `"
			<< function << "`: "
			<< message
			<< std::endl;
		fileStream.flush();
	}
}

void Logger::openLogFile(const std::string& filename) {
	if (fileStream.is_open()) {
		fileStream.close();
	}
	fileStream.open(filename, std::ios::out | std::ios::app);
}

void Logger::closeLogFile() {
	if (fileStream.is_open()) {
		fileStream.close();
	}
}

std::string Logger::getTimestamp() {
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
	std::string timestamp = std::ctime(&currentTime);

	timestamp.pop_back();
	return timestamp;
}