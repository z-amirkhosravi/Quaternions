#ifndef REGULARG_H
#define REGULARG_H
#include "quaternion.h"
#include <ginac/ginac.h>

namespace qtrn {

template<class T>
quaternion<T> RegularG(int a, int b, int c, quaternion<T> q);

quaternion<GiNaC::ex> SymbolicRegularG(int a, int b, int c);
}

#include "regularg.tpp"
#endif