#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

#include "engine.hxx"

class nngame : public nn::game
{
public:
    nngame(nn::engine&)
        : progress{ 0 }
        , progress_bar_width{ 33 }
        , symbols{ { '*' } }
        , symbol_index{ 0 }
        , loading_displayed{ false }
    {
    }

    void initialize() override {}

    void update() override
    {
        using namespace std::chrono;
        std::this_thread::sleep_for(milliseconds(400));

        ++progress;
        if (progress == progress_bar_width)
        {
            progress = 0;
        }
    }

    void render() const override
    {
        if (!loading_displayed)
        {
            std::cout << '\r' << "Loading [] 0%" << std::flush;
            loading_displayed = true;
            return;
        }

        const char current_symbol = symbols.at(symbol_index);
        std::cout << '\r' << "Loading [";

        const float percent_complete =
            static_cast<float>(progress) / (progress_bar_width);

        for (int i = 0; i < progress_bar_width; ++i)
        {
            if (static_cast<float>(i) / progress_bar_width <= percent_complete)
            {
                std::cout << current_symbol;
            }
            else
            {
                std::cout << '-';
            }
        }

        std::cout << "] " << std::fixed << std::setprecision(0)
                  << (percent_complete * 100) << "%" << std::flush;

        if (progress == progress_bar_width)
        {
            std::cout << '\r';
        }
    }

private:
    int                 progress;
    int                 progress_bar_width;
    std::array<char, 1> symbols;
    uint32_t            symbol_index;
    mutable bool        loading_displayed;
};

nn::game* create_game(nn::engine* engine)
{
    if (engine != nullptr)
    {
        return new nngame(*engine);
    }
    return nullptr;
}
