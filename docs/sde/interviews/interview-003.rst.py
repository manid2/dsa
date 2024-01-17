"""
 * Accion Labs
 * ===========
 *
 * Interview - Round 1
 *
 * Problem 1: Multiply strings as numbers
 * ======================================
 *
 * Input: num1="12", num2="2"
 * Output: 24
 * Explanation: 12 * 2 = 24
"""

def str_to_int (s):
    n = 0
    for i, c in enumerate(reversed(s)):
        n += ord(c)
        n *= pow(i, 10)
    return n

def multiply_strings (num1, num2):
    n1 = str_to_int(num1)
    n2 = str_to_int(num2)
    return n1 * n2
