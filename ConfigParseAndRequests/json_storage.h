#pragma once
#include "cpr/cpr.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class json_storage {
private:
    std::string api = "z4y20K2fY5FAt3YrIrzC8P8tTSnzPHUL5FYFv7R0";

    int day;
    int update_time;
    std::vector<std::string> processed_cities;
    std::vector<std::pair<float, float>> json_city_storage;
    std::vector<json> weather;

    std::vector<float> max_temperatures;
    std::vector<float> min_temperatures;
    std::vector<float> precipitations; //осадки
    std::vector<int> weather_codes;

public:
    void GetConfig(std::string file_path);

    void GetRequestCoordinates(const std::string& city);

    void JsonCoordinatesSaver();

    void GetRequestWeather(float latitude, float longitude);

    void JsonWeatherSaver();

    void print();
    void print1();

    int GetDays() const;

    int GetSizeProcessedCities() const;

    void ParseParameters();

    std::string GetCity(int index);
    bool IsCity(int index);
    std::string GetDate(int current_day);
    int GetPrecipitationValue(int city, int index);
    int GetMinTempValue(int city, int index);
    int GetMaxTempValue(int city, int index);
    int GetWeatherCode(int city, int index);
};