#include <vector>
#include <iostream>
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
    // -exec handle SIGSEGV nostop pass
    int ok;

    vector<int*, checked_alloc<int*>> v = {&ok, &ok, &ok};
    for (int i=0; i<1000; ++i)
        v.push_back(&ok);

    for (auto n : v)
        cout << n << endl;

    v.push_back((int*)0);

    return 0;
}
