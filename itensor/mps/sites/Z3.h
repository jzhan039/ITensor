//
// Distributed under the ITensor Library License, Version 1.2
//    (See accompanying LICENSE file.)
//
#ifndef __ITENSOR_Z3_H
#define __ITENSOR_Z3_H
#include "itensor/mps/siteset.h"

namespace itensor {

class Z3 : public SiteSet
    {
    public:

    Z3() { }

    Z3(int N);

    Cplx static
    Omega()
        {
        static Cplx w(cos(2.*Pi/3.),sin(2.*Pi/3.));
        return w;
        }

    private:

    virtual IQIndexVal
    getState(int i, String const& state) const;

    virtual IQTensor
    getOp(int i, String const& opname, Args const& args) const;

    void
    constructSites();
        
    };

inline Z3::
Z3(int N)
  : SiteSet(N)
    { 
    constructSites();
    }

void inline Z3::
constructSites()
    {
    for(int i = 1; i <= N(); ++i)
        {
        set(i,{nameint("Z3 site=",i),
        Index(nameint("0|site",i),1,Site),QN({0,3}),
        Index(nameint("1|site",i),1,Site),QN({1,3}),
        Index(nameint("2|site",i),1,Site),QN({2,3})});
        }
    }

inline IQIndexVal Z3::
getState(int i, String const& state) const
    {
    int st = -1;
    if(state == "0") { st = 1; }
    else
    if(state == "1") { st = 2; }
    else
    if(state == "2") { st = 3; }
    else
        {
        Error("State " + state + " not recognized");
        }
    return si(i)(st);
    }

inline IQTensor Z3::
getOp(int i, String const& opname, Args const& args) const
    {
    auto s = si(i);
    auto sP = prime(s);

    auto Zer = s(1);
    auto ZerP = sP(1);
    auto One = s(2);
    auto OneP = sP(2);
    auto Two = s(3);
    auto TwoP = sP(3);

    auto Op = IQTensor(dag(s),sP);

    if(opname == "N")
        {
        Op.set(One,OneP,1);
        Op.set(Two,TwoP,2);
        }
    else
    if(opname == "Sig")
        {
        Op.set(Zer,TwoP,1);
        Op.set(One,ZerP,1);
        Op.set(Two,OneP,1);
        }
    else
    if(opname == "SigDag")
        {
        Op.set(Two,ZerP,1);
        Op.set(Zer,OneP,1);
        Op.set(One,TwoP,1);
        }
    else
    if(opname == "Tau")
        {
        Op.set(Zer,ZerP,1);
        Op.set(One,OneP,cos(2.*Pi/3.));
        Op.set(Two,TwoP,cos(4.*Pi/3.));

        auto TauI = IQTensor(s,sP);
        TauI.set(One,OneP,sin(2.*Pi/3.));
        TauI.set(Two,TwoP,sin(4.*Pi/3.));

        Op += TauI*Cplx_i;
        }
    else
    if(opname == "TauDag")
        {
        Op.set(Zer,ZerP,1);
        Op.set(One,OneP,cos(2.*Pi/3.));
        Op.set(Two,TwoP,cos(4.*Pi/3.));

        auto TauI = IQTensor(s,sP);
        TauI.set(One,OneP,-sin(2.*Pi/3.));
        TauI.set(Two,TwoP,-sin(4.*Pi/3.));

        Op += TauI*Cplx_i;
        }
    else
    if(opname == "Proj0")
        {
        Op.set(Zer,ZerP,1);
        }
    else
    if(opname == "Proj1")
        {
        Op.set(One,OneP,1);
        }
    else
    if(opname == "Proj2")
        {
        Op.set(Two,TwoP,1);
        }
    else
        {
        Error("Operator " + opname + " name not recognized");
        }

    return Op;
    }

} //namespace itensor

#endif
