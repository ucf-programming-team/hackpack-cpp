/**
 * if you provide less than D args for dimension, it is assumed
 * to be 0 examples: Vec<2, int> a(10, 50); // int a[10][50]
 * initialized with zero Vec<3, double> b(n, m, k, 3.14); //
 * double b[n][m][k] initialized with 3.14
 */

template <int D, typename T>
struct Vec : public vector<Vec<D - 1, T>> {
  static_assert(D >= 1,
                "Vector dimension must be greater than zero!");
  template <typename... Args>
  Vec(int n = 0, Args... args):
    vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {}
};
template <typename T>
struct Vec<1, T> : public vector<T> {
  Vec(int n = 0, const T& val = T()): vector<T>(n, val) {}
};