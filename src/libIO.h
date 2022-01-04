#ifndef LIBIO_H
#define LIBIO_H

#include <string>

void parseCommand(const std::string line, std::string& command, std::string& value);
#endif