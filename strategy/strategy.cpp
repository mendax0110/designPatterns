#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <memory>

class Strategy
{
public:
    virtual ~Strategy() {}
    virtual std::string DoAlgorithm(const std::vector<std::string> &data) const = 0;
};

class Context
{
private:
    std::unique_ptr<Strategy> strategy_;

public:
    explicit Context(std::unique_ptr<Strategy> strategy = nullptr) : strategy_(std::move(strategy))
    {
    }

    void set_strategy(std::unique_ptr<Strategy> &&strategy)
    {
        strategy_ = std::move(strategy);
    }

    void doSomeBusinessLogic() const
    {
        if (strategy_)
        {
            std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
            std::string result = strategy_->DoAlgorithm({"a", "e", "c", "b", "d"});
            std::cout << result << "\n";
        }
        else
        {
            std::cout << "Context: Strategy isn't set\n";
        }
    }
};

class ConcreteStrategyA : public Strategy
{
public:
    std::string DoAlgorithm(const std::vector<std::string> &data) const
    {
        std::string result;
        for (const std::string &letter : data)
        {
            result += letter;
        }
        std::sort(result.begin(), result.end());

        return result;
    }
};

class ConcreteStrategyB : public Strategy
{
public:
    std::string DoAlgorithm(const std::vector<std::string> &data) const
    {
        std::string result;
        for (const std::string &letter : data)
        {
            result += letter;
        }
        std::sort(result.begin(), result.end(), std::greater<char>());

        return result;
    }
};

void ClientCode()
{
    Context *context = new Context(std::unique_ptr<ConcreteStrategyA>(new ConcreteStrategyA()));
    std::cout << "Client: Strategy is set to normal sorting.\n";
    context->doSomeBusinessLogic();
    std::cout << "\n";
    std::cout << "Client: Strategy is set to reverse sorting.\n";
    context->set_strategy(std::unique_ptr<ConcreteStrategyB>(new ConcreteStrategyB()));
    context->doSomeBusinessLogic();
    delete context;
}

int main()
{
    ClientCode();
    return 0;
}
