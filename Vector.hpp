#pragma once

#include <memory>
#include <iostream>
#include <algorithm>

using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;
using std::allocator_traits;
using std::make_move_iterator;
using std::initializer_list;
using std::move;
using std::lexicographical_compare;
using std::max;

//iteratoriu konvertavimui
template<typename InputIt>
using RequireInputIt = typename std::enable_if<std::is_convertible<typename std::iterator_traits<InputIt>::iterator_category, std::input_iterator_tag>::value>::type;

template <class T> 
class Vector {
 public:
    
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type; 
    typedef T value_type; 
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef T &reference;
    typedef const T &const_reference;
    
    using allocator_type = allocator<T>;
    using pointer = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;

    //konstruktoriai
    Vector() { create(); }
    explicit Vector(size_type n, const T& val = T{}) { create(n, val); }
    Vector(const initializer_list<T> &init_list) { create(init_list.begin(), init_list.end()); }

    //destruktorius
    ~Vector() { uncreate(); }

    //dydis
    size_type size() const { return avail - data; } //size()

    //elementu grazinimas per indeksa
    reference operator[](size_type i) { return data[i]; } 
    const_reference operator[](size_type i) const { return data[i]; }

    reference at(size_type i) //at()
    {
        if (i < 0 || i >= size()) throw std::out_of_range("Index(Vector::at) out of range!");
        return data[i];
    }

    const_reference at(size_type i) const //at(), const
    {
        if (i < 0 || i >= size()) throw std::out_of_range("Index(Vector::at) out of range!");
        return data[i];
    }

    //pirmo elemento gavimas
    reference front() { return data[0]; }
    const_reference front() const { return data[0]; }

    //paskutinio elemento gavimas
    reference back() { return data[size()-1]; }
    const_reference back() const { return data[size()-1]; }

    //data() implementacija
    T* get_data() noexcept { return data; }
    const T* get_data() const noexcept { return data; }

