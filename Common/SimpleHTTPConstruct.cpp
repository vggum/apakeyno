#pragma once
#include "SimpleHTTPConstruct.h"

std::string SimpleHTTPConstruct::SimpleHTTPConstruct::Paragrah(std::string attributes, std::string content)
{
    std::string retString;
    retString = "\n<p" + (attributes != "" ? " " + attributes + ">" : ">") + "\n" + content + "\n</p>";
    return retString;
}

std::string SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(const std::string& s)
{
    std::string retWstr(s.begin(), s.end());
    return retWstr;
}

std::string SimpleHTTPConstruct::SimpleHTTPConstruct::Meta(std::string attributes)
{
    return "<meta" + (attributes == "" ? ">" : " " + attributes + " >") + "\n";
}

std::string SimpleHTTPConstruct::SimpleHTTPConstruct::Body(std::string attributes, std::string content)
{
    return "<body" + (attributes == "" ? ">" : " " + attributes + " >") + content + "\n</body>";
}

std::string SimpleHTTPConstruct::SimpleHTTPConstruct::Head(std::string attributes, std::string content)
{
    return "<head" + (attributes == "" ? ">" : attributes + " >") + "\n" + content + "\n</head>\n";
}

std::string SimpleHTTPConstruct::SimpleHTTPConstruct::HTML(std::string attributes, std::string content)
{
    return "\n<htm" + (attributes == "" ? ">" : attributes + " >") + "\n" + content + "\n</html>";
}

std::string SimpleHTTPConstruct::SimpleHTTPConstruct::Form(std::string  attributes, std::string content)
{
    return "\n<form" + (attributes == "" ? ">" : " "+ attributes + " >") + content + "</form>";
}

std::string SimpleHTTPConstruct::SimpleHTTPConstruct::Select(std::string attributes, std::vector<std::string> options)
{
    std::string options_wstr;
    
    for (auto& it : options) {
        options_wstr += "<option value =\"" + it + "\"> " + it + " </option>\n";
    }


    return "\n<select" + (attributes == "" ? ">" : " " + attributes + " >") + options_wstr + "</select>";
}



std::string SimpleHTTPConstruct::SimpleHTTPConstruct::AsIs(std::string content)
{
    return content;
}

std::string SimpleHTTPConstruct::SimpleHTTPConstruct::Img(std::string params)
{
    return "<img " + params + " >";
}

std::map<std::string, std::string> SimpleHTTPConstruct::SimpleHTTPConstruct::GetCookies() {
	auto res = std::map<std::string, std::string>();
	if (getenv("HTTP_COOKIE")) {
		std::string cookie_string = getenv("HTTP_COOKIE");
		std::string delimiter = "; ";
		std::string name, value;
		size_t pos = 0, pos_ = 0;;
		std::string token;
		while ((pos = cookie_string.find(delimiter)) != std::string::npos) {
			token = cookie_string.substr(0, pos);
			pos_ = token.find("=");
			name = token.substr(0, pos_);
			token.erase(0, pos_ + std::string("=").length());//I suck cocks
			value = token;
			res.emplace(name, value);
			cookie_string.erase(0, pos + delimiter.length());
		}
		token = cookie_string;
		pos_ = token.find("=");
		name = token.substr(0, pos_);
		token.erase(0, pos_ + std::string("=").length());//I suck cocks
		value = token;
		res.emplace(name, value);
	}
	return res;
}

std::string SimpleHTTPConstruct::SimpleHTTPConstruct::rawURLDecode(std::string raw) {
    int NumCntr = 0,
        TempNum = 0;

    std::string loginHex,
        passHex,
        temp,
        retval;
    std::vector<int>AlphasInUint;

    for (size_t it = 0; it < raw.size() + 1; it++) {

        if (raw[it] != '%' && it != raw.size()) {
            temp += raw[it];
        }
        else {
            NumCntr++;
            TempNum += std::stoi(temp, 0, 16);
            if (NumCntr == 2) {
                AlphasInUint.push_back(TempNum);
                TempNum = 0;
                NumCntr = 0;
            }
            temp.clear();
            continue;
        }
    }

    for (auto it = 0; it < AlphasInUint.size(); it++)
    {
        if (AlphasInUint.at(it) >= 352)
            AlphasInUint.at(it) += 688;
        else {
            AlphasInUint.at(it) += 751;

        }
        retval.push_back((AlphasInUint.at(it)));
    }
    return retval;
}