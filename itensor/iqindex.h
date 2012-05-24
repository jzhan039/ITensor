//
// Distributed under the ITensor Library License, Version 1.0.
//    (See accompanying LICENSE file.)
//
#ifndef __IQINDEX_H
#define __IQINDEX_H
#include "index.h"
#include "itensor.h"
#include "qn.h"

/*
* Conventions regarding arrows:
*
* * Arrows point In or Out, never right/left/up/down.
*
* * The Site indices of a ket point Out.
*
* * Conjugation switches arrow directions.
*
* * All arrows flow Out from the ortho center of an MPS 
*   (assuming it's a ket - In if it's a bra).
*
* * IQMPOs are created with the same arrow structure as if they are 
*   orthogonalized to site 1, but this is just a default since they 
*   aren't actually ortho. If position is called on an IQMPO it follows 
*   the same convention as for an MPS except Site indices point In and 
*   Site' indices point Out.
*
* * Local site operators have two IQIndices, one unprimed and pointing In, 
*   the other primed and pointing Out.
*
*/

// Forward declarations
struct inqn;
class IQIndexDat;
struct IQIndexVal;

class ArrowError : public ITError
    {
public:
    typedef ITError
    Parent;

    ArrowError(const std::string& message) 
        : Parent(message)
        { }
    };


//
// IQIndex
//

class IQIndex
    {
    public:

    const std::vector<inqn>& 
    iq() const;

    int 
    nindex() const;

    const Index& 
    index(int i) const;

    const QN& 
    qn(int i) const;

    IndexType 
    type() const { return index_.type(); }

    std::string 
    name() const { return index_.name(); }

    const std::string&
    rawname() const { return index_.rawname(); }

    Real 
    uniqueReal() const { return index_.uniqueReal(); }

    int 
    primeLevel() const { return index_.primeLevel(); }
    void 
    primeLevel(int val) { index_.primeLevel(val); }

    bool
    isNull() const { return index_.isNull(); }
    bool
    isNotNull() const { return index_.isNotNull(); }

    //------------------------------------------
    //IQIndex: Constructors

    IQIndex();

    explicit 
    IQIndex(const Index& other, Arrow dir = Out);

    explicit 
    IQIndex(const std::string& name,
            IndexType it = Link, 
            Arrow dir = Out, 
            int plev = 0);

    IQIndex(const std::string& name, 
            const Index& i1, const QN& q1, 
            Arrow dir = Out);

    IQIndex(const std::string& name, 
            const Index& i1, const QN& q1, 
            const Index& i2, const QN& q2,
            Arrow dir = Out);

    IQIndex(const std::string& name, 
            const Index& i1, const QN& q1, 
            const Index& i2, const QN& q2,
            const Index& i3, const QN& q3,
            Arrow dir = Out);

    IQIndex(const std::string& name, 
            const Index& i1, const QN& q1, 
            const Index& i2, const QN& q2,
            const Index& i3, const QN& q3,
            const Index& i4, const QN& q4,
            Arrow dir = Out);

    IQIndex(const std::string& name, 
            const Index& i1, const QN& q1, 
            const Index& i2, const QN& q2,
            const Index& i3, const QN& q3,
            const Index& i4, const QN& q4,
            const Index& i5, const QN& q5,
            Arrow dir = Out);

    IQIndex(const std::string& name, 
            std::vector<inqn>& ind_qn, 
            Arrow dir = Out, int plev = 0);

    IQIndex(const IQIndex& other, 
            std::vector<inqn>& ind_qn);

    IQIndex(const Index& other, 
            const Index& i1, const QN& q1, 
            Arrow dir = Out);

    IQIndex(PrimeType pt, const IQIndex& other, int inc = 1);

    explicit 
    IQIndex(std::istream& s);

    void 
    write(std::ostream& s) const;

    void 
    read(std::istream& s);

    explicit
    IQIndex(Imaker im);

    static const IQIndex& 
    Null()
        {
        static const IQIndex Null_(makeNull);
        return Null_;
        }

    static const IQIndex& 
    IndReIm()
        {
        static const IQIndex IndReIm_(makeReIm);
        return IndReIm_;
        }

    static const IQIndex& 
    IndReImP()
        {
        static const IQIndex IndReImP_(makeReImP);
        return IndReImP_;
        }

    static const IQIndex& 
    IndReImPP()
        {
        static const IQIndex IndReImPP_(makeReImPP);
        return IndReImPP_;
        }

    //------------------------------------------
    //IQIndex: operators

    IQIndexVal 
    operator()(int n) const;

    operator Index() const { return index_; }

    bool 
    operator==(const IQIndex& other) const
        { return index_.operator==(other.index_); }

    bool 
    operator<(const IQIndex& other) const
        { return index_.operator<(other.index_); }

    bool 
    noprime_equals(const IQIndex& other) const
        { return index_.noprime_equals(other.index_); }

    //------------------------------------------
    //IQIndex: methods for querying m's

    int
    m() const { return index_.m(); }

    int 
    biggestm() const;

    std::string 
    showm() const;

    //------------------------------------------
    //IQIndex: quantum number methods

    void 
    negate();

    friend IQIndex 
    negate(IQIndex I); // Quantum numbers negated
     
    QN 
    qn(const Index& i) const;

    Arrow 
    dir() const;

    void 
    conj();

    //------------------------------------------
    //IQIndex: index container methods


    const Index& 
    findbyqn(QN q) const;

    bool 
    hasindex(const Index& i) const;

    bool 
    hasindex_noprime(const Index& i) const;

    int 
    offset(const Index& I) const;

    //------------------------------------------
    //IQIndex: prime methods

    void 
    doprime(PrimeType pt, int inc = 1);

    void 
    mapprime(int plevold, int plevnew, PrimeType pt = primeBoth);

    void 
    noprime(PrimeType pt = primeBoth);

    IQIndex friend inline
    noprime(const IQIndex& I)
        { 
        IQIndex J(I);
        J.noprime(); 
        return J; 
        }

    IQIndex 
    primed(int inc = 1) const;

    friend inline IQIndex
    primed(const IQIndex& I, int inc = 1)
        { return IQIndex(primeBoth,I,inc); }

    friend std::ostream& 
    operator<<(std::ostream &o, const IQIndex &I);

    void 
    print(std::string name = "") const;

    typedef std::vector<inqn>::iterator 
    iq_it;
    typedef std::vector<inqn>::const_iterator 
    const_iq_it;

    private:

    Index index_;

    Arrow _dir;

    boost::intrusive_ptr<IQIndexDat> pd;

    void 
    solo();


    }; //class IQIndex





