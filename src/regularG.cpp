#include "regularG.h"
#include <ginac/ginac.h>

namespace qtrn {

    using GiNaC::lst, GiNaC::ex, GiNaC::symbol;

// The following is a naive implementation of symbolic G(a,b,c). For computations involving many such functions, 
// they should be computed at the same time, or it's hugely wasteful.

quaternion<ex> SymbolicRegularG(int a, int b, int c, symbol t, symbol x, symbol y, symbol z) {
    quaternion<ex> q(t,x,y,z), G = q.inv()/q.norm();

    ex Gt = G.t.diff(x,a).diff(y,b).diff(z,c);
    ex Gx = G.x.diff(x,a).diff(y,b).diff(z,c);
    ex Gy = G.y.diff(x,a).diff(y,b).diff(z,c);
    ex Gz = G.z.diff(x,a).diff(y,b).diff(z,c);

    return quaternion<ex>(Gt,Gx,Gy,Gz);
}

quaternion<ex> SymbolicRegularG(int a, int b, int c, qsymbol qs) {
    return SymbolicRegularG(a,b,c,qs.t,qs.x,qs.y,qs.z);
}
}