#define _CRT_SECURE_NO_WARNINGS 



#include "..\Common\SimpleHTTPConstruct.h"
#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <map>
#include "../Common/SHA256.h"
#include <list>


class mainFunc : public SimpleHTTPConstruct::SimpleHTTPConstruct {
public:
    static void RunMainFunc(void);
};

#define HTTP_methoods SimpleHTTPConstruct::SimpleHTTPConstruct


void mainFunc::RunMainFunc() {
    std::cout << "Content-Type: text/html; charset=utf-8" + std::string("\n\n");

    std::cout <<
        AsIs("<!DOCTYPE HTML>") +

        HTML("",
            Head("",
                "<meta encoding = \"utf-8\">" +
                AsIs("\n<title> login page </title>")
            ) +
            Body("align = \"center\"",
                Form("METHOD = \"POST\"",
                    AsIs("<h1 align = \"center\" > Создайте новый аккаунт </h1>\n") +
                    Paragrah("align = \"center\"",
                        Paragrah("", "Login") +
                        AsIs("<input name = \"text\"> ") +
                        Paragrah("", "Password") +
                        AsIs("<input name = \"pass\">")
                    ) +
                    Paragrah("align = \"center\"",
                        AsIs("<input type = \"submit\"; style=\"background-color: green\"; value = \"Create\">")
                    )
                )+
                Form("METHOD = \"POST\" action = Autorization.cgi",

                    Paragrah("align = \"center\"",
                        AsIs("<input type = \"submit\"; style=\"background-color: white\"; value = \"back to autorization\">")
                    )
                )+

                Form("METHOD = \"POST\" action = MainPage.cgi",
                   
                    Paragrah("align = \"center\"",
                        AsIs("<input type = \"submit\"; style=\"background-color: Yellow\"; value = \"back to mainPage\">")
                    )
                )
            )
        );
}



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



bool IsPersonExist(std::string Username) {

    const std::string accounts_path = "account.properties";
    std::ifstream ifstr(accounts_path);
    std::string Credential, UserName;

    std::set<std::string>UserNames;

    while (std::getline(ifstr, Credential)) { // пока не достигнут конец файла класть очередную строку в переменную (s)
        UserName = Credential.substr(0, Credential.find(' '));
        UserNames.emplace(UserName);
    }

    std::string NamesStr = "Names: ";
    for (auto& it : UserNames)
        NamesStr += it;


    return (UserNames.find(Username) != UserNames.end());
}


int main() {

    setlocale(LC_ALL, "Russian");
    const std::string accounts_path = "account.properties";

    mainFunc::RunMainFunc();
    std::string body,
        action;


    std::getline(std::cin, body);
    action = getenv("REQUEST_URI");
    
    if (getenv("REQUEST_METHOD") != "GET") {

        IsPersonExist("Name");

        std::string Name,
            Password;

        if (body.find('%') != body.npos)
            std::cout << HTTP_methoods::Paragrah("", "<font> <b> Login or password contain forbidden symbol<b> </font>");
        else {
            Name = QueryTo_RawValue("text", body);

            if (!IsPersonExist(Name)) {
                Password = QueryTo_RawValue("pass", body);
                char* cPassword[20];
                for (auto it = 0; it < Password.size(); it++)
                    *(cPassword + it) = &(Password.at(it));
                SHA256Crypt CrypthPass(*cPassword);

                std::ofstream ofstr(accounts_path, std::ios::app);
                ofstr << Name << " " << CrypthPass.Crypted << "\n";
                ofstr.close();


                std::string success_str = " User " + HTTP_methoods::StringToWString(Name) + "successfully created!";
                std::cout << HTTP_methoods::Paragrah("", success_str);


            }
            else {
                std::cout << HTTP_methoods::Paragrah("", "This name already used\n");
            }

        }
    };
    return 0;
}
