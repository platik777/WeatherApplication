#include "../ConfigParseAndRequests/json_storage.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <utility>

using namespace ftxui;

class ConsoleInterface {
private:
    json_storage this_json_storage;
    int current_days_amount;
    int current_city;

public:

    explicit ConsoleInterface(const json_storage&  json);

    ConsoleInterface(const ConsoleInterface& other);

    ~ConsoleInterface();

    void CreateForecast();

    void IncreaseDays();

    void DecreaseDays();

    void NextCity();

    void PreviousCity();
};
