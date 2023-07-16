

#include "quaternion.h"
#include "regularG.h"
#include "elliptic.h"

#include <iostream>
#include <vector>

#include <cln/real_io.h>
#include <ginac/ginac.h>


//  This is unorganized test code to see if the basic functions work. At some point it has to be made into a systematic test suite.

int main()
{
    using std::vector;
    using qtrn::quaternion;

    // generators of the Hurwitz maximal order: (1+i+j+k)/2, i, j, k
    quaternion<double> x1 = qtrn::e1<double>, x2 = qtrn::e2<double>, x3 = qtrn::e3<double>;
    quaternion<double> x0 = (qtrn::e0<double> + x1 + x2 + x3) * 0.5l;

    qtrn::Lattice<double> L(x0,x1,x2,x3);

    qtrn::EisensteinSeries E(1,1,1);

    std::cout << E.evaluate(L, 5) << std::endl;

    std::cout << E.evaluate(L, 10) << std::endl;

}
