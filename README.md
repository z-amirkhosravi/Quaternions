# Computations in Quaternionic Analysis

This is a current project I'm working on. The aim is to implement some computational tools for use in **_quaternionic analysis_**.

This is an area of mathematics that's not been very active since it was discovered nearly eighty years ago. As a result, there are virtually no computational tools available for it.

To be clear, there are many tools available for _quaternionic algebra_, but _analysis_ is a different beast altogether.

To see why this is computationally difficult let me describe the most basic objects in the area. In _complex analysis_ one is interested in functions of the form
$$f(z) = \sum_{n} a_n z^n,$$
where $a_n$ and $z$ are complex numbers, and the sum is indexed by integers $n$. By contrast, in quaternionic analysis, the analogous functions have the form
$$f(q) = c + \sum_{\nu} a_\nu G_{\nu}(q)  + \sum_{\nu} b_\nu P_{\nu}(q),$$
where:
- $q$, $c$, $a_{\nu}$, $b_{\nu}$ are quaternions.
- The sums are indexed by triples $\nu = (a,b,c)$ of non-negative integers, with $abc\neq 0$.
- The functions $P_{\nu}(q)$ are non-commutative polynomials in the variables
  $$z_1 = it - x,\ \ \  z_2 = jt - y,\ \ \  z_3 = kt - z,$$
  derived from the independent variable $q = t + ix + iy + iz$.
- The functions $G_{\nu}(q)$ are given by the partial derivatives
  
$$G_{a,b,c}(q) = \frac{\partial^{a+b+c}}{\partial x^a \partial y^b \partial z^c} \frac{t-ix-jy-kz}{(t^2+x^2+y^2+z^2)^2}.$$

$P_{\nu}(q)$ and $G_{\nu}(q)$ are quaternionic analogues of the monomials $z^n$ for $n$ positive and negative, respectively. They become increasingly complicated as the index $\nu$ grows, e.g.:
$$P_{(1,1,1)}(q) = z_1 z_2 z_3 + z_1 z_3 z_2 + z_2 z_3 z_1 + z_2 z_1 z_3 + z_3 z_1 z_2 + z_3 z_2 z_1$$
and
$$G_{(1,1,1)}(q) = 192\frac{ix^2yz + jxy^2 z + kxyz^2-txyz}{(z^2+t^2+x^2+y^2)^5} - 24\frac{iyz+jxz+kyz}{(t^2+x^2+y^2+z^2)^4}.$$

The number of operations required to compute each of these functions grows exponentially as $n=a+b+c$ increases. Compared with $z^n$ from complex analysis there is just a lot more to compute. 

See my <a href=https://arxiv.org/pdf/2002.06140.pdf>preprint</a> for more detailed information about quaternionic analysis.

I'm especially interested in computing values of the form
$$E_{\nu}(L)= \sum_{x \in L} G_{\nu}(x)$$
where $x$ varies over a lattice $L$ of rank $4$ embedded in quaternion space. These are quaternionic analogues of complex _Eisenstein series_ which are a type of modular form. It would be interesting to check numerically whether the
real components of $E_{\nu}(L)$ have any significant algebraic properties when the lattice $L$ has an arithmetic origin. To do this, one has to compute $E_{\nu}(L)$ to many significant digits, and at the moment this just takes too long. 

# Implementation

The code here compiles with GNU C++ running under the Windows Linux Subsystem. It uses the <a href=https://www.ginac.de/>GiNaC<a> library for symbolic computations, which in turn uses <a href=https://www.ginac.de/CLN/>CLN</a>.

Everything is in the namespace `qtrn`. There is a template class `qtrn::quaternion<T>` where $T$ is the data type of the components $t,x,y,z$ for a quaternion $q = t + ix + iy + iz$. To compute one of the quantities $E_{\nu}(L)$
described above, we can write

```

#include <iostream>
#include <ginac/ginac.h>

#include "quaternion.h"
#include "regularG.h"
#include "elliptic.h"

int main()
{    using qtrn::quaternion;

    // x0,x1,x2,x3 below are generators of the Hurwitz order: (1+i+j+k)/2, i, j, k
    quaternion<double> x1 = qtrn::e1<double>, x2 = qtrn::e2<double>, x3 = qtrn::e3<double>;
    quaternion<double> x0 = (qtrn::e0<double> + x1 + x2 + x3) * 0.5l;

    qtrn::Lattice<double> L(x0,x1,x2,x3);

    qtrn::EisensteinSeries E(1,1,1);

    std::cout << E.evaluate(L, 5) << std::endl;

    std::cout << E.evaluate(L, 10) << std::endl;

    std::cout << E.evaluate(L, 20) << std::endl;
    return 0;
}
```


This attempts to compute $E_{(1,1,1)}(L)$ three times, for a simple arithmetic lattice $L$. The first attempt computes $5^5=625$ terms, and takes about a second on my laptop. The next attempt tries $10^4=10000$
terms and takes about ten seconds. The third attempt tries $20^4=160,000$ terms and takes a couple of minutes. The output is:

```
(-0.00497808,-0.0117233,-0.0117233,-0.0117233)
(-0.00140376,-0.00323157,-0.00323157,-0.00323157)
(-0.000371042,-0.000848833,-0.000848833,-0.000848833)
```

As might be apparent from how different the results are, the convergence is very slow. The function $G_{(1,1,1)}$ is homogeneous of order $-4$, which means it goes to zero just fast enough for the lattice
sum to converge. If we try $E_{(a,b,c)}(L)$ with $a+b+c$ larger, the convergence will be faster, but the summand functions $G_{(a,b,c)}$ will get more complicated.

One either has to have a very fast computer and a great deal of patience, or find a better way.

# General Ideas

- Right now the code uses GiNaC to compute the function $G_{\nu}$ symbolically, then relies on GiNaC's symbolic substitution routines to compute $G_{\nu}(x)$ for each $x$. 
Perhaps one can extract the computation graph from GiNaC after the first step and do the second step more efficienctly. This should also make it easier to upgrade the precision by using `long double` for example.

- An obvious improvement would be to use lattice symmetries to cut down on the number of terms. This could speed it up by a large factor, but is not going to change the time complexity. 

- Will need to implement saving a partial computation to continue it later.

- Is there a formula for $E_{\nu}(L)$ that's easier to compute? 

- Need to figure out exactly how many terms are required for a given precision.
