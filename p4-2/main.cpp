#include "Queue.h"

int main() {
	krft::Queue<int> q{new int[] {1, 2, 3}, 3};
	// std::cout << q;
	std::cout << q[0] << q[1] << q[2];
	std::cout << q[3];
}

