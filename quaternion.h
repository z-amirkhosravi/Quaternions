#pragma once

// 2023-05-11:	Created by Z.Amir-Khosravi

#ifndef QUATERNION_H
#define QUATERNION_H

#include <ostream>

namespace qtrn {

template <class T>
class quaternion {
public:
	T t, x, y, z;
	quaternion(T, T, T, T);
	quaternion<T> conj() const;
	quaternion<T> inv() const;
	T norm() const;
	T trace() const;

	quaternion<T> operator+ (const quaternion<T>& q) const;
	quaternion<T> operator- (const quaternion<T>& q) const;
	quaternion<T> operator* (const quaternion<T>& q) const;
	quaternion<T>& operator+= (const quaternion<T>& q);	

	quaternion<T> operator* (const T& s) const;

	bool operator== (const quaternion<T>& q) const;

	template <class  T>
	friend std::ostream& operator<<(std::ostream& os, const quaternion<T>& q);
};


template <class  T>
std::ostream& operator<<(std::ostream& os, const quaternion<T>& q);

template <class T>
const quaternion<T> e0{ 1, 0, 0, 0 };

template <class T>
const quaternion<T> e1{ 0, 1, 0, 0 };

template <class T>
const quaternion<T> e2{ 0, 0, 1, 0 };

template <class T>
const quaternion<T> e3{ 0, 0, 0, 1 };


// the Fueter regular functions:

template <class T>
quaternion<T> z1(quaternion<T> q);

template <class T>
quaternion<T> z2(quaternion<T> q);

template <class T>
quaternion<T> z3(quaternion<T> q);

template <class T>
quaternion<T> RegularP(int a, int b, int c, quaternion<T> q);

}

#include "quaternion.tpp"
#endif