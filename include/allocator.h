#pragma once
#include <iostream>


namespace HW3
{
template<typename T, std::size_t N = 0>
struct I_rob_this_allocator //sad but true :(
{
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    private:
    std::size_t  count = 0;
    void* head = nullptr;
    pointer p = nullptr;

    public:

    template<typename U>
    struct rebind
    {
        using other = I_rob_this_allocator<U,N>;
    };

    I_rob_this_allocator()
    {
        head = std::malloc(N * sizeof(T));
        if (!head)
            throw std::bad_alloc();
    }

    ~I_rob_this_allocator()
    {}

    template<typename U>
    I_rob_this_allocator(const I_rob_this_allocator<U>&)
    {}

    pointer allocate(std::size_t n)
    {
        if (count==0)
        {
            ++count;
            p = reinterpret_cast<pointer>(head);
            return p;
        }
        else if (count + n <= N)
        {
            ++count;
            p+=n;
            return p;
        }
        else
        {
            free(head);
            throw std::bad_alloc();
        }
    }

    void deallocate(pointer p, std::size_t n=0)
    {
        if(p && n>=0)--count;
        if(count==0)
        {
            free(head);
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {
        new(p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p)
    {
        p->~U();
    }
};
}
