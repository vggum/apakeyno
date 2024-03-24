#pragma once
#define _CRT_SECURE_NO_WARNINGS 

#include <string>
#include <vector>
#include <map>

namespace SimpleHTTPConstruct {

	class SimpleHTTPConstruct {
	public:
		static std::string Paragrah(std::string content, std::string attributes);
		static std::string Meta(std::string attributes = "");
		static std::string Body(std::string attributes, std::string content);
		static std::string Form(std::string attributes, std::string content);
		static std::string Select(std::string attributes, std::vector<std::string> options);
		static std::string AsIs(std::string content);
		static std::string Img(std::string params);
		static std::string Head(std::string attributes, std::string content);
		static std::string HTML(std::string attributes, std::string content);
		static std::string StringToWString(const std::string& s);
		static std::map<std::string, std::string> GetCookies();
		static std::string rawURLDecode(std::string raw);
	};


};