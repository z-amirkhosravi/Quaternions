#include "elliptic.h"

namespace qtrn {

    using GiNaC::numeric;

    template<class T>
    quaternion<T> Lattice<T>::element(int i0, int i1, int i2, int i3) {
        return basis[0] *i0 + basis[1] *i1 +  basis[2] *i2 + basis[3] *i3;
    }

    EisensteinSeries::EisensteinSeries(int a0, int b0, int c0): a(a0), b(b0), c(c0) {
        summand = SymbolicRegularG(a,b,c,qs);
    } 

    // evaluate(L, N) approximates the vaue of the Eisenstein series by summing the defining summand over the lattice points with indices in [-N,N]
    // ideally rather than take N as input, this should compute for the desired accuracy

    template<class T>
    quaternion<T> EisensteinSeries::evaluate(Lattice<T> L, int N) {
        quaternion<T> q;
        T t0, x0, y0, z0;

        long long count = 0;

        for (int i0 = -N; i0 <= N; i0 ++) 
            for (int i1 =-N; i1 <= N; i1 ++)
                for (int i2 = -N; i2 <= N; i2++)
                    for (int i3 = -N; i3 <= N; i3++) {
                        if (i0==0 && i1==0 && i2==0 && i3==0)
                            continue;
                        // if (++count % 10000 ==0)
                        //     std::cout << count << " ";
                        q = L.element(i0, i1, i2, i3);
                        t0 += ex_to<numeric>(evalf(summand.t.subs(lst{qs.t, qs.x, qs.y, qs.z},lst{q.t, q.x, q.y, q.z}))).to_double();
                        x0 += ex_to<numeric>(evalf(summand.x.subs(lst{qs.t, qs.x, qs.y, qs.z},lst{q.t, q.x, q.y, q.z}))).to_double();
                        y0 += ex_to<numeric>(evalf(summand.y.subs(lst{qs.t, qs.x, qs.y, qs.z},lst{q.t, q.x, q.y, q.z}))).to_double();
                        z0 += ex_to<numeric>(evalf(summand.z.subs(lst{qs.t, qs.x, qs.y, qs.z},lst{q.t, q.x, q.y, q.z}))).to_double();
                        // std::cout << t0 << " " << x0 << " " << y0 << " " << z0 << std::endl;
                        }
        return quaternion<T>(t0,x0,y0,z0);
    }
}