/**
 * Aviz Networks
 * Senior Software Engineer
 * DPDK: C & Python
 * Round 2
 * 2024-01-18T16:00:28+0530
 */

/**
 * Problem 1: Pointer deference and operators precedence.
 * ======================================================
 *
 * My solution: 0 1 2 3 4
 * Correct solution: 0 1 2 2 3
 */
void ptr_ops(void)
{
	int i;
	int *ptr = (int *) malloc(5 * sizeof(int));

	for (i=0; i<5; i++)
		*(ptr + i) = i;

	printf("%d ", *ptr++);
	printf("%d ", (*ptr)++);
	printf("%d ", *ptr);
	printf("%d ", *++ptr);
	printf("%d ", ++*ptr);
}

/**
 * Problem 2: Search for string in another string
 * ==============================================
 *
 * Given:
 *
 * char portlist[xx] = "Ethernet1,Ethernet2,Ethernet3,Ethernet4,Ethernet6,"
 *                     "Ethernet7,Ethernet8,Ethernet9,Ethernet10";
 * char newPort[xx] = "Ethernet1";
 *
 * Check if the newPort is part of portlist.?
 *
 * Note : only string compare/copy functions of string.h is allowed and not
 * any other APIs.
 *
 * My solution: Not worked at strncmp () but explained logic.
 */

#include <stdio.h>
#include <string.h>

void str_search(void)
{
	char portlist[] = "Ethernet1,Ethernet2,Ethernet3,Ethernet4,Ethernet6,"
		"Ethernet7,Ethernet8,Ethernet9,Ethernet10";
	char newPort[] = "Ethernet01";

	int nplen = 0;
	char *pl = portlist;
	int ps = 0;
	char np[sizeof(newPort) + 2];
	memset (np, 0, sizeof (np));
	while (*pl) {
		ps = strchr (pl, ',') - pl;
		printf ("ps: %d\n", ps);
		if (ps < 1) {
			printf ("np: %s not exists\n", np);
			break;
		}
		strncpy(np, pl, ps);
		printf ("np: %s, newPort: %s\n", np, newPort);
		// FIXME check string is equal
		pl += ps + 1;
	}
	return 0;
}

/**
 * Problem 3: Largest contiguous sub-array sum (Kadane's algorithm)
 * ================================================================
 *
 * Given an array arr[] of size N. The task is to find the sum of the
 * contiguous sub-array within a arr[] with the largest sum.
 *
 * Example 1:
 *
 * Input: -2 -3 4 -1 -2 1 5 -3
 * Output: 4-->5 = 7
 * 
 * My solution: Incomplete just explained of comparing previous maximum sum
 * with current maximum sum by moving two pointers (begin & end).
 */

#define N 10

int largestSubArraySum(void)
{
	int a[] = {-2, -3, 4, -1, -2, 1, 5, -3, 0, 0};
	int sum = 0, pre_sum = 0;
	int h=0, b=0, e=0;
	while (e < N) {
		pre_sum += a[e++];
		if (sum > pre_sum)
	}
	return 0;
}

/**
 * Problem 4: LRU replacement
 * ==========================
 *
 * Given that we have many books present in the library. And you have only N
 * decks available in front lounge where you can only display N Books at a
 * given time.  If in-case any new book is requested by user and it is not
 * present in deck then least recently used book should be replaced with
 * user-requested new book.
 *
 * Write a program to efficiently implement the above requirement.
 *
 * My solution: using Double ended queue + hashing this can be implemented
 */

/**
 * Question 1: ConfD Keypath internals
 *
 * How internally confd manages the keypath and call point?
 *
 * My solution: Manages using binary tree data structures similar to xpath.
 *
 * Follow up: why cannot it be hash.?
 */

/** Question 2: Thread synchronization techniques
 *
 * My answer: Explained thread synchronization techniques such as Locks,
 * Mutexes, conditional variables.
 *
 * Follow up: Explained best synchronization techniques for multiple write
 * applications
 *
 * My answer: For multiple write applications use locking with mutexes to give
 * the thread exclusive access to write.
 */

/**
 * Question 3: What is ARP?
 * ========================
 *
 * My answer: Address Resolution Protocol used to map IP (logical system)
 * addresses to MAC (hardware) addresses to achieve host-to-host communication
 * in TCP/IP layer 3 (network layer).
 */

/**
 * Question 4: 400G incoming traffic to 1G OS capacity how it handles?
 * ===================================================================
 *
 * My answer: Explained Rx queue full and packets drop due to out of memory.
 */
