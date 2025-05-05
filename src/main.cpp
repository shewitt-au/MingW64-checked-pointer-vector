#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <windows.h>
#include "WriteWatchDLL.h"
using namespace std;

template <class T>
class checked_alloc
{
public:
    typedef T value_type;
    checked_alloc() noexcept {}
    ~checked_alloc() noexcept {}
    template<class U> checked_alloc(const checked_alloc<U>&) noexcept {}
    
    template<class U> bool operator==(const checked_alloc<U>&) const noexcept
    {
        return true;
    }

    T* allocate(const size_t n) const
    {
        return static_cast<T*>(AllocWatched(n*sizeof(T)));
        //return static_cast<T*>(::operator new(n*sizeof(T)));
    }

    void deallocate(T* const p, size_t n) const noexcept
    {
        FreeWatched(p);
        //::operator delete(p); //FreeWatched(p);
    }
};

int main()
{
    // -exec handle SIGSEGV nostop noprint pass

   vector<int, checked_alloc<int>> v = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    for (auto n : v)
        cout << n << endl;

    return 0;
}
