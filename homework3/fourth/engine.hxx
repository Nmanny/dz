
#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace nn
{

struct KeyState
{
    bool pressed  = false;
    bool released = false;
};

class engine
{
public:
    ~engine();
};

struct game
{
    virtual ~game()             = default;
    virtual void initialize()   = 0;
    virtual void update()       = 0;
    virtual void render() const = 0;
};

} // namespace nn

extern "C" nn::game* create_game(nn::engine*);
