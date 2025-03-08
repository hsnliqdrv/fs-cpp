#pragma once

#include <iostream>
#include <global.h>

#define DEF_ARRAY_SIZE 4
#define DEF_EXTEND_SIZE 8

size_t strlen(char* s);

template <typename T> class Array {
    private:
        size_t max_size = 0;
        size_t length_ = 0;
        T* data = nullptr;
        void changeMaxSize(size_t max_size, bool copy = true) {
            this->max_size=max_size;
            if (length_ > this->max_size) length_=this->max_size;
            T* _data = new T[this->max_size]();
            if (copy) {
                for (size_t i = 0; i < length_; i++) {
                    _data[i]=data[i];
                }
            }
            delete[] data;
            data = _data;
        };
        void extend() {changeMaxSize(max_size>0?(max_size+DEF_EXTEND_SIZE):(DEF_ARRAY_SIZE));}
        void shrink() {changeMaxSize(length_);}
    public:
        bool des = false;
        bool nullArray() const ;
        bool isEmpty() const ;
        Array(T* default_value, size_t c) ;
        Array(size_t c = 0);
        Array(bool b) ;
        void emptyArray() ;
        size_t length() const ;
        size_t add(T& value) ;
        size_t find (T& value) const ;
        void split(T& delim, Array<Array<T>>& res) const ;
        template<typename F> size_t find(const F& func) const ;
        size_t remove(T& value) ;
        size_t remove(size_t ind);
        size_t concat(Array<T>& second);
        bool equals(const T* data, size_t len);
        T* begin() const;
        T* end() const;
        T& operator[](size_t index) const;
        bool operator ==(Array<T>& second) const ;
        operator bool() const ;
        bool operator !() const ;
        bool operator !=(Array<T>& second) const ;
        Array<T>& operator=(Array<T>& second) ;
        ~Array() ;
};

template <typename T> bool Array<T>::nullArray() const {return (data == nullptr);}
        template <typename T> bool Array<T>::isEmpty() const {return (!nullArray() && length_ == 0);}
        template <typename T> Array<T>::Array(T* default_value, size_t c) {
            if (default_value) {
                max_size=c;
                length_=c;
                data = default_value;
            }
        }
        template <typename T> Array<T>::Array(size_t c) {
            data=new T[c]();
            max_size = c;
            length_ = 0;
        };
        template <typename T> Array<T>::Array(bool b) {
            if (b) {
                max_size = DEF_ARRAY_SIZE;
                length_ = 0;
                data = new T[max_size]();
            }
        };
        template <typename T> void Array<T>::emptyArray() {
            for (size_t i = 0; i < length_; i++) {
                data[i].~T();
            }
            length_=0;
        }

        template <typename T> size_t Array<T>::length() const {return this->length_;}
        template <typename T> size_t Array<T>::add(T& value) {
            while (length_ >= max_size) extend();
            data[length_] = value;
            length_++;
            return length_;
        }
        template <typename T> void Array<T>::split(T& delim, Array<Array<T>>& res) const {
            Array<T> s;
            for (size_t i = 0; i < length_; i++) {
                if (delim == (*this)[i]) {
                    res.add(s);
                    s.emptyArray();
                } else {
                    s.add((*this)[i]);
                }
            }
            res.add(s);
        }
        template <typename T> size_t Array<T>::find (T& value) const {
            return find([&value](T& elem) {return elem == value;});
        }
        template <typename T> template<typename F> size_t Array<T>::find(const F& func) const  {
            for (size_t i = 0; i < length_; i++) {
                if (func(data[i])) {
                    return i;
                }
            }
            return length_;
        }
        template <typename T> size_t Array<T>::remove(T& value) {
            size_t i = find(value);
            this->remove(i);
        }
        template <typename T> size_t Array<T>::remove(size_t i) {
            if (i >= length_) return length_;
            for (size_t j = i; j < length_-1; j++) {
                data[j]=data[j+1];
            }
            length_--;
            if (max_size > DEF_ARRAY_SIZE && max_size > 2*length_) shrink();
            return length_;
        }
        template <typename T> bool Array<T>::equals(const T* data, size_t len) {
            if (len != length_) return false;
            for (size_t i = 0; i < len; i++) {
                if (data[i] != this->data[i]) return false;
            }
            return true;
        }
        template <typename T> size_t Array<T>::concat(Array<T>& second) {
            for (size_t i = 0 ; i < second.length(); i++) {
                this->add(second[i]);
            }
        }
        template <typename T>  T* Array<T>::begin() const {return data;}
        template <typename T>  T* Array<T>::end() const {return data+length_;}
        template <typename T> T& Array<T>::operator[](size_t index) const {return data[index];}
        template <typename T> bool Array<T>::operator ==(Array<T>& second) const {
            if (length_ == second.length_) {
                for (size_t i = 0; i < length_; i++) {
                    if (data[i] != second.data[i]) {
                        return false;
                    }
                }
                return true;
            } else return false;
        }
        template <typename T> Array<T>::operator bool() const {return data != nullptr;}
        template <typename T> bool Array<T>::operator !() const {return data == nullptr;}
        template <typename T> bool Array<T>::operator !=(Array<T>& second) const {return !(*this == second);}
        template <typename T> Array<T>& Array<T>::operator =(Array<T>& second) {
            if (*this == second) return *this;
            this->changeMaxSize(second.length(),false);
            length_=second.length();
            for (size_t i = 0; i < length_; i++) {
                (this->data)[i] = second[i];
            }
            return *this;
        }

        template <typename T> Array<T>::~Array() {
            if (max_size > 0) delete[] data;
            this->des = true;
            data=nullptr;
        }

        template<typename T,typename U> U& operator<<(U& u, Array<T>& arr) {
            const char* delim = sizeof(T) == 1 ? "" : " ";
            for (T* i = arr.begin(); i < arr.end(); i++) {
                u << *i << (i<(arr.end()-1)?delim:"");
            }
            return u;
        };
        
        template<typename U> U& operator>>(U& u, Array<char>& s) {
            char c;
            while (1) {
                u.get(c);
                if (c == '\n') break;
                else s.add(c);
            }
            return u;
        }

