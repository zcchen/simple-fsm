#ifndef ZCCHEN_FSM_HPP
#define ZCCHEN_FSM_HPP

#include <vector>
#include <map>
#include <type_traits>

namespace zcchen {
namespace fsm {

// --- The base class ---
struct BaseEvent {};
struct BaseState {};
struct BaseTransit {};
// ----------------------

// --- The template class ---
struct State : public BaseState
{
};

struct Event : public BaseEvent
{
};

template<typename states, typename from, typename to, typename event
    std::
>
struct Transit : public BaseTransit
{
};
// ----------------------

template<typename ... States>
class StateList
{
private:
    const std::vector<BaseState> states = {
        States() ...
    };
};

template<typename ... Transits>
class TransitList
{
private:
    const std::vector<BaseTransit> transits = {
        Transits() ...
    };
};

template<typename name>
class StateMachine
{
protected:
    StateList<> states;
    TransitList<> transits;

public:
};

};
};
#endif /* ifndef ZCCHEN_FSM_HPP */
