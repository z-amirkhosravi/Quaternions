

#include "quaternion.h"
#include "qpyramid.h"

#include <iostream>
#include <format>
#include <vector>

int main()
{
    using std::vector;
    using qtrn::quaternion;
    using qtrn::QPyramid;

    quaternion<double> q{ 1, 2, 3, 4 };
    quaternion<double> p{ 0, 0, 0, -1 };
    std::cout << "norm of q = " << (q + p).norm() << '\n';
    std::cout << "q=" << q << '\n';

    std::cout << "e0 = " << qtrn::e0<double> << '\n';
    std::cout << "e1 = " << qtrn::e1<double> << '\n';
    std::cout << "e2 = " << qtrn::e2<double> << '\n';
    std::cout << "e3 = " << qtrn::e3<double> << '\n';

    std::cout << "e1 * e1 = " << qtrn::e1<double> *qtrn::e1<double> << '\n';
    std::cout << "e2 * e2 = " << qtrn::e2<double> *qtrn::e2<double> << '\n';
    std::cout << "e3 * e3 = " << qtrn::e3<double> *qtrn::e3<double> << '\n';
    std::cout << "e0 * e0 = " << qtrn::e0<double> *qtrn::e0<double> << '\n';

    std::cout << "q * 10 = " << q * 10 << '\n';

    std::cout << "q.inv() =  " << q.inv() << '\n';

    std::cout << "q.inv() * q = " << q.inv() * q << '\n';

    std::cout << "Testing Regular Poylnomials:" << "\n";
    
    quaternion<double> z1 = qtrn::RegularP100(q), z2 = qtrn::RegularP010(q), z3 = qtrn::RegularP001(q);

    std::cout << "z1 = " << z1 << " z2 = " << z2 << " z3 = " << z3 << "\n";

    std::cout << "P100 = " << (qtrn::RegularP(1, 0, 0, q)) << " P010 = " << (qtrn::RegularP(0, 1, 0, q)) << " P001 = " << (qtrn::RegularP(0, 0, 1, q)) << "\n";

    std::cout << "P(1,0,0)==z1? " << (qtrn::RegularP(1, 0, 0, q) == z1) << "\n";
    std::cout << "P(0,1,0)==z2? " << (qtrn::RegularP(0, 1, 0, q) == z2) << "\n";
    std::cout << "P(0,0,1)==z3? " << (qtrn::RegularP(0, 0, 1, q) == z3) << "\n";

    //qtrn::quaternion<double> u = z1 * z2;
    //u += z2 * z1;

    std::cout << "P(1,1,0) =" << qtrn::RegularP(1, 1, 0, q) << "\n";
    std::cout << "z1*z2 + z2*z1 = " << z1 * z2 + z2 * z1 << "\n";

    std::cout << "P(1,1,0)==z1z2 + z2z1? " << (qtrn::RegularP(1, 1, 0, q) == z1*z2 + z2*z1) << "\n";

    QPyramid<double> qp(q, 10);

    std::cout << "QPyramid(1,1,0) = " << qp(1, 1, 0) << "\n";

}
