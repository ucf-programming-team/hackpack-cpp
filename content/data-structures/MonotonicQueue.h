/**
 * Description: Queue that maintains its minimum/maximum element.
 * Time: Amortized $O(1)$ for $\texttt{push()}$, true
 * $O(1)$ for $\texttt{pop()}/\texttt{min()}$.
 * Usage: Works exactly like std::queue;
 * monotonic_queue<T> gives a min queue,
 * and monotonic_queue<T, greater<T>> gives a max queue.
 */
template<class T, class Compare = less<T>>
struct monotonic_queue: queue<T> {
	using q = queue<T>;
	deque<T> mq;
	Compare cmp;
	const T& min() { return assert(!q::empty()), mq.front(); }
	void update() {
		while (!mq.empty() && cmp(q::back(), mq.back()))
			mq.pop_back();
		mq.push_back(q::back());
	}
	void pop() {
		assert(!q::empty());
		if (!mq.empty() && !cmp(mq.front(), q::front()))
			mq.pop_front();
		q::pop();
	}
	void push(const T& val) { queue<T>::push(val), update(); }
	void push(T&& val) { queue<T>::push(val), update(); }
	template<class... Args> void emplace(Args&&... args) {
		q::emplace(args...), update();
	}
};
