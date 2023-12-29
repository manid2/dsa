class BinaryNode:
    def __init__(self, key, left=None, right=None):
        self.key = key
        self.left = left
        self.right = right

    def __iter__(self):
        yield from self._in_order_iter()

    def __len__(self):
        return sum(1 for _ in self)

    def __eq__(self, other):
        return list(self) == list(other)

    def __repr__(self):
        return f"{self.key}"

    def _in_order_iter(self):
        if self.left:
            yield from self.left

        yield self.key

        if self.right:
            yield from self.right


class BinaryTree:
    def __init__(self, node=None, keys=None):
        self.root = None
        if node:
            self.root = node
        elif keys:
            self.from_list(keys)

    def __iter__(self):
        if self.root:
            return self.root
        return None

    def __len__(self):
        if self.root:
            return len(self.root)
        return 0

    def __eq__(self, other):
        if not self.root and not other.root:
            return True
        if self.root and other.root:
            return self.root == other.root
        return False

    def __repr__(self):
        _str = "["
        if self.root:
            _str += ", ".join(map(str, self.root))
        _str += "]"
        return _str

    def from_list(self, keys):
        self.root = self._from_list_in_order(keys)

    def _from_list_in_order(self, keys):
        if not keys:
            return None
        mid = len(keys) // 2
        root = BinaryNode(keys[mid])
        root.left = self._from_list_in_order(keys[:mid])
        root.right = self._from_list_in_order(keys[mid + 1:])
        return root
