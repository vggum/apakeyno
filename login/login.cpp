#define _CRT_SECURE_NO_WARNINGS 



#include "SimpleHTTPConstruct.h"
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <map>
#include "SHA256.h"


    class mainFunc : public SimpleHTTPConstruct::SimpleHTTPConstruct {
    public:
        static void RunMainFunc(void);
		static std::map<std::string, std::string> GetCookies();
    };


    void mainFunc::RunMainFunc() {
		auto cookie = GetCookies();
		std::wcout << AsIs(L"Content-Type: text/html; charset=utf-8" + std::wstring(L"\n\n"));

        std::wcout <<
            AsIs(L"<!DOCTYPE HTML>") +

            HTML(L"",
                Head(L"",
                    L"<meta encoding = \"windows-1251\">" +
                    AsIs(L"\n<title> login page </title>") 
                ) +
                Body(L"align = \"center\"",
                    Form(L"METHOD = \"POST\"",
                        AsIs(L"<h1 align = \"center\" > For continue enter your Account data </h1>\n") +
                        Paragrah(L"align = \"center\"",
                            Paragrah(L"", L"Логин") +
                            AsIs(L"<input name = \"text\" value =\"") +
							StringToWString(cookie["name"]+
							AsIs(L"\"> ") +

                            Paragrah(L"", L"Пароль") +
                            AsIs(L"<input name = \"pass\" value =\"") +
							StringToWString(cookie["password"])+
							AsIs(L"\"> ")
                            ) +
                        Paragrah(L"align = \"center\"",
                            AsIs(L"<input type = \"submit\"; style=\"background-color: green\"; value = \"Атправиц\">")
                        )
                        )
                    )
                );
    }
	std::map<std::string, std::string> mainFunc::GetCookies(){
		auto res = std::map<std::string, std::string>();
		if (getenv("HTTP_COOKIE")){
			std::string cookie_string = getenv("HTTP_COOKIE");
			std::string delimiter = "; ";
			std::string name, value;
			size_t pos = 0, pos_ = 0;;
			std::string token;
			while ((pos = cookie_string.find(delimiter)) != std::string::npos) {
				token = cookie_string.substr(0, pos);
				pos_ = token.find("=");
				name = token.substr(0, pos_);
				token.erase(0, pos_+ std::string("=").length());//I suck cocks
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



    std::wstring rawURLDecode(std::wstring raw) {
        int NumCntr = 0,
            TempNum = 0;

        std::wstring loginHex,
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

    //DEPRECATED Methods

#if 0
    //UTF-8  application/x-www-form-urlencoded


    std::wstring OLDDecodeRAWstring(const std::wstring& rawstr) {

        if (rawstr.find('%') != rawstr.npos) {
            std::wstring loginHex,
                passHex,
                temp;
            std::wstring retval = L"";
            std::vector<std::wstring> tempcontainer;
            std::vector<int>AlphasInUint;

            int NumCntr = 0,
                TempNum = 0;



            size_t SubstrDev = rawstr.find('&');

            if (rawstr.find('&') != std::wstring::npos) {
                passHex = rawstr.substr(SubstrDev + 1, rawstr.size() - SubstrDev - 1);
                passHex = passHex.substr(passHex.find('%') + 1, passHex.size() - 1);
                tempcontainer.push_back(passHex);
            }
            else {
                SubstrDev = rawstr.size();
            }
            loginHex = rawstr.substr(0, SubstrDev);
            loginHex = loginHex.substr(loginHex.find('%') + 1, loginHex.size() - loginHex.find('%'));
            tempcontainer.push_back(loginHex);


            for (auto& input_wstring : tempcontainer) {

                TempNum = 0;
                NumCntr = 0;
                temp.clear();

                for (size_t it = 0; it < loginHex.size() + 1; it++) {

                    if (input_wstring[it] != '%' && it != input_wstring.size()) {
                        temp += input_wstring[it];
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
                AlphasInUint.clear();
            }
            return retval;
        }
        else {
            return rawstr;
        }
    }
#endif

#if 0 
    std::wstring QueryTo_RawValue(std::wstring Name_var, std::wstring query) {

        std::wstring var;
        size_t SubstrDev = query.find(Name_var);

        if (SubstrDev != std::wstring::npos) {
            std::wstring tempVar = query.substr(SubstrDev + Name_var.size() + 1, query.size());
            var = tempVar;

            auto DeviderPos = tempVar.find('&');

            if (DeviderPos != std::wstring::npos) {
                var = tempVar.substr(0, DeviderPos);
            }
        }
        else {
            return L"";
        }
        return var;
    }
#endif

#if 0
    std::wstring DecodeRAWstring(const std::wstring& rawstr) {

        std::wstring temp,
            tempWStr;

        for (size_t it = 1; it < rawstr.size() + 1; it++) {
            if (rawstr[it] != '%' && it != rawstr.size()) {
                temp += rawstr[it];
            }
            else {
                tempWStr.push_back(std::stoi(temp, 0, 16) + 848);
                temp.clear();
                continue;
            }
        }

        std::wstring RV = tempWStr;
        return RV;
    }
#endif




    std::wstring StringToWString(const std::string& s)
    {
        std::wstring retWstr(s.begin(), s.end());
        return retWstr;
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



    void AuthService(std::pair<std::string, std::string> AuthDATa) {

        std::string credentials;
        std::map<std::string, std::string> credentialVector;

        const std::string accounts_path = "account.properties";
        std::ifstream ifstr(accounts_path);

        if (!ifstr) {
            std::wcout << "accounts_path file not exist<br>";

            std::ofstream ofstr(accounts_path);
            ofstr << AuthDATa.first << " " << AuthDATa.second;
            ofstr.close();
        }
        else {

            if (ifstr.is_open())
            {
                while (std::getline(ifstr, credentials))
                {
                    if (credentials != "") {
                        size_t spaceSymb = credentials.find(" ");
                        credentialVector.emplace(credentials.substr(0, credentials.size() - spaceSymb - 1), credentials.substr(spaceSymb + 1, credentials.size() - spaceSymb));
                        credentials.clear();
                    }
                }
            }
            ifstr.close();
            if (!credentials.size()) {
                if (credentialVector.find(AuthDATa.first) != credentialVector.end())
                    std::wcout << L"Добро пожаловать";
                else
                    std::wcout << L"НЕ НАЙДЕН ПОЛЬЗОВАТЕЛЬ С ТАКИМИ ДАННЫМИ";
            }
            else {
                std::wcout << SimpleHTTPConstruct::SimpleHTTPConstruct::Paragrah(L"", L" Список пользователей пуст");
            }

        }
        
    }


    int main() {
        enum HTTP_env {
            COMSPEC = 0, DOCUMENT_ROOT, GATEWAY_INTERFACE,
            HTTP_ACCEPT, HTTP_ACCEPT_ENCODING,
            HTTP_ACCEPT_LANGUAGE, HTTP_CONNECTION,
            HTTP_HOST, HTTP_USER_AGENT, PATH,
            QUERY_STRING, REMOTE_ADDR, REMOTE_PORT,
            REQUEST_METHOD, REQUEST_URI, SCRIPT_FILENAME,
            SCRIPT_NAME, SERVER_ADDR, SERVER_ADMIN,
            SERVER_NAME, SERVER_PORT, SERVER_PROTOCOL,
            SERVER_SIGNATURE, SERVER_SOFTWARE
        };

        setlocale(LC_ALL, "Russian");
        std::string body,
                    action;
        action = getenv("REQUEST_URI");
		std::string method = getenv("REQUEST_METHOD");
		if (method == "GET" && action == "/cgi-bin/login.cgi"){
			//std::wcout << SimpleHTTPConstruct::SimpleHTTPConstruct::AsIs(L"Content-Type: text/html; charset=utf-8" + std::wstring(L"\n\n"));
			mainFunc::RunMainFunc();
		}
		//std::wcout << L"<br>"<< SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(action);
		//std::wcout << L"<br>" << SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(method);


        else if (method == "POST" && action == "/cgi-bin/login.cgi") {
        std::getline(std::cin, body);

#ifdef DEBUG
            std::wcout << SimpleHTTPConstruct::SimpleHTTPConstruct::Paragrah(L"", StringToWString(body));
#endif
            /*std::wstring wName,
                         wPassword;*/
			//std::wcout << SimpleHTTPConstruct::SimpleHTTPConstruct::AsIs(L"Content-Type: text/html; charset=utf-8" + std::wstring(L"\n\n"));
			//mainFunc::RunMainFunc();
			//return 0;
            std::string Name,
                        Password;
			bool isValidNumber = false;

			if (body.find('%') == body.npos){
				isValidNumber = true;
				Name = QueryTo_RawValue("text", body);
				Password = QueryTo_RawValue("pass", body);
				std::wcout << L"Set-Cookie: name=" << SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(Name) << std::endl;
				std::wcout << L"Set-Cookie: password=" << SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(Password) << std::endl;
				mainFunc::RunMainFunc();

				char *cName[20],
					*cPassword[20];

				for (auto it = 0; it < Name.size(); it++)
					*(cName + it) = &(Name.at(it));//at(it);

				for (auto it = 0; it < Password.size(); it++)
					*(cPassword + it) = &(Password.at(it));//at(it);

				SHA256Crypt CrypthName(*cName);
				SHA256Crypt CrypthPass(*cPassword);
				//std::wcout << SimpleHTTPConstruct::SimpleHTTPConstruct::Paragrah(L"", L"CryptName:" + StringToWString(CrypthName.Crypted) + L"<br>");
				//std::wcout << SimpleHTTPConstruct::SimpleHTTPConstruct::Paragrah(L"", L"CryptPassword:" + StringToWString(CrypthPass.Crypted) + L"<br>");
				AuthService(std::make_pair(CrypthName.Crypted, CrypthPass.Crypted));
			}
			if (!isValidNumber){
				mainFunc::RunMainFunc();
				std::wcout << SimpleHTTPConstruct::SimpleHTTPConstruct::Paragrah(L"", L"<font color = \"red\"> <b> Логин и/или пароль содержат недопустимые символы <b> </font>");
			}
    //            if(getenv("HTTP_COOKIE"))
				//	std::wcout << L"<br>" << SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(getenv("HTTP_COOKIE"));
				//else{
				//	std::wcout << L"Set-Cookie: name=" << SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(Name) << std::endl;
				//	std::wcout << L"Set-Cookie: password=" << SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(Password) << std::endl;
    //        }
        }
		/*else {
			std::wcout << SimpleHTTPConstruct::SimpleHTTPConstruct::AsIs(L"Content-Type: text/html; charset=utf-8" + std::wstring(L"\n\n"));
			mainFunc::RunMainFunc();
			std::wcout << L"<br> Action:"<< SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(action);
			std::wcout << L"<br> Method:" << SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(method);
		}*/
        return 0;
    }