    //iteratoriai
    iterator begin() noexcept { return data; }                                                      //begin()
    const_iterator begin() const noexcept { return data; }                                          //begin(), const            
    const_iterator cbegin() const noexcept { return begin(); }                                      //cbegin()                
    iterator end() noexcept { return avail; }                                                       //end()
    const_iterator end() const noexcept { return avail; }                                           //end(), const           
    const_iterator cend() const noexcept { return end(); }                                          //cend()            
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }                          //rbegin()                            
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(begin()); }      //rbegin(), const                                                
    const_reverse_iterator crbegin() const noexcept { return rbegin(); }                            //crbegin()
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }                          //rend()       
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }        //rend(), const                          
    const_reverse_iterator crend() const noexcept { return rend(); }                                //crend()  
    //iteratoriai

    //capacity
    bool empty() { return data == avail; }                                                          //empty()
    //size_type size() const { return limit - data; }                                               //size(), jau yra auksciau
    size_type max_size() const { return alloc.max_size(); }                                         //max_size()      
    void reserve(size_type n) { if(n>capacity()) grow(n); }                                         //reserve()             
    size_type capacity() const { return limit - data; }                                             //capacity()         
    void shrink_to_fit() { if(limit>avail) limit = avail; }                                         //shrink_to_fit()    
    //capacity

    //modifier'iai
    void clear()                                                                                    //clear()                                
    {
        iterator i = avail;
        while(i!=data)
        {
            alloc.destroy(--i);
        }
        avail = data;
    }         

    iterator insert(iterator i, size_type n, const T& val)                                          //insert()       
    {
        if (i < begin() || i >= end()) throw std::out_of_range("Index(Vector::insert) out of range!");
        if (size() + n >= capacity())
        {
            size_type pradinis = i - begin();
            grow(capacity() + n);
            i = pradinis + begin();
        }
        for(iterator j = avail - 1; j >= i; j--) alloc.construct(j + n, *j); //pastumiam elementus

        uninitialized_fill(i, i+n, val); //uzpildom reiksmem
        avail = avail + n; //pakeiciam 'avail' iteratoriu
        return i;
    }
    iterator insert(iterator i, const T& val) { return insert(i, 1, val); } //vienam elementui

    template<class InputIt, class = RequireInputIt<InputIt>>
    iterator insert(iterator i, InputIt pradzia, InputIt pabaiga)
    {
        if (i < begin() || i >= end()) throw std::out_of_range("Index(Vector::insert) out of range!");
        size_type n = pabaiga - pradzia;

        if (size() + n >= capacity())
        {
            size_type pradinis = i - begin();
            grow(capacity() + n);
            i = pradinis + begin();
        }
        for(iterator j = avail - 1; j >= i; j--) alloc.construct(j + n, *j); //pastumiam elementus

        uninitialized_copy(i, i+n, i); //uzpildom reiksmem
        avail = avail + n; //pakeiciam 'avail' iteratoriu
        return i;
    }
    iterator insert (iterator i, initializer_list<T> init_list)
    {
        return insert(i, init_list.begin(), init_list.end());
    }

    template< class... Args >
    iterator emplace(iterator i, Args&&... args)                                                               //emplace()
    {
        if (i < begin() || i >= end()) throw std::out_of_range("Index(Vector::emplace) out of range!");
        if (size() + 1 >= capacity())
        {
            size_type pradinis = i - begin();
            grow(capacity() + 1);
            i = pradinis + begin();
        }
        for(iterator j = avail - 1; j >= i; j--) alloc.construct(j + 1, *j); //pastumiam elementus

        alloc.construct(i, std::forward<Args>(args)...); //uzpildom reiksmem
        avail = avail + 1; //pakeiciam 'avail' iteratoriu
        return i;
    }

    iterator erase(iterator i)                                                                                 //erase()
    {
        if (i < begin() || i > end()) throw std::out_of_range("Index(Vector::erase) out of range!");
        if (i == end()) return end();
        alloc.destroy(i);
        avail = uninitialized_copy(i+1, end(), i);
        return i;
    }
    iterator erase(iterator pradzia, iterator pabaiga)
    {
        if (pradzia < begin() || pabaiga > end()) throw std::out_of_range("Index(Vector::erase) out of range!");
        iterator i = pabaiga;
        while(i!=pradzia) alloc.destroy(--i);
        avail = uninitialized_copy(pabaiga+1, end(), pradzia);
        return pabaiga;
    }

    void push_back(const T& val)                                                                               //push_back()
    {
        if (avail == limit) grow(); //vietos isskyrimas
        unchecked_append(val); //elemento idejimas
    }

    void push_back(const T&& val) 
    {
        if (avail == limit) grow();
        unchecked_append(move(val));
    }

    template< class... Args >
    void emplace_back(Args&&... args)                                                                          //emplace_back()
    {
        alloc.construct(avail++, std::forward<Args>(args)...);
    }

    void pop_back()                                                                                            //pop_back()
    {
        alloc.destroy(--avail);
    }

    void resize(size_type n, const value_type &val = 0)
    {
        if(size() > n) erase(begin()+n, end());
        if(size() < n)
        {
            size_type pradinis = end() - begin();
            if(capacity() < n) grow(n);
            avail = data + n; 
            uninitialized_fill(begin() + pradinis, avail, val);
        }
    }

    void swap(Vector &v)
    {
        std::swap(data, v.data);
        std::swap(avail, v.avail);
        std::swap(limit, v.limit);
    }
    void swap(Vector<T> &v1, Vector<T> &v2)
    {
        std::swap(v1,v2);
    }
    //modifier'iai

    //non-member function'ai
    bool operator==(Vector<T> &v) { return (size() == v.size()) && (std::equal(begin(), end(), v.begin())); }
    bool operator!=(Vector<T> &v) { return !(*this == v); }
    bool operator<(Vector<T> &v) { return lexicographical_compare(begin(), end(), v.begin(), v.end()); }
    bool operator<=(Vector<T> &v) { return !(v < *this); }
    bool operator>(Vector<T> &v) { return lexicographical_compare(v.begin(), v.end(), begin(), end()); }
    bool operator>=(Vector<T> &v) { return !(*this < v); }
    //non-member function'ai

    //priskyrimo operatorius
    Vector& operator=(const Vector&);

    //copy konstruktorius
    Vector(const Vector& v) { create(v.begin(), v.end()); }

    //move konstruktorius
    Vector(const Vector&& v)
    {
        data = alloc.allocate(v.end()-v.begin());
        limit = avail = uninitialized_copy(make_move_iterator(v.begin()), make_move_iterator(v.end()), data);
        v.uncreate();
    }

    //konstruktorius, kuriantis vektoriu is gautu iteratoriu
    template<class InputIt, class = RequireInputIt<InputIt>>
    Vector(InputIt pradzia, InputIt pabaiga) 
    {
        create(pradzia, pabaiga);
    }

    //assign() uzpildymas su val (n elementu)
    void assign(size_type n, const T& val)
    {
        uncreate();
        create(n, val);
    }

    //assign() uzpildymas is iteratoriu
    template<class InputIt, class = RequireInputIt<InputIt>>
    void assign(InputIt i, InputIt j)
    {
        uncreate();
        create(i,j);
    }

    //assign() per initializatoriu
    void assign(initializer_list<T> init_list)
    {
        uncreate();
        create(init_list.begin(), init_list.end());
    }

    //allocatoriaus grazinimas
    allocator_type get_allocator() const { return alloc; }

 private:

    iterator data; //pirmas elementas
    iterator avail; //pirmas po paskutinio inicializuoto elemento
    iterator limit; //pirmas po paskutinio

    //atminties isskyrimui
    allocator<T> alloc;

    void create() { data = avail = limit = nullptr; }
    void create(size_type n, const T& val)
    {
        data = alloc.allocate(n); //rodo i pirma allocatinta elementa
        limit = avail = data + n; //rodo i pirma + n elementa (po paskutinio)
        uninitialized_fill(data, limit, val); //uzpildo val reiksme
    }
    void create(const_iterator i, const_iterator j)
    {
        data = alloc.allocate(j-i); //isskiriam vietos intervalui
        limit = avail = uninitialized_copy(i, j, data);
    }

    void uncreate()
    {
        if(data)
        {
            //naikinam esancius elementus
            iterator it = avail;
            while (it!=data) alloc.destroy(--it);

            //atlaisvinam isskirta atminti
            alloc.deallocate(data, limit-data);
        }
        //resetinam pointerius, kai vektorius tuscias
        data = limit = avail = nullptr;
    }

    //didinimui vietos
    void grow(size_type n = ptrdiff_t(1)) 
    {
        size_type new_size;
        
        if (n != ptrdiff_t(1)) new_size = n;
        else new_size = max(2 * capacity(), n); //padarom dvigubai daugiau vietos

        //isskiriam vietos ir perkopijuojam
        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = uninitialized_copy(data, avail, new_data);

        //atlaisvinam sena vieta
        uncreate();

        //pakeiciam rodykles
        data = new_data;
        avail = new_avail;
        limit = data + new_size;
    }

    void unchecked_append(const T& val) { alloc.construct(avail++, val); }

};

//priskyrimo operatorius
template <class T>
Vector<T>& Vector<T>::operator=(const Vector& v)
{
    //jei lygu, tai nieko nereikia daryt
    if (&v != this)
    {
        uncreate(); //naikinam sena
        create(v.begin(), v.end());
    }
    return *this;
}