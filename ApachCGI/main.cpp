#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "../Common/SimpleHTTPConstruct.h"
#include <set>


using namespace std;
using namespace SimpleHTTPConstruct;

class mainFunc : public SimpleHTTPConstruct {
public:
    static const std::string action(void) {
        if (StringToWString(getenv("REQUEST_METHOD")) != "") {
            return Paragrah("", StringToWString(getenv("QUERY_STRING")) );
        }
    }

    static void RunMainFunc(void) {
        std::cout << AsIs("Content-Type: text/html; charset=utf-8" + std::string("\n\n"));

        std::cout <<
            AsIs("<!DOCTYPE HTML>") +

            HTML("",
                Head("",
                    AsIs("<title> RZD </title>")
                ) +
                Body("",
                    Paragrah(
                        "align = \"center\"",
                        AsIs("<font color = \"green\" face = \"Comic Sans MS\"> Save the <b>Queen!!!<b> </font>")
                    ) +
                    Paragrah("align = \"center\" ",
                        Img("src = \"https://riamo.ru/files/image/05/35/94/-gallery!kt1.jpg\" alt = \"Can`t load RZD image\" width = \"700\"")
                    ) +
                    Form("METHOD=\"POST\" action = Autorization.cgi",
                        Paragrah("align = \"center\"",
                            AsIs("<input type = \"submit\" value=\"Let`s GO!\"  style=\"background: rgb(250, 132, 43); border-radius: 0.1cm; width: 10cm;\" > ")
                            
                        )
                    ) 
                   + action()
                )
            );
    }
};

int main()
{
    mainFunc::RunMainFunc();
    return -1;
}

