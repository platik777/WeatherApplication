#include "json_storage.h"


void json_storage::GetConfig(std::string file_path) {
    std::ifstream settings_config(file_path);
    json settings = json::parse(settings_config);
    update_time = settings["update"];
    day = settings["day"];
    for (int i = 0; i < settings["city"].size(); i++) {
        processed_cities.emplace_back(settings["city"][i]);
    }
}

void json_storage::GetRequestCoordinates(const std::string& city) {
    cpr::Response r = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city?name=" + city},
                               cpr::Header{{"X-Api-Key", api}});
    json temp = json::parse(r.text);
    if (!temp.empty()) {
        json_city_storage.emplace_back(temp[0]["latitude"], temp[0]["longitude"]);
    } else {
        json_city_storage.emplace_back(-1, -1);
    }
}

void json_storage::JsonCoordinatesSaver() {
    for (auto & processed_city : processed_cities) {
        GetRequestCoordinates(processed_city);
    }
}

void json_storage::GetRequestWeather(float latitude, float longitude) {
    cpr::Response r = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast?latitude=" +
                                        std::to_string(latitude) +
                                        "&longitude=" + std::to_string(longitude) +
                                        "&hourly=temperature_2m,precipitation,weathercode&forecast_days=16"});
    json temp = json::parse(r.text);
    if (r.status_code != 200) {
        temp = R"([])"_json;
    }
    weather.emplace_back(temp);
}

void json_storage::JsonWeatherSaver() {
    json empty_json = R"([])"_json;
    for (int i = 0; i < json_city_storage.size(); i++) {
        if (json_city_storage[i].first == -1) {
            weather.emplace_back(empty_json);
        } else {
            GetRequestWeather(json_city_storage[i].first, json_city_storage[i].second);
        }
    }
}

void json_storage::print() {
    for (auto & i : weather) std::cout << i << "\n\n";
}

void json_storage::ParseParameters() {
    json empty_json = R"([])"_json;
    float max_precipitation = 0;
    float max_temperature = 0;
    float min_temperature = 200;
    int max_weather_code = 0;
    for (int i = 0; i < weather.size(); i++) {
        if (weather[i] != empty_json) {
            for (int j = 0; j < 16; ++j) {
                for (int k = 0; k < 4; ++k) {
                    for (int h = 0; h < 6; h++) {
                        max_precipitation = std::max(max_precipitation,
                                                     static_cast<float>(weather[i]["hourly"]["precipitation"][24 * j +
                                                                                                              k*6+h]));
                        auto temp = static_cast<float>(weather[i]["hourly"]["temperature_2m"][24 * j + k*6+h]);
                        max_temperature = std::max(max_temperature, temp);
                        min_temperature = std::min(min_temperature, temp);
                        max_weather_code = std::max(max_weather_code,
                                                    static_cast<int>(weather[i]["hourly"]["weathercode"][24 * j + k*6+h]));
                    }
                    precipitations.emplace_back(max_precipitation);
                    max_temperatures.emplace_back(max_temperature);
                    min_temperatures.emplace_back(min_temperature);
                    weather_codes.emplace_back(max_weather_code);
                    max_precipitation = 0;
                    max_temperature = 0;
                    min_temperature = 200;
                    max_weather_code = 0;
                }
            }
        } else {
            for (int j = 0; j < 64; ++j) {
                precipitations.emplace_back(0.0);
                max_temperatures.emplace_back(0.0);
                min_temperatures.emplace_back(0.0);
                weather_codes.emplace_back(0);
            }
        }
    }
}

void json_storage::print1() {
    for (int j = 0; j < 5; j++) {
        std::cout << processed_cities[j] << '\n';
        for (int i = 0; i < 64; i++)
            std::cout << precipitations[64*j + i] << ' ' << min_temperatures[64*j + i] << ' ' << max_temperatures[64*j + i] << ' '
                      << weather_codes[64*j + i] << "\n";
    }
}

int json_storage::GetDays() const {
    return day;
}

int json_storage::GetSizeProcessedCities() const{
    return processed_cities.size();
}

int json_storage::GetPrecipitationValue(int city, int index) {
    return ceil(precipitations[city*64 + index]);
}

int json_storage::GetMinTempValue(int city, int index) {
    return ceil(min_temperatures[city*64 + index]);
}

int json_storage::GetMaxTempValue(int city, int index) {
    return ceil(max_temperatures[city*64 + index]);
}

int json_storage::GetWeatherCode(int city, int index) {
    return weather_codes[city*64 + index];
}

std::string json_storage::GetCity(int index) {
    return processed_cities[index];
}

std::string json_storage::GetDate(int current_day) {
    return weather[0]["hourly"]["time"][current_day*24];
}

bool json_storage::IsCity(int index) {
    if (json_city_storage[index].first == -1) return false;
    return true;
}





