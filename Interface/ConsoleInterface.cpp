#include "ConsoleInterface.h"

std::unordered_map<int, std::string> Weather_codes = {
        {0, "Clear sky"},
        {1, "Mainly clear"},
        {2, "Partly cloudy"},
        {3, "Overcast"},
        {45, "Fog and depositing rime fog"},
        {51, "Drizzle: Light intensity"},
        {53, "Drizzle: Moderate intensity"},
        {55, "Drizzle: Dense intensity"},
        {56, "Freezing Drizzle: Light intensity"},
        {57, "Freezing Drizzle: Dense intensity"},
        {61, "Rain: Slight intensity"},
        {63, "Rain: Moderate intensity"},
        {65, "Rain: Heavy intensity"},
        {66, "Freezing Rain: Light intensity"},
        {67, "Freezing Rain: Heavy intensity"},
        {71, "Snow fall: Slight intensity"},
        {73, "Snow fall: Moderate intensity"},
        {75, "Snow fall: Heavy intensity"},
        {77, "Snow grains"},
        {80, "Rain showers: Slight intensity"},
        {81, "Rain showers: Moderate intensity"},
        {82, "Rain showers: Violent intensity"},
        {85, "Snow showers: Slight intensity"},
        {86, "Snow showers: Heavy intensity"},
        {95, "Thunderstorm: Slight or moderate"},
        {96, "Thunderstorm with slight hail"},
        {99, "Thunderstorm with heavy hail"}
};

ConsoleInterface::ConsoleInterface(const json_storage& json) {
    current_city = 0;
    this_json_storage = json;
    current_days_amount = this_json_storage.GetDays();
}

ConsoleInterface::ConsoleInterface(const ConsoleInterface& other) {
    this_json_storage = other.this_json_storage;
    current_city = other.current_city;
    current_days_amount = other.current_days_amount;
}

void ConsoleInterface::CreateForecast() {
    system("cls");
    std::cout << "Forecast for " + this_json_storage.GetCity(current_city) << '\n';
    if (!this_json_storage.IsCity(current_city)) {
        std::cout << "Can't receive forecast for this city\n" + this_json_storage.GetCity(current_city) + " does not exist";
    } else {
        for (int i = 0; i < current_days_amount; i++) {
            auto document = vbox(
                    text("Date: " + this_json_storage.GetDate(i).substr(0, 10)) | hcenter,
                    hbox({
                                 vbox(
                                         text("Night") | center | underlined | color(Color::Yellow),
                                         text("precipitation: " + std::to_string(
                                                 this_json_storage.GetPrecipitationValue(current_city, 4 * i)) + " mm"),
                                         text("min_temperature: " +
                                              std::to_string(this_json_storage.GetMinTempValue(current_city, 4 * i)) +
                                              " °C"),
                                         text("max_temperature: " +
                                              std::to_string(this_json_storage.GetMaxTempValue(current_city, 4 * i)) +
                                              " °C"),
                                         text(Weather_codes[this_json_storage.GetWeatherCode(current_city, 4 * i)])
                                 ) | border | flex_grow,
                                 vbox(
                                         text("Morning") | center | underlined | color(Color::Yellow),
                                         text("precipitation: " + std::to_string(
                                                 this_json_storage.GetPrecipitationValue(current_city, 4 * i + 1)) +
                                              " mm"),
                                         text("min_temperature: " + std::to_string(
                                                 this_json_storage.GetMinTempValue(current_city, 4 * i + 1)) + " °C"),
                                         text("max_temperature: " + std::to_string(
                                                 this_json_storage.GetMaxTempValue(current_city, 4 * i + 1)) + " °C"),
                                         text(Weather_codes[this_json_storage.GetWeatherCode(current_city, 4 * i + 1)])
                                 ) | border | flex_grow,
                                 vbox(
                                         text("Day") | center | underlined | color(Color::Yellow),
                                         text("precipitation: " + std::to_string(
                                                 this_json_storage.GetPrecipitationValue(current_city, 4 * i + 2)) +
                                              " mm"),
                                         text("min_temperature: " + std::to_string(
                                                 this_json_storage.GetMinTempValue(current_city, 4 * i + 2)) + " °C"),
                                         text("max_temperature: " + std::to_string(
                                                 this_json_storage.GetMaxTempValue(current_city, 4 * i + 2)) + " °C"),
                                         text(Weather_codes[this_json_storage.GetWeatherCode(current_city, 4 * i + 2)])
                                 ) | border | flex_grow,
                                 vbox(
                                         text("Evening") | center | underlined | color(Color::Yellow),
                                         text("precipitation: " + std::to_string(
                                                 this_json_storage.GetPrecipitationValue(current_city, 4 * i + 3)) +
                                              " mm"),
                                         text("min_temperature: " + std::to_string(
                                                 this_json_storage.GetMinTempValue(current_city, 4 * i + 3)) + " °C"),
                                         text("max_temperature: " + std::to_string(
                                                 this_json_storage.GetMaxTempValue(current_city, 4 * i + 3)) + " °C"),
                                         text(Weather_codes[this_json_storage.GetWeatherCode(current_city, 4 * i + 3)])
                                 ) | border | flex_grow
                         }));
            auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
            Render(screen, document);
            screen.Print();
        }
    }
}

void ConsoleInterface::IncreaseDays() {
    if (current_days_amount < 16) {
        current_days_amount++;
    }
}

void ConsoleInterface::DecreaseDays() {
    if (current_days_amount > 1) {
        current_days_amount--;
    }
}

void ConsoleInterface::NextCity() {
    if (current_city < this_json_storage.GetSizeProcessedCities() - 1) current_city++;
}

void ConsoleInterface::PreviousCity() {
    if (current_city > 0) current_city--;
}

ConsoleInterface::~ConsoleInterface() = default;


