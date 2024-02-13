# Commvault - Senior Engineer
# Round 1 - 2024-02-13T11:30:00+0530

# Brute force: TC O(n^2), SC O(1)
def _01_subarrays_equal_0s_1s(nums):
    c = 0
    m = {0: 0, 1: 1}
    for i in range(len(nums) - 1):
        for j in range(i, len(nums)):
            m[nums[i]] += 1
        if m[0] == m[1]:
            c += 1
    return c

# Optimized: TC O(n), SC O(1)
def _02_subarrays_equal_0s_1s(nums):
    b = 0, e = 0, c = 0
    m = {0: 0, 1: 1}
    pass
