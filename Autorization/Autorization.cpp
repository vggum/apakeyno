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
    static void RunMainFunc(void);
};

#define HTTP_methoods SimpleHTTPConstruct::SimpleHTTPConstruct

//Вернуть RawValue 
std::string QueryTo_RawValue(std::string Name_var, std::string query) {

    std::string retval;
    size_t VarDev_Pos = query.find(Name_var);

    if (VarDev_Pos != std::string::npos) {
        std::string tempVar = query.substr(VarDev_Pos + Name_var.size() + 1, query.size());
        retval = tempVar;

        auto DeviderPos = tempVar.find('&');

        if (DeviderPos != std::string::npos) {
            retval = tempVar.substr(0, DeviderPos);
        }
    }
    else {
        return "";
    }
    return retval;
}

void mainFunc::RunMainFunc() {

    auto cookie = HTTP_methoods::GetCookies();
    std::string body, Name, Password;
    std::getline(std::cin, body);

    Name = QueryTo_RawValue("text", body);
    Password = QueryTo_RawValue("pass", body);
    std::cout << "Set-Cookie: name=" << Name << std::endl;
    std::cout << "Set-Cookie: password=" << Password << std::endl;
    std::cout << AsIs("Content-Type: text/html; charset=utf-8" + std::string("\n\n"));

    std::cout <<
        AsIs("<!DOCTYPE HTML>") +
        HTML("",
            Head("",
                "<meta encoding = \"utf-8\">" +
                AsIs("\n<title> Авторизация </title>")
            ) +
            Body("align = \"center\"",
                Form("METHOD = \"POST\" action = RZD.cgi",
                    AsIs("<h1 align = \"center\" > Введите данные аккаунта </h1>\n") +
                    Paragrah("align = \"center\"",
                        Paragrah("", "Login") +
                        AsIs("<input name = \"login\" value =\"" +
                             StringToWString(cookie["name"] + "\"> ")
                        )+

                        Paragrah("", "Password") +
                        AsIs("<input name = \"password\" value =\"" +
                             StringToWString(cookie["password"] + "\"> ")   
                        )
                    ) +
                    Paragrah("align = \"center\"",
                        AsIs("<input type = \"submit\"; style=\"background-color: green\"; value = \"sign In\">")
                    )
                )
            )
        );


}



int main() {
    mainFunc::RunMainFunc();
    return 0;
}