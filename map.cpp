#include <map.h>

template<typename A, typename B>void Map<A,B>::set(A a, B b) {
    size_t ind = first.find(a);
    if (ind < first.length()) {second[ind] = b;}
    else {first.add(a);second.add(b);}
}
template<typename A, typename B>B* Map<A,B>::get(A a) {
    size_t ind = first.find(a);
    if (ind < first.length()) return second.begin()+ind;
    else return nullptr;
}