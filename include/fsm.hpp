#ifndef FSM_HPP
#define FSM_HPP

#include <string>
#include <vector>
#include <stdexcept>

namespace fsm {

class noncopyable
{
protected:
    constexpr noncopyable() = default;
    ~noncopyable() = default;
    noncopyable( const noncopyable& ) = delete;
    noncopyable& operator=( const noncopyable& ) = delete;
};

class error
{
public:
    class MissingVars : public std::exception
    {
    public:
        explicit MissingVars (const std::string& what_arg);
        explicit MissingVars (const char* what_arg);
    };
};

template <class FSM>
class Fsm : public noncopyable
{
protected:
    class State;
    class Transition;

    class State
    {
    public:
        State(const char* name, std::initializer_list<Transition> ts) :
            m_name(name),
            m_transitions({ts})
        {}
        virtual ~State() {}
        const std::string& getName() {
            return m_name;
        }
        virtual int execute(const char* transition,
                            const char* ev_data, const uint32_t ev_len) final {
            const auto s = std::string(transition);
            for (auto& t : m_transitions) {
                if (t.getName() == s) {
                    return t.exec(ev_data, ev_len);
                }
            }
            return -2;
        }
    private:
        const std::string m_name;
        std::vector<Transition> m_transitions;
    };

    class Transition
    {
    public:
        typedef int (FSM::*transitFunc)(const char*, const uint32_t);
        Transition(FSM *fsm, const char* name, State* nextState, const transitFunc func) :
            m_fsm(fsm),
            m_name(name),
            m_nextState(nextState),
            m_func(func)
        {}
        virtual ~Transition() {}

        int exec(const char* ev_data, const uint32_t ev_len) {
            if (!m_func) {
                return -1;
            }
            int ret = (m_fsm->*m_func)(ev_data, ev_len);
            if (ret == 0) {
                transit();
            }
            return ret;
        }

        const std::string& getName() {
            return m_name;
        }
    protected:
        void transit() {    // Convenience method
            m_fsm->Fsm<FSM>::transit(m_nextState);
        }

    private:
        FSM *m_fsm;
        const std::string m_name;
        State* m_nextState;
        const transitFunc m_func;
    };

    // transit the state to next.
    virtual void transit(State* nextState) {
        if (nextState) {
            m_state = nextState;
        }
    }

    virtual void destroy() {
        m_state = nullptr;
    }

private:
    State* m_state = nullptr;

public:
    const char* getState(void) {
        if (m_state) {
            return m_state->getName().c_str();
        }
        return "";
    }

    virtual int execute(const char* transition,
                         const char* ev_data, const uint32_t ev_len) final {
        if (!m_state) {
            throw std::domain_error(__PRETTY_FUNCTION__);
        }
        return m_state->execute(transition, ev_data, ev_len);
    }

};

};

#endif /* ifndef FSM_HPP */
