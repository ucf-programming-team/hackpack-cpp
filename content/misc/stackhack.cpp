/*
  stackhack.cpp
  Use this shit when sparta is being annoying
*/
#include <sys/resource.h> // important
int main(void) {
	const rlim_t kStackSize = 1024 * 1024 * 1024;
	struct rlimit rl;
	int result;
	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0) {
		// std::cerr << rl.rlim_cur << std::endl;
		if (rl.rlim_cur < kStackSize) {
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			// if (result != 0)
			// 	std::cerr << "setrlimit returned result = " << result << "\n";
		}
	}
	return 0;
}
