#include <iostream>
#include <conio.h>
#include "ConfigParseAndRequests/json_storage.h"
#include "Interface/ConsoleInterface.h"


int main(int argc, char** argv) {
    setlocale( LC_ALL, "en-US" );

    json_storage weather;
    weather.GetConfig("w.json");

    weather.JsonCoordinatesSaver();
    weather.JsonWeatherSaver();
    weather.ParseParameters();

    ConsoleInterface Interface(weather);

    Interface.CreateForecast();
    int key_button;
    while (true) {
        if (kbhit()) {
            key_button = _getch();
            switch (key_button) {
                case 117:
                    Interface.CreateForecast(); // update
                    break;
                case 110:
                    Interface.NextCity();   // next
                    Interface.CreateForecast();
                    break;
                case 112:
                    Interface.PreviousCity();   // previous
                    Interface.CreateForecast();
                    break;
                case 27:
                    exit(0);    // exit
                case 43:
                    Interface.IncreaseDays();   // increment days amount
                    Interface.CreateForecast();
                    break;
                case 45:
                    Interface.DecreaseDays();   //decrement days amount
                    Interface.CreateForecast();
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}
