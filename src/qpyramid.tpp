#include "quaternion.h"
#include "qpyramid.h"

namespace qtrn {
	template<class T>
	QPyramid<T>::QPyramid() : h(0) {}

	template<class T>
	QPyramid<T>::QPyramid(int height) : h(height) {
		pyr.resize(h, std::vector < std::vector<quaternion<T>>>(h, std::vector<quaternion<T>>(h)));
	}

	template<class T>
	QPyramid<T>::QPyramid(quaternion<T> q0) : q(q0) {}

	template<class T>
	QPyramid<T>::QPyramid(quaternion<T> q0, int height) : q(q0), h(height) {
		pyr.resize(h, std::vector < std::vector<quaternion<T>>>(h, std::vector<quaternion<T>>(h)));
		generate();
	}

	template<class T>
	quaternion<T> QPyramid<T>::operator() (int a, int b, int c) {
		return pyr[a][b][c];
	}

	template<class T>
	void QPyramid<T>::generate() {

		if (h == 0)
			return;

		pyr[0][0][0] = 1;

		if (h == 1)
			return;

		quaternion<T> z1 = RegularP100(q), z2 = RegularP010(q), z3 = RegularP001(q);

		pyr[1][0][0] = z1;
		pyr[0][1][0] = z2;
		pyr[0][0][1] = z3;


		for (int m = 2; m < h; m++) {
			for (int i = 0; i <= m; i++) 
				for (int j = 0; j <= m - i; j++) {
					int k = m - i - j;
					pyr[i][j][k] = 0;
					if (i>0)
						pyr[i][j][k] += z1 * pyr[i - 1][j][k];
					if (j>0)
						pyr[i][j][k] += z2 * pyr[i][j - 1][k];
					if (k>0)
						pyr[i][j][k] += z3 * pyr[i][j][k - 1];

				}
		}
	}

	template <class T>
	quaternion<T> QPyramid<T>::P(int a, int b, int c) const {
		return pyr[a][b][c];
	}

	template <class T>
	int QPyramid<T>::height() {
		return h;
	}
}