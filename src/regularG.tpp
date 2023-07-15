#include "regularG.h"
#include "quaternion.h"

/* The code here implements the Fueter-regular "G functions", which are the partial 
   derivatives of q^{-1}/Nm(q) with respect to the the x,y,z variables in q = t + ix + jy + kz.

   It's in a separate file because it relies on the GiNAC library to symbolically compute the partial derivatives.
*/
namespace qtrn {

    using GiNaC::lst, GiNaC::ex;

// The following is a naive implementation of symbolic G(a,b,c). For computations involving many such functions, 
// they should be computed all together.

quaternion<ex> SymbolicRegularG(int a, int b, int c) {
    GiNaC::symbol t("t"), x("x"), y("y"), z("z");
    quaternion<ex> q(t,x,y,z), G = q.inv()/q.norm();

    ex Gt = G.t.diff(x,a).diff(y,b).diff(z,c);
    ex Gx = G.x.diff(x,a).diff(y,b).diff(z,c);
    ex Gy = G.y.diff(x,a).diff(y,b).diff(z,c);
    ex Gz = G.z.diff(x,a).diff(y,b).diff(z,c);

    return quaternion<ex>(Gt,Gx,Gy,Gz);
}

template <class T>
quaternion<T> RegularG(int a, int b, int c, quaternion<T> q) {
    quaternion<ex> SRG = SymbolicRegularG(a,b,c);
    GiNaC::symbol t("t"), x("x"), y("y"), z("z");
    return quaternion<T>(SRG.t.subs(lst{t,x,y,z},lst{q.t,q.x,q.y,q.z}),
                        SRG.x.subs(lst{t,x,y,z},lst{q.t,q.x,q.y,q.z}),
                        SRG.y.subs(lst{t,x,y,z},lst{q.t,q.x,q.y,q.z}),
                        SRG.z.subs(lst{t,x,y,z},lst{q.t,q.x,q.y,q.z}));
}

}