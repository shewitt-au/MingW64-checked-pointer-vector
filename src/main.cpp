#include <vector>
#include <iostream>
using namespace std;

template <class T>
struct Mallocator
{
    typedef T value_type;
    Mallocator() noexcept {}

    template<class U> Mallocator(const Mallocator<U>&) noexcept {}
    template<class U> bool operator==(const Mallocator<U>&) const noexcept
    {
        return true;
    }
    template<class U> bool operator!=(const Mallocator<U>&) const noexcept
    {
        return false;
    }
    T* allocate(const size_t n) const
    {
        return new T();
    }
    void deallocate(T* const p, size_t) const noexcept
    {
        delete p;
    }
};

int main()
{
 //   *(int*)0 = 0;

    cout << "Made it" << endl;

    vector<int, Mallocator<int>> v;
    v.push_back(3);

    return 0;
}
