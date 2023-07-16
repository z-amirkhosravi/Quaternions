#pragma once

#ifndef REGULARG_H
#define REGULARG_H

/* regularG.h, regularG.tpp, and regulargG.cpp implement the Fueter-regular "G functions", which are homgeoneous polynomials of negative degree. The function G(q) = q^{-1} / Nq
    has deggree -3 and is the starting point. G(a,b,c) is then the derivative of G(q), a times with respect to x, b time wrt y, c times wrt z.

   Because we need the GiNaC library to do this computation, it's done in a separate file.

*/

#include "quaternion.h"

#include <ginac/ginac.h>

namespace qtrn {
using GiNaC::symbol;
using GiNaC::ex;

// a symbol wrapper class four symbols for one quaternion
class qsymbol {
    public:
    symbol t,x,y,z;

    qsymbol(symbol t0, symbol x0, symbol y0, symbol z0): t(t0), x(x0), y(y0), z(z0) {}
    qsymbol(): t("t"), x("x"), y("y"), z("z") {}
};

template<class T>
quaternion<T> RegularG(int a, int b, int c, quaternion<T> q);

quaternion<ex> SymbolicRegularG(int a, int b, int c, symbol t, symbol x, symbol y, symbol z);
quaternion<ex> SymbolicRegularG(int a, int b, int c, qsymbol qs);

}

#include "regularG.tpp"
#endif