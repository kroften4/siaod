namespace krft {
	template <typename DataT>
	struct Node {
		DataT value;
		Node * next;
		Node(DataT value) : value{value}, next{nullptr} {};
	};
}

