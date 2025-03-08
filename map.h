#pragma once

template <typename A, typename B> class Map {
    Array<A> first;
    Array<B> second;
    public:
        void set(A& a, B& b) ;
        bool del(A& a);
        B* get(A& a) ;
};

template<typename A, typename B>void Map<A,B>::set(A& a, B& b) {
    size_t ind = first.find(a);
    if (ind < first.length()) {second[ind] = b;}
    else {first.add(a);second.add(b);}
}
template<typename A, typename B>B* Map<A,B>::get(A& a) {
    size_t ind = first.find(a);
    if (ind < first.length()) return second.begin()+ind;
    else return nullptr;
}
template<typename A, typename B>bool Map<A,B>::del(A& a) {
    size_t ind = first.find(a);
    if (ind < first.length()) {
        first.remove(ind);
        second.remove(ind);
    }
}