//
// inqn
//

struct inqn
    {
    Index index;
    QN qn;
    inqn() { }
    inqn(const Index& i, QN q) 
        : index(i), 
          qn(q) 
        { }

    void 
    write(std::ostream& s) const { index.write(s); qn.write(s); }

    void 
    read(std::istream& s) { index.read(s); qn.read(s); }

    inline friend std::ostream& 
    operator<<(std::ostream &o, const inqn& x)
        { o << "inqn: " << x.index << " (" << x.qn << ")\n"; return o; }
    };



//
// IQIndexDat
//

class IQIndexDat
    {
    public:


    IQIndexDat();

    IQIndexDat(const Index& i1, const QN& q1);

    IQIndexDat(const Index& i1, const QN& q1,
               const Index& i2, const QN& q2);

    IQIndexDat(const Index& i1, const QN& q1,
               const Index& i2, const QN& q2,
               const Index& i3, const QN& q3);

    IQIndexDat(const Index& i1, const QN& q1,
               const Index& i2, const QN& q2,
               const Index& i3, const QN& q3,
               const Index& i4, const QN& q4);

    IQIndexDat(const Index& i1, const QN& q1,
               const Index& i2, const QN& q2,
               const Index& i3, const QN& q3,
               const Index& i4, const QN& q4,
               const Index& i5, const QN& q5);

    IQIndexDat(const Index& i1, const QN& q1,
               const Index& i2, const QN& q2,
               const Index& i3, const QN& q3,
               const Index& i4, const QN& q4,
               const Index& i5, const QN& q5,
               const Index& i6, const QN& q6);

    IQIndexDat(const Index& i1, const QN& q1,
               const Index& i2, const QN& q2,
               const Index& i3, const QN& q3,
               const Index& i4, const QN& q4,
               const Index& i5, const QN& q5,
               const Index& i6, const QN& q6,
               const Index& i7, const QN& q7);

    IQIndexDat(const Index& i1, const QN& q1,
               const Index& i2, const QN& q2,
               const Index& i3, const QN& q3,
               const Index& i4, const QN& q4,
               const Index& i5, const QN& q5,
               const Index& i6, const QN& q6,
               const Index& i7, const QN& q7,
               const Index& i8, const QN& q8);

    IQIndexDat(std::vector<inqn>& ind_qn);

    explicit 
    IQIndexDat(std::istream& s);

    void 
    write(std::ostream& s) const;

    void 
    read(std::istream& s);

    static IQIndexDat* Null()
        {
        static IQIndexDat Null_(makeNull);
        return &Null_;
        }

    static IQIndexDat* ReImDat()
        {
        static IQIndexDat ReImDat_(makeReIm);
        return &ReImDat_;
        }

    static IQIndexDat* ReImDatP()
        {
        static IQIndexDat ReImDatP_(makeReImP);
        return &ReImDatP_;
        }

    static IQIndexDat* ReImDatPP()
        {
        static IQIndexDat ReImDatPP_(makeReImPP);
        return &ReImDatPP_;
        }

    friend void 
    intrusive_ptr_add_ref(IQIndexDat* p);

    friend void 
    intrusive_ptr_release(IQIndexDat* p);

    int 
    count() const { return numref; }

    typedef std::vector<inqn>::iterator 
    iq_it;

    typedef std::vector<inqn>::const_iterator 
    const_iq_it;

    private:

    friend class IQIndex;

    explicit 
    IQIndexDat(Imaker im);

    //////////////////
    //
    // Data Members
    //

    std::vector<inqn> iq_;

    mutable int numref;

    const bool is_static_;

    //
    /////////////////

    explicit 
    IQIndexDat(const IQIndexDat& other);

    //Disallow copying using =
    void 
    operator=(const IQIndexDat&);

    };


