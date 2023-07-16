#include "regularG.h"
#include "quaternion.h"

namespace qtrn {

    using GiNaC::lst, GiNaC::ex, GiNaC::symbol;

// RegularG returnsthe value of the Fueter-regular G(a,b,c) at a given quaternion q. 
template <class T>
quaternion<T> RegularG(int a, int b, int c, quaternion<T> q) {
    GiNaC::symbol t("t"), x("x"), y("y"), z("z");
    quaternion<ex> SRG = SymbolicRegularG(a,b,c,t,x,y,z);
    return quaternion<T>(SRG.t.subs(lst{t,x,y,z},lst{q.t,q.x,q.y,q.z}),
                        SRG.x.subs(lst{t,x,y,z},lst{q.t,q.x,q.y,q.z}),
                        SRG.y.subs(lst{t,x,y,z},lst{q.t,q.x,q.y,q.z}),
                        SRG.z.subs(lst{t,x,y,z},lst{q.t,q.x,q.y,q.z}));
}

}