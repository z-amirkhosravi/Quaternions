#ifndef QPYRAMID_H
#define QPYRAMID_H

#include "quaternion.h"
#include <vector>

namespace qtrn {

	template <class T>
	class QPyramid {
	public:
		QPyramid();
		QPyramid(int);
		QPyramid(quaternion<T>);
		QPyramid(quaternion<T>, int);

		quaternion<T> operator() (int, int, int);

		void generate();
		int height();
		quaternion<T> P(int, int, int) const;

	private:
		int h;
		quaternion<T> q;
		std::vector<std::vector<std::vector<quaternion<T>>>> pyr;
	};

}

#include "qpyramid.tpp"
#endif