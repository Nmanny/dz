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
    engine();
    ~engine();
    void run();
};
} // namespace nn