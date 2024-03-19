template<typename T>
struct Matrix {
	int n_row, n_col;
	vector<T> x;

	// accessors
	typename vector<T>::iterator operator [] (int r) {
		return x.begin() + r * n_col;
	}
	inline T get(int i, int j) const { return x[i * n_col + j]; }

	// constructors
	Matrix() = default;
	Matrix(int _n_row, int _n_col) : n_row(_n_row), n_col(_n_col), x(n_row * n_col) {}
	Matrix(const vector<vector<T>>& d) : n_row(d.size()), n_col(d.size() ? d[0].size() : 0) {
		for (auto& row : d) std::copy(row.begin(), row.end(), std::back_inserter(x));
	}

	// convert to 2d vec
	vector<vector<T>> vecvec() const {
		vector<vector<T>> ret(n_row);
		for (int i = 0; i < n_row; i++) {
			std::copy(x.begin() + i*n_col,
								x.begin() + (i+1)*n_col,
								std::back_inserter(ret[i]));
		}
		return ret;
	}
	operator vector<vector<T>>() const { return vecvec(); }

	static Matrix identity(int n) {
		Matrix res(n, n);
		for (int i = 0; i < n; i++) {
			res[i][i] = 1;
		}
		return res;
	}

	Matrix transpose() const {
		Matrix res(n_col, n_row);
		for (int i = 0; i < n_row; i++) {
			for (int j = 0; j < n_col; j++) {
				res[j][i] = this->get(i, j);
			}
		}
		return res;
	}

	Matrix operator * (const Matrix& r) const {
		assert(n_col == r.n_row);
		auto rt = r.transpose();
		Matrix res(n_row, r.n_col);

		for (int i = 0; i < n_row; i++) {
			for (int j = 0; j < rt.n_row; j++) {
				for (int k = 0; k < n_col; k++) {
					res[i][j] = (res[i][j] + this->get(i, k) * rt.get(j, k)) % MOD;
				}
			}
		}
		return res;
	}

	Matrix pw(long long exp) {
		assert(n_col == n_row && exp >= 0);
		Matrix res = identity(n_col), base = *this;
		while (exp) {
			if (exp & 1) {
				res = res * base;
			}
			base = base * base;
			exp >>= 1;
		}
		return res;
	}
};