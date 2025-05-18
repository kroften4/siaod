#include "QueueDA.h"
#include "QueueLL.h"

int main() {
	krft::QueueDA<int> q_da{new int[] {1, 2, 3}, 3};
	std::cout << q_da;
	std::cout << q_da.back();

	krft::QueueLL<int> q_ll{new int[] {1, 2, 3}, 3};
	std::cout << q_ll;
	std::cout << q_ll.back();
}

