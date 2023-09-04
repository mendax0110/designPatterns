#include <iostream>
#include <string>
#include <thread>
#include <chrono>

class Singelton
{
protected:
    Singelton(const std::string value): value_(value)
    {

    }

    static Singelton* singelton_;
    std::string value_;

public:

    Singelton(Singelton &other) = delete;

    void operator=(const Singelton &) = delete;

    static Singelton *GetInstance(const std::string& value);
        
    void SomeBusinessLogic()
    {
        // ...
    }

    std::string value() const {
        return value_;
    }
};

Singelton* Singelton::singelton_ = nullptr;

Singelton *Singelton::GetInstance(const std::string& value)
{
    if(singelton_ == nullptr)
    {
        singelton_ = new Singelton(value);
    }
    return singelton_;
}

void ThreadFoo()
{
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singelton* singleton = Singelton::GetInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar()
{
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singelton* singleton = Singelton::GetInstance("BAR");
    std::cout << singleton->value() << "\n";
}

int main()
{
    std::cout << "If you see the same value, then singleton was reused (yay!\n" <<
        "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
        "RESULT:\n"; 
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();

    return 0;
}