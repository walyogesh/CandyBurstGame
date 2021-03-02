#pragma once
#include <memory>

template<typename T>
class Singleton
{
protected:
    Singleton() noexcept = default;

    Singleton(const Singleton&) = delete;

    Singleton& operator=(const Singleton&) = delete;

    virtual ~Singleton() = default;
public:
    static const std::unique_ptr<T>& GetInstance()
    {
        static const std::unique_ptr<T> instance= std::make_unique<T>();
        return instance;
    }
};
