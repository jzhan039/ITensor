//
// Distributed under the ITensor Library License, Version 1.2
//    (See accompanying LICENSE file.)
//
#ifndef __ITENSOR_ITDENSECPLX_H
#define __ITENSOR_ITDENSECPLX_H

#include "itdata.h"

namespace itensor {

//
// Optimization TODO: 
//  replace std::vector storage with
//  storage type only holding data ptr
//  and size, maybe use in simpletensor too
//

struct ITDenseCplx : RegisterData<ITDenseCplx>
    {
    using storage_type = std::vector<Real>;
    using size_type = storage_type::size_type;
    using iterator = storage_type::iterator;
    using const_iterator = storage_type::const_iterator;

    //
    // Data members
    //

    storage_type store;

    //
    // Constructors
    //

    ITDenseCplx() { }

    ITDenseCplx(size_t size) : store(2*size,0) { }

    ITDenseCplx(size_t size, Real val) 
        : 
        store(2*size,0) 
        { 
        std::fill(store.begin(),store.begin()+csize(),val);
        }
    ITDenseCplx(size_t size, const Complex& val) 
        : 
        store(2*size) 
        { 
        fill(val);
        }

    template<typename InputIterator>
    ITDenseCplx(InputIterator b, InputIterator e) : store(b,e) { }

    //
    // Accessors
    //

    Complex
    get(size_type i) const
        {
        return Complex(store[i],store[csize()+i]);
        }

    void
    set(size_type i, const Complex& z) 
        {
        store[i] = z.real();
        store[csize()+i] = z.imag();
        }

    ITDenseCplx&
    operator*=(const Complex& z)
        {
        auto* r = rstart();
        auto* re = istart(); //imag start is real end
        auto* i = istart();
        auto a = z.real(),
             b = z.imag();
        for(; r < re; ++r, ++i)
            {
            *r = *r*a-*i*b;
            *i = *i*a+*r*b;
            }
        return *this;
        }

    void
    fill(const Complex& z)
        {
        std::fill(store.begin(),store.begin()+csize(),z.real());
        std::fill(store.begin()+csize(),store.end(),z.imag());
        }

    size_type
    csize() const { return store.size()/2; }

    Real*
    rstart() { return store.data(); }
    const Real*
    rstart() const { return store.data(); }

    Real*
    istart() { return store.data()+csize(); }
    const Real*
    istart() const { return store.data()+csize(); }

    //
    // std container like methods
    //

    size_type
    size() const { return store.size(); }
    bool
    empty() const { return store.empty(); }

    Real*
    data() { return store.data(); }
    const Real*
    data() const { return store.data(); }
    
    const_iterator
    cbegin() const { return store.cbegin(); }
    const_iterator
    cend() const { return store.cend(); }
    const_iterator
    begin() const { return store.begin(); }
    const_iterator
    end() const { return store.end(); }
    iterator
    begin() { return store.begin(); }
    iterator
    end() { return store.end(); }

    };

}; //namespace itensor

#endif