enum IQmaker {makeSing};




//
// IQIndexVal
//

struct IQIndexVal
    {
    IQIndex iqind; 

    int i;

    IQIndexVal();

    IQIndexVal(const IQIndex& iqindex, int i_);

    Index index() const;

    QN qn() const;

    friend inline IQIndexVal
    primed(const IQIndexVal& IV, int inc = 1)
        {
        return IQIndexVal(primed(IV.iqind,inc),IV.i); 
        }

    void conj() 
        { iqind.conj(); }

    bool
    operator==(const IQIndexVal& other) const;

    operator IndexVal() const;

    IndexVal blockIndexVal() const;

    //operator ITensor() const;

    ITensor 
    operator*(const IndexVal& iv) const 
        { 
        return IndexVal(Index(iqind),i) * iv; 
        }

    void 
    print(std::string name = "") const
        { std::cerr << "\n" << name << " =\n" << *this << "\n"; }

    inline friend std::ostream& 
    operator<<(std::ostream& s, const IQIndexVal& iv)
        { return s << "IQIndexVal: i = " << iv.i << ", iqind = " << iv.iqind << "\n"; }

    static const IQIndexVal& Null()
        {
        static const IQIndexVal Null_(makeNull);
        return Null_;
        }

    private:

    void 
    calc_ind_ii(int& j, int& ii) const;

    explicit
    IQIndexVal(Imaker im);

    };


class DoPrimer // Functor which applies doprime within STL's for_each, etc
    {
    public:

    PrimeType pt; 

    int inc;

    DoPrimer (PrimeType _pt, int _inc = 1) 
        : pt(_pt), 
          inc(_inc) 
        { }

    void 
    operator()(inqn& iq) const { iq.index.doprime(pt,inc); }
    void 
    operator()(Index& i) const { i.doprime(pt,inc); }
    void 
    operator()(ITensor& it) const { it.doprime(pt,inc); }
    void 
    operator()(IQIndex &iqi) const { iqi.doprime(pt,inc); }
    };

class MapPrimer // Functor which applies mapprime within STL's for_each, etc
    {
    public:

    PrimeType pt;

    int plevold, plevnew;

    MapPrimer (int _plevold,int _plevnew,PrimeType _pt = primeBoth) 
		: pt(_pt), 
          plevold(_plevold), 
          plevnew(_plevnew) 
        {}

    void 
    operator()(inqn& iq) const { iq.index.mapprime(plevold,plevnew,pt); }
    void 
    operator()(Index& i) const { i.mapprime(plevold,plevnew,pt); }
    void 
    operator()(ITensor& it) const { it.mapprime(plevold,plevnew,pt); }
    void 
    operator()(IQIndex &iqi) const { iqi.mapprime(plevold,plevnew,pt); }
    };

class IndEq // Functor which checks if the index is equal to a specified value within STL's for_each, etc
    {
    public:

    Index i;

    IndEq(Index _i) 
        : i(_i) {}

    bool 
    operator()(const inqn &j) const { return i == j.index; }
    };


#endif
