#include "fsm.hpp"
#include <iostream>
#include <memory>
#include <cstdio>

class UpDown : public fsm::Fsm<UpDown>
{
protected:
    virtual int goUp(const char* ev_data, const uint32_t ev_len) {
        std::cout << "going up..." << std::endl;
        std::cout << ev_data << std::endl;
        return 0;
    };

    virtual int goDown(const char* ev_data, const uint32_t ev_len) {
        std::cout << "going down..." << std::endl;
        std::cout << ev_data << std::endl;
        return 0;
    };

    State m_stateUp = State("up", {
            Transition(this, "goUp", &m_stateDown, &UpDown::goUp)
        });
    State m_stateDown = State("down", {});

public:
    UpDown()
    {
        transit(&m_stateUp);
    }

    ~UpDown()
    {
    }
};

int main(void)
{
    UpDown a;
    std::cout << "current state: " << a.getState() << std::endl;
    int ret = -1;
    std::cout << "ret: " << ret << std::endl;
    ret = a.execute("goUp", "dfagag", 7);
    std::cout << "ret: " << ret << std::endl;
    ret = a.execute("go", "dfagag", 7);
    std::cout << "ret: " << ret << std::endl;
    //std::cout << "current state: " << a.getState()->getName() << std::endl;
    return 0;
}
