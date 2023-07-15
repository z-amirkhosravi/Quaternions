#include "quaternion.h"
#include <ostream>

// 2023-05-11:	Created by Z.Amir-Khosravi

namespace qtrn {
	template <class T>
	quaternion<T>::quaternion()	{}

	template <class T>
	quaternion<T>::quaternion(T t0) : t(t0), x(0), y(0), z(0) {}

	template <class T>
	quaternion<T>::quaternion(T t0, T x0, T y0, T z0) :
		t(t0), x(x0), y(y0), z(z0)
	{}

	template <class T>
	quaternion<T> quaternion<T>::conj() const {
		return quaternion<T>(t, -x, -y, -z);
	}

	template <class T>
	T quaternion<T>::norm() const {
		return t * t + x * x + y * y + z * z;
	}

	template <class T>
	T quaternion<T>::trace() const {
		return t + t;
	}



	template <class T>
	quaternion<T> quaternion<T>::inv() const {
		return this->conj() * (1 / this->norm());			// note this can exhibit undefined behavior because of 1/this->norm() 
	}

	template <class T>
	quaternion<T> quaternion<T>::operator+ (const quaternion<T>& q) const {
		return quaternion<T>(t + q.t, x + q.x, y + q.y, z + q.z);
	}

	template <class T>
	quaternion<T> quaternion<T>::operator- (const quaternion<T>& q) const {
		return quaternion<T>(t - q.t, x - q.x, y - q.y, z - q.z);
	}
	
	template <class T>
	quaternion<T> quaternion<T>::operator* (const quaternion<T>& q) const {
		return quaternion<T>{	t* q.t - x * q.x - y * q.y - z * q.z,
			t* q.x + x * q.t + y * q.z - z * q.y,
			t* q.y - x * q.z + y * q.t + z * q.x,
			t* q.z + x * q.y - y * q.x + z * q.t };
	}

	// The following inherits undefined behavior from inv() when q is zero.
	template <class T>
	quaternion<T> quaternion<T>::operator/ (const quaternion<T>& q) const {
		return *this * q.inv();
	}

	template <class T>
	quaternion<T> & quaternion<T>::operator+= (const quaternion<T>& q) {
		t += q.t;
		x += q.x;
		y += q.y;
		z += q.z;
		return *this;
	}

	template <class T>
	quaternion<T>& quaternion<T>::operator*= (const quaternion<T>& q) {
		return *this = *this * q;
	}

	template <class T>
	quaternion<T>& quaternion<T>::operator/= (const quaternion<T>& q) {
		return *this = *this / q;
	}

	template <class T>
	bool quaternion<T>::operator== (const quaternion<T>& q) const {
		return (t == q.t) && (x == q.x) && (y == q.y) && (z == q.z);
	}

	template <class T>
	quaternion<T> quaternion<T>::operator* (const T& s) const {
		return quaternion<T>{s * t, s * x, s * y, s * z };
	}

	template <class T>
	std::ostream& operator<<(std::ostream& os, const quaternion<T>& q) {
		os << '(' << q.t << ',' << q.x << ',' << q.y << ',' << q.z << ')';
		return os;
	}


	//  the basic Fueter-regular functions

	template <class T>
	quaternion<T> RegularP100(quaternion<T> q) {
		return quaternion<T>(-q.x, q.t, 0, 0);
	}

	template <class T>
	quaternion<T> RegularP010(quaternion<T> q) {
		return quaternion<T>(-q.y, 0, q.t, 0);
	}

	template <class T>
	quaternion<T> RegularP001(quaternion<T> q) {
		return quaternion<T>(-q.z, 0, 0, q.t);
	}

	template <class T>
	quaternion<T> GG(quaternion<T> q) {
		;
		return q.conj() / (q.norm() * q.norm());
	}

	// This function computes the _unnormalized_ regular polynomials. That is, without the 1/n! factor. 
	template <class T>
	quaternion<T> RegularP(int a, int b, int c, quaternion<T> q) {
		if (!a && !b && !c)
			return quaternion<T>(1, 0, 0, 0);

		quaternion<T> z1 = RegularP100(q);
		if (a == 1 && !b && !c)
			return z1;

		quaternion<T> z2 = RegularP010(q);
		if (!a && b == 1 && !c)
			return z2;

		quaternion<T> z3 = RegularP001(q);
		if (!a && !b && c == 1)
			return z3;

		
		quaternion<T> S(0, 0, 0, 0);
		/*
		if (a > 0)
			S += z1 * RegularP(a - 1, b, c, q);
		if (b > 0)
			S += z2 * RegularP(a, b - 1, c, q);
		if (c > 0)
			S += z3 * RegularP(a, b, c - 1, q);
			*/

		int m = (a + b + c) / 2;

		for (int i = 0; i <= std::min(a, m); i++)
			for (int j = 0; j <= std::min(b, m - i); j++)
				for (int k = 0; k <= m - i - j; k++)
					if (i || j || k)
						S += RegularP(i, j, k, q) * RegularP(a - i, b - j, c - k, q);

		return S;
	}
}


