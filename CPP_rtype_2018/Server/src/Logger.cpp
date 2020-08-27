#include <stdio.h>
#include <time.h>
#include <boost/asio/buffer.hpp>

#include "Logger.hpp"

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::getTime()
{
	time_t raw_time;
	struct tm *time_info;

	time(&raw_time);
	time_info = localtime(&raw_time);
	printf(ANSI_COLOR_MAGENTA);
	printf("%02d/%02d/%04d %02d:%02d:%02d ",
		   time_info->tm_mday, time_info->tm_mon + 1,
		   time_info->tm_year + 1900, time_info->tm_hour,
		   time_info->tm_min, time_info->tm_sec);
	printf(ANSI_COLOR_RESET);
}

void Logger::printError(std::string message)
{
	this->getTime();
	std::cout << ANSI_COLOR_RED << "Error: " << message << ANSI_COLOR_RESET << std::endl;
}

void Logger::printLog(std::string message)
{
	this->getTime();
	std::cout << ANSI_COLOR_GREEN << message << ANSI_COLOR_RESET << std::endl;
}

void Logger::printLogNoTime(std::string message)
{
	std::cout << "\t\t\t" << ANSI_COLOR_GREEN << message << ANSI_COLOR_RESET << std::endl;
}
