#ifndef ZCCHEN_SIMPLE_FSM_HPP
#define ZCCHEN_SIMPLE_FSM_HPP

#include <memory>
#include <map>
#include <queue>
#include <vector>
#include <functional>
#include <stdexcept>
#include <typeinfo>
#include <string>

namespace zcchen {
namespace fsm {

// Error class
class error {
public:
    class empty_size : public std::logic_error {
    public:
        explicit empty_size(const char* what_arg);
    };
    class unmatched_state : public std::logic_error {
    public:
        explicit unmatched_state(const char* what_arg);
    };
};


// Base class
struct BaseEvent
{
public:
    virtual const char* getType(void) const {
        return "BaseEvent";
    }
};

class BaseTransition
{
public:
    BaseTransition(const char* name, const char* fromState, const char* toState) :
        m_name(name),
        m_fromState(fromState),
        m_toState(toState)
    {}
    virtual ~BaseTransition() {}
    const std::string& getName() const { return m_name; }
    const std::string& getFromState() const { return m_fromState; }
    const std::string& getToState() const { return m_toState; }
    virtual const std::string& getEventType() const = 0;
    virtual bool exec(const BaseEvent& ev) const = 0;
private:
    const std::string m_name;
    const std::string m_fromState;
    const std::string m_toState;
    const std::string m_emptyEventType = "";
};

class BaseStateMachine
{
};

/**
 * @brief inherited 'Event<EventName>' to define the event info.
 * example; struct AbcEvent : Event<AbcEvent> { // ... data info ... // };
 */
template <typename DerivedEvent>
struct Event : public BaseEvent
{
protected:
    Event() {};     // Hide the constructor so that it can be used only at inherited struct class.
public:
    virtual const char* getType(void) const final {
        return typeid(DerivedEvent).name();
    }
    static const char* getType_s(void) {
        return typeid(DerivedEvent).name();
    }
};


// Transition relates
template <typename Event>
class Transition : public BaseTransition
{
public:
    Transition(const char* name, const char* fromState, const char* toState,
               std::function<bool(const Event&)> func):
        BaseTransition(name, fromState, toState),
        m_func(func),
        m_eventType(Event::getType_s())
    {}
    virtual ~Transition() {}
    virtual bool exec(const BaseEvent& ev) const final
    {
        return m_func((Event&)ev);
    }
    virtual const std::string& getEventType() const final
    {
        return m_eventType;
    }

private:
    const std::function<bool(const Event&)> m_func;
    const std::string m_eventType;
};


class TransitionTable final
{
public:
    typedef std::shared_ptr<BaseTransition> Transition_t;

    template<typename StateMachineT, class ... transitions>
    TransitionTable(StateMachineT* sm, transitions* ... t) :
        m_stateMachine(sm),
        m_transitions({Transition_t(t) ...})
    {}

    virtual ~TransitionTable();

    size_t size(void);

    const std::vector<std::string> namelist(void);

    const std::vector<Transition_t*> find(const std::string& name="", const std::string& fromState="");

private:
    const std::shared_ptr<BaseStateMachine> m_stateMachine;
    const std::vector<Transition_t> m_transitions;
};


// State Machine
class StateMachine : public BaseStateMachine
{
public:
    typedef std::pair<const std::string, std::shared_ptr<StateMachine>> State_t;
    typedef std::map<const std::string, std::shared_ptr<StateMachine>> StateList_t;

    StateMachine(const char* firstState = ".");
    virtual ~StateMachine();
    virtual void assert(void) final;    // this assert will be called at factory creator.

    /**
     * @brief listStates() is to list ALL available states
     * @return const std::vector with their states' names.
     */
    virtual const std::vector<std::string> listStates(void) final;

    /**
     * @brief listTransitions() is to list ALL available transitions
     * @return const std::vector with their transitions' names.
     */
    //virtual const std::vector<const std::string&> listTransitions(void) final;

    /**
     * @brief get_state() is to get the current state
     * @return the current state
     */
    virtual const std::string& get_currentState() final;

    /*
     * @brief transit(event) is to transit the state with event.
     * @param event: the transit event reference, which is self defined.
     */
    virtual bool transit(const BaseEvent& event) final;

    /*
     * @brief transit() is to transit the state with event queue.
     */
    virtual bool transit() final;

    /*
     * @brief trigger(event) is to transit the state with event queue.
     */
    virtual bool trigger(const BaseEvent& event) final;

protected:
    //virtual const std::shared_ptr<StateList_t> get_states(void) = 0;
    virtual const std::shared_ptr<StateList_t> get_states(void) = 0;
    virtual const std::shared_ptr<TransitionTable> get_transitions(void) = 0;

    //template<typename Class, typename Param>
    //inline std::function<bool(const Param&)> func_bind(bool (Class::*f)(const Param&)) {
        //return std::bind(Class::f, this, std::placeholders::_1);
    //}

    /*
     * @brief trigger(event) is to transit the state with event queue.
     */
    virtual void cleanEvents(void) final;

private:
    std::string m_current;
    std::string m_firstState;
    std::queue<const BaseEvent*> m_events;
};

};
};

#endif /* ifndef ZCCHEN_SIMPLE_FSM_HPP */
