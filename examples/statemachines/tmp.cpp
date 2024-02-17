#include "msfsm.hpp"
#include <iostream>

using namespace msfsm;
using namespace std;

// Events
class Up {};
class Down {};

// stateMachine
class UpDown : public Fsm<UpDown> {

public:
    //friend Fsm;

    class State : public Fsm::State {
        friend Fsm;
        using Fsm::State::State;
        virtual void event(Up)   { cout << "Ignoring Up event" << endl; }
        virtual void event(Down) { cout << "Ignoring Down event" << endl; }
    };

    // States = pointers to incomplete class definitions
    class Upper : public State {
        friend Fsm;
        using State::State;
        void entry() {
            cout << "Entering upper" << endl;
        }
        void event(Down) override {
            transition(*fsm.lower);
        }
    };

    class Lower : public UpDown::State {
        friend Fsm;
        using State::State;
        void entry() {
            cout << "Entering lower" << endl;
        }
        void event(Up) override {
            transition(*fsm.upper);
        }
        void exit() override {
            cout << "Exiting lower" << endl;
        }
    };

protected:
    Upper *upper;
    Lower *lower;

public:
    UpDown() :
        upper(new UpDown::Upper(this)),
        lower(new UpDown::Lower(this))
    {
        transition(*lower);
    }

    ~UpDown()
    {
        delete(lower);
        delete(upper);
    };
};

/*
 *class UpDown::State : public Fsm::State {
 *    friend Fsm;
 *    using Fsm::State::State;
 *    virtual void event(Up)   { cout << "Ignoring Up event" << endl; }
 *    virtual void event(Down) { cout << "Ignoring Down event" << endl; }
 *};
 *
 *class UpDown::Upper : public UpDown::State {
 *    friend Fsm;
 *    using State::State;
 *    void entry() {
 *        cout << "Entering upper" << endl;
 *    }
 *    void event(Down) override {
 *        transition(*fsm.lower);
 *    }
 *};
 */

/*
 *class UpDown::Lower : public UpDown::State {
 *    friend Fsm;
 *    using State::State;
 *    void entry() {
 *        cout << "Entering lower" << endl;
 *    }
 *    void event(Up) override {
 *        transition(*fsm.upper);
 *    }
 *    void exit() override {
 *        cout << "Exiting lower" << endl;
 *    }
 *};
 */


//UpDown::UpDown()
    //: upper(new Upper(this))
    //, lower(new Lower(this))
//{
    //transition(*lower);
//}

//UpDown::~UpDown()
//{
    //delete(lower);
    //delete(upper);
//}

int main(int argc, char *argv[])
{
    UpDown f;
    f.handle(Up());
    f.handle(Up());
    f.handle(Down());
    f.handle(Down());
    return 0;
}
