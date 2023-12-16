from queue import PriorityQueue


class HuffmanNode:
    def __init__(self, char, freq, left=None, right=None):
        self.char = char
        self.freq = freq
        self.left = left
        self.right = right
        self.bits = ''

    def __lt__(self, nxt):
        return self.freq < nxt.freq


class HuffmanTree:
    def __init__(self, nodes):
        self.encoded_bits = {}
        self.walk(nodes.get())

    def walk(self, node, bits=''):
        new_bits = bits + str(node.bits)

        if node.left:
            self.walk(node.left, new_bits)

        if node.right:
            self.walk(node.right, new_bits)

        if (not node.left and not node.right):
            self.encoded_bits[node.char] = new_bits

    def get(self):
        return self.encoded_bits


class HuffmanCoding:
    """
    Huffman coding algorithm to compress (encode) and decompress (decode)

    Refer:

    * `Huffman Coding | Greedy Algo-3 <gfg1>`_

    .. _gfg1: https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
    """

    def __init__(self, chars_freqs):
        self.chars_freqs = chars_freqs

    def compress(self):
        """
        Steps:

        * Use min heap to store Huffman nodes
        * Repeat till there is only 1 node in Huffman tree
            * Get two smallest nodes from min heap as left and right
            * Assign 0 to left nodes and 1 to right nodes
            * Put the sum of smallest nodes into min heap
        """
        nodes = PriorityQueue()
        for c, f in self.chars_freqs.items():
            nodes.put(HuffmanNode(c, f))

        while nodes.qsize() > 1:
            left = nodes.get()
            right = nodes.get()

            left.bits = 0
            right.bits = 1

            new_node = HuffmanNode(left.char + right.char,
                                   left.freq + right.freq,
                                   left, right)
            nodes.put(new_node)
        return HuffmanTree(nodes).get()
