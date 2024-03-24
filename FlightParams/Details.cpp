#define _CRT_SECURE_NO_WARNINGS 



#include "../Common/SimpleHTTPConstruct.h"
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <map>
#include "../Common/SHA256.h"
#include "string"
#include <list>


class mainFunc : public SimpleHTTPConstruct::SimpleHTTPConstruct {
public:
    static void RunMainFunc(std::string = 0);
};

#define HTTP_methoods SimpleHTTPConstruct::SimpleHTTPConstruct


void mainFunc::RunMainFunc(std::string input) {
    std::cout << AsIs("Content-Type: text/html; charset=utf-8" + std::string("\n\n"));

    std::cout <<
        AsIs("<!DOCTYPE HTML>") +

        HTML("",
            Head("",
                "<meta encoding = \"utf-8\">" +
                AsIs("\n<title> login page </title>")
            ) +
            Body("align = \"center\"",
                Paragrah("align = \"center\"", StringToWString(input))
            )
        );
}

//Вернуть RawValue 
std::string QueryTo_RawValue(std::string Name_var, std::string query) {

    std::string retval;
    size_t VarDev_Pos = query.find(Name_var);

    if (VarDev_Pos != std::wstring::npos) {
        std::string tempVar = query.substr(VarDev_Pos + Name_var.size() + 1, query.size());
        retval = tempVar;

        auto DeviderPos = tempVar.find('&');

        if (DeviderPos != std::wstring::npos) {
            retval = tempVar.substr(0, DeviderPos);
        }
    }
    else {
        return "";
    }
    return retval;
}





int main() {


    setlocale(LC_ALL, "Russian");
    std::string body,
        action;
    action = getenv("REQUEST_URI");




    if (getenv("REQUEST_METHOD") != "GET" && action == "/cgi-bin/Details.cgi") {

        mainFunc::RunMainFunc("SOME_TEXT");

        std::getline(std::cin, body);
    
    };
    return 0;
}
