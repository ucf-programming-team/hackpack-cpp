template <class T>
struct MinQueue : public deque<T> {
  deque<T> minq;
  void add(T val) {
    this->push_back(val);
    while (!minq.empty() && minq.back() > val)
      minq.pop_back();
    minq.push_back(val);
  }
  T pop() {
    T val = this->front();
    this->pop_front();
    if (minq.front() == val)
      minq.pop_front();
    return val;
  }
  T min() { return minq.front(); }
};
