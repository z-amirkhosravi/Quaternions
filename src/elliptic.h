#pragma once

#ifndef ELLIPTIC_H
#define ELLIPTIC_H

#include <vector>
#include "regularG.h"

namespace qtrn {

    // We define a basic lattice class (+ choice of basis), because an Eisenstein Series is going to be evaluated at a Lattice

    template<class T>
    class Lattice {
        public:

        Lattice(quaternion<T> q0, quaternion<T> q1, quaternion<T> q2, quaternion<T> q3): basis({q0,q1,q2,q3}) {}
        Lattice(std::vector<quaternion<T>> b): basis(b) {}

        quaternion<T> element(int, int, int, int);

        private:
        std::vector<quaternion<T>> basis;
    };

    class EisensteinSeries {
        public:
        EisensteinSeries(int a, int b, int c);    // These integers need to be non-negative. 

        // T should almost always be double or float in the next one, but leaving as template just in case there's a use for e.g. rational or complex
        template<class T>
        quaternion<T> evaluate(Lattice<T> L, int N);

        private:
        int a, b, c;
        qsymbol qs;
        quaternion<ex> summand;
    };
}

#include "elliptic.tpp"
#endif