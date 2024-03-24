#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <time.h>   
#include <ctime>

class WebLogger {
public:
        WebLogger(std::string message);
        const std::string Path = "listing.log";
        ~WebLogger();
};
