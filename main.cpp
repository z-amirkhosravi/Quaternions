// Quaternions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "quaternion.h"
#include <iostream>
#include <format>

int main()
{
    qtrn::quaternion<double> q{ 1, 2, 3, 4 };
    qtrn::quaternion<double> p{ 0, 0, 0, -1 };
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
    
    qtrn::quaternion<double> z1 = qtrn::RegularP100(q), z2 = qtrn::RegularP010(q), z3 = qtrn::RegularP001(q);

    std::cout << "P(1,0,0)==z1? " << (qtrn::RegularP(1, 0, 0, q) == z1) << "\n";
    std::cout << "P(0,1,0)==z1? " << (qtrn::RegularP(0, 1, 0, q) == z2) << "\n";
    std::cout << "P(0,0,1)==z1? " << (qtrn::RegularP(0, 0, 1, q) == z3) << "\n";

    //qtrn::quaternion<double> u = z1 * z2;
    //u += z2 * z1;

    std::cout << "P(1,1,0)==z1z2 + z2z1? " << (qtrn::RegularP(1, 1, 0, q) == q) << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
