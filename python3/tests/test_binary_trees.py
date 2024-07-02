from binary_trees import BinaryNode, BinaryTree


class TestBinaryTree:
    def test_binary_node(self):
        root = BinaryNode(2)
        assert str(root) == '2'
        assert len(root) == 1

        root.left = BinaryNode(1)
        root.right = BinaryNode(3)
        assert len(root) == 3

        _in_order = [1, 2, 3]
        assert _in_order == list(root)

        _index = 1
        root_1 = BinaryNode(_in_order[_index])
        root_1.left = BinaryNode(_in_order[_index - 1])
        root_1.right = BinaryNode(_in_order[_index + 1])
        assert root == root_1

        _in_order_wrong_keys = [1, 2, 4]
        root_2 = BinaryNode(_in_order_wrong_keys[_index])
        root_2.left = BinaryNode(_in_order_wrong_keys[_index - 1])
        root_2.right = BinaryNode(_in_order_wrong_keys[_index + 1])
        assert root != root_2

    def test_binary_tree(self):
        root = BinaryNode(2)
        tree = BinaryTree(root)
        assert str(tree) == "[2]"
        assert len(tree) == 1

        root.left = BinaryNode(1)
        root.right = BinaryNode(3)
        assert str(tree) == "[1, 2, 3]"
        assert len(tree) == 3

        _in_order = [1, 2, 3]
        tree_1 = BinaryTree(_in_order)
        assert tree == tree_1
        assert str(tree) == "[1, 2, 3]"
        assert len(tree) == 3

        _in_order_wrong_keys = [1, 2, 4]
        tree_2 = BinaryTree(_in_order_wrong_keys)
        assert tree != tree_2

        tree_none = BinaryTree()
        assert tree_none.root is None
        assert str(tree_none) == "[]"
        assert len(tree_none) == 0
