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
#include "WebLogger.h"
#include <fstream>



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

        std::cout << "Content-Type: text/html; charset=utf-8\r\n\r\n";

        std::cout <<
            AsIs("<!DOCTYPE HTML>\n") +
            AsIs("<HTML>\n") +
                AsIs("<meta encoding = \"utf-8\">" +
                    AsIs("\n<title> Авторизация </title>")
                )+
                AsIs("\n<body align = \"center\">\n <br> <br> <br>\n");
    }


    void siteLogicRun(std::string input) {

        std::cout << HTTP_methoods::AsIs("<h1 align = \"center\"> РЖД билеты </h1>");


        std::cout << HTTP_methoods::Paragrah("align = \"center\"",
             "<br> <b> Отправьте файл для подтверждения личности : </b> " +
            HTTP_methoods::Form("enctype =\"multipart/form-data\" method = \"POST\" action = /cgi-bin/RZD.cgi ",
                HTTP_methoods::AsIs("<label align = \"left\" for=\"ProfilePic\"> Profile photo:   <\label>") +
                HTTP_methoods::AsIs("\n<input type = \"file\" id = \"ProfilePic\" name = \"ProfilePic\" accept=\"image/jpeg\"> <br><br>") +

                HTTP_methoods::AsIs("<label align = \"left\" for=\"VoiceRec\"> Voice example:    <\label>") +
                HTTP_methoods::AsIs("\n<input type = \"file\" id = \"VoiceRec\" name = \"VoiceRec\" accept = \"audio/*\"> <br><br>") +

                HTTP_methoods::AsIs("<label align = \"left\" for=\"VideoRec\"> Video example:    <\label>") +
                HTTP_methoods::AsIs("\n<input type = \"file\" id = \"VideoRec\" name = \"VideoRec\" accept=\"video/*\"> <br><br>") +

                HTTP_methoods::AsIs("<label align = \"left\" for=\"PersonalDocument\"> personal document scan (.pdf):    <\label>") +
                HTTP_methoods::AsIs("\n<input type = \"file\" id = \"PersonalDocument\" name = \"PersonalDocument\" accept=\"application/pdf\"> <br><br><br>") +

                HTTP_methoods::AsIs("<label align = \"left\" for=\"TXT_file\"> Your resume in text file (.txt):    <\label>") +
                HTTP_methoods::AsIs("\n<input type = \"file\" id = \"TXT_file\" name = \"TXT_file\" accept=\"> <br><br><br>") +

                HTTP_methoods::AsIs("<label align = \"left\" for=\"Archive\"> If u have a problem with file uploading,<br> send it in archive by clicking button below:<br><\label>") +
                HTTP_methoods::AsIs("\n<input type = \"file\" id = \"Archive\" name = \"Archive\" accept=\"application/zip, application/x-gzip\"> <br>") +


                HTTP_methoods::AsIs("\n<br><br>\n <input type = \"submit\"; style=\"width: 10cm; height: 1cm\"; value = \"Upload\">\n")    
            )
        );

        std::cout <<
            HTTP_methoods::AsIs("\n</body>\n<\HTML>");
            
    }

    bool AuthService(std::pair<std::string, std::string> AuthDATa) {

        bool AllowLogging = false;

        std::string credentials;
        std::map<std::string, std::string> credentialVector;

        const std::string accounts_path = "account.properties";
        std::ifstream ifstr(accounts_path);

        if (!ifstr) {
            std::cout << "config file doesn`t exist <br>";

            //Создаем файл с AuthDATa внутри
            std::ofstream ofstr(accounts_path);
            ofstr << AuthDATa.first << " " << AuthDATa.second << "\n";
            ofstr.close();
            AllowLogging = true;
        }
        else {

            if (ifstr.is_open())
            {
                while (std::getline(ifstr, credentials))
                {
                    if (credentials != "") {
                        size_t spaceSymb = credentials.find(" ");
                        credentialVector.emplace(credentials.substr(0, spaceSymb), credentials.substr(spaceSymb + 1, credentials.size() - spaceSymb));
                        credentials.clear();
                    }
                }
            }


            ifstr.close();
            if (!credentials.size()) {
                if (credentialVector.find(AuthDATa.first) != credentialVector.end()) {
                    if (credentialVector.at(AuthDATa.first) == AuthDATa.second) {
                        AllowLogging = true;
                        siteLogicRun(AuthDATa.first);
                    }
                    else {
                        std::cout << HTTP_methoods::Paragrah("align = \"center\"", "wrong password" +
                                HTTP_methoods::Form("METHOD = \"POST\" action = Autorization.cgi",
                                    HTTP_methoods::AsIs("<input type = \"submit\"; style=\"background-color: red\"; value = \"to mainPage\">"))
                        );


                    }
                }
                else {
                    std::cout << HTTP_methoods::Paragrah("", "wrong user or pass\n");
                    std::cout <<
                        HTTP_methoods::Form("METHOD = \"POST\" action = UserRegistration.cgi",

                            HTTP_methoods::Paragrah("align = \"center\"",
                                HTTP_methoods::AsIs("<input type = \"submit\"; style=\"background-color: Yellow\"; value = \"log in\">")
                            )
                        );
                    }
            }
        }
        return AllowLogging;     
    }


    int main() {

        mainFunc::RunMainFunc();

        std::string body,
            action,
            CONTENT,
            extBody;

        char buff;




        action = getenv("REQUEST_URI");
        new WebLogger("REQUEST_URI is: " + action);


        std::string RequestMethod = getenv("REQUEST_METHOD");

        std::string ContentType = getenv("CONTENT_TYPE");
        std::string ContentLength = getenv("CONTENT_LENGTH");
        std::string SERVER_PROTOCOL = getenv("SERVER_PROTOCOL");


        new WebLogger("ContentType: " + ContentType);
        new WebLogger("ContentLength: " + ContentLength);
        new WebLogger("RequestMethod: " + RequestMethod);
        new WebLogger("action: " + action);
        new WebLogger("SERVER_PROTOCOL: " + action);

        new WebLogger("finishing of getting env");



        if (RequestMethod != "GET" && action == "/cgi-bin/RZD.cgi") {

            uint64_t strleng = atoi(ContentLength.c_str());
            std::cin >> body;

            while (strleng) {
                std::cin >> buff;
                extBody.push_back(buff);
                strleng--;
            }
           // new WebLogger("std::cin: " + extBody);

            new WebLogger("BODY: " + body);

            std::string Name,
                Password;

            char* cPassword[20];



            if (body.find('%') != body.npos) {

                std::cout << HTTP_methoods::Paragrah("align = \"center\"", "login or pass contain forbidden symbol" +
                    HTTP_methoods::Form("METHOD = \"POST\" action = Autorization.cgi",
                        HTTP_methoods::AsIs("<input type = \"submit\"; style=\"background-color: red\"; value = \"back to mainPage\">"))
                );
                std::cout << HTTP_methoods::AsIs("\n</body>\n<\HTML>");
            }
            else {
                if (body.find("WebKitFormBoundary") != body.npos) {
                    std::cout << HTTP_methoods::AsIs("<h1 align = \"center\"> РЖД билеты </h1>");

                    std::cout << HTTP_methoods::Paragrah("align = \"center\"",
                        "<br> <b> Выберите направление и станцию выезда : </b> " +
                        HTTP_methoods::Form("METHOD = \"POST\" action = /cgi-bin/TimeSelect.cgi",
                            HTTP_methoods::Paragrah("", "Откуда <br>") +
                                HTTP_methoods::Select("name=\"Departure\"", { "Москва", "Казань", "Рязань", "Санкт-Петербург", "Воронеж", "Нижний Новгород", "Кисловодск", "Железноводск", "Анапа", "Геленджик", "Севастополь" })+"<br>" +
                            HTTP_methoods::Paragrah("", "Куда <br>") +
                                HTTP_methoods::Select("name=\"Arrive\"", { "Москва", "Казань", "Рязань", "Санкт-Петербург", "Воронеж", "Нижний Новгород", "Кисловодск", "Железноводск", "Анапа", "Геленджик", "Севастополь" }) + "\n<br>\n<br>\n" +
                            "<input type = \"submit\"; style=\"background-color: green\"; value = \"go to timeSelectPage\">")
                    );

                }
                else
                {
                    Name = QueryTo_RawValue("login", body);
                    Password = QueryTo_RawValue("password", body);

                    new WebLogger("User trying to auth with login: \"" + Name + "\" and pass: \"" + Password + "\"");




                    for (auto it = 0; it < Password.size(); it++)
                        *(cPassword + it) = &(Password.at(it));

                    SHA256Crypt CrypthPass(*cPassword);

                    AuthService(std::make_pair(Name, CrypthPass.Crypted));
                }

            }
            }
            else {
                std::cout << HTTP_methoods::Paragrah("align = \"center\"", HTTP_methoods::StringToWString("it is a GET METHOD"));

            }
        
        return 0;
    }
