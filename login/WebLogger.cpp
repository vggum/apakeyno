#include "WebLogger.h"

WebLogger::WebLogger(std::string message) {

	std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string CurTim = std::ctime(&tt);

	std::ofstream ofs;
	ofs.open(WebLogger::Path, std::ios::app);
	ofs <<"Time:" << CurTim.substr(0, CurTim.size()-5) << message << std::endl;
	ofs.close();
	this->~WebLogger();
}

WebLogger::~WebLogger()
{
	//std::ofstream ofs;
	//ofs.open(WebLogger::Path, std::ios::app);
	//ofs << "Distructor is run" << std::endl;
	//ofs.close();
}

