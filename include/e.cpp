#include <iostream>
#include <functional>
#include <typeinfo>
#include <vector>

struct BaseEvent {};

class A
{
public:
    typedef bool (A::*func_t)(BaseEvent*);
    //typedef bool (*func_t)(BaseEvent*);

    //template<typename ... Functions>
    A(std::initializer_list<func_t> f) :
        m_func({f})
    {}
    //A(std::initializer_list<func_t> f)
    //{
        //for (auto i : f) {
            //bind_f(i);
        //}
    //}

    virtual bool f(unsigned int i, BaseEvent* a) {
        if (i < m_func.size()) {
            auto f = m_func[i];
            if (f) {
                return (this->*f)(a);
            }
        }
        return false;
    }

    virtual bool f_a(BaseEvent* a) {
        std::cout << "f_a(): " << typeid(a).name() << std::endl;
        return a;
    }
    virtual bool f_b(BaseEvent* a) {
        std::cout << "f_b(): " << typeid(a).name() << std::endl;
        return a;
    }

public:
    void bind_f(const func_t f)
    {
        m_func.push_back(f);
    }


private:
    std::vector<A::func_t> m_func;
};

int main(void)
{
    auto a = A({&A::f_a, nullptr});
    a.bind_f(&A::f_b);
    BaseEvent e;
    a.f(0, &e);
    a.f(1, &e);
    return 0;
}
