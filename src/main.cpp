#include <vector>
#include <iostream>
using namespace std;

template <class T>
class checked_alloc
{
public:
    typedef T value_type;
    checked_alloc() noexcept {}

    template<class U> checked_alloc(const checked_alloc<U>&) noexcept {}
    template<class U> bool operator==(const checked_alloc<U>&) const noexcept
    {
        return true;
    }
    template<class U> bool operator!=(const checked_alloc<U>&) const noexcept
    {
        return false;
    }
    T* allocate(const size_t n) const
    {
        return static_cast<T*>(::operator new(n*sizeof(T)));
    }
    void deallocate(T* const p, size_t) const noexcept
    {
        ::operator delete(p);
    }
};

int main()
{
    cout << "Made it" << endl;

    vector<int, checked_alloc<int>> v;
    v.push_back(3);

    return 0;
}
