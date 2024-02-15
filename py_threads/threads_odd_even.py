"""
 * Print odd & even numbers in sync with 2 threads
 *
 * Example:
 * thread 1: 1
 * thread 2: 2
 * thread 1: 3
 * thread 2: 4
"""

from threading import Thread, Lock, Condition


class ThreadsOddEven:
    def __init__(self):
        # threads synchronization primitives
        self.mx = Lock()
        self.cv = Condition(lock=self.mx)

        # shared data between threads
        self.sd = 1

        self.max_data = 10

    # cv.wait_for() predicate objects don't take args
    def is_odd(self):
        return self.sd % 2

    def is_even(self):
        return not self.is_odd()

    def print_odd(self, tidx):
        while self.sd < self.max_data:
            # use with state for cv to acquire & release lock
            with self.cv:
                # cv.wait_for(predicate) handles spurious wake up
                self.cv.wait_for(self.is_odd)
                print(f"thread {tidx}: {self.sd}")
                self.sd += 1
                self.cv.notify()

    def print_even(self, tidx):
        while self.sd < self.max_data:
            # use with state for cv to acquire & release lock
            with self.cv:
                # cv.wait_for(predicate) handles spurious wake up
                self.cv.wait_for(self.is_even)
                print(f"thread {tidx}: {self.sd}")
                self.sd += 1
                self.cv.notify()


def main():
    th = ThreadsOddEven()
    t1 = Thread(target=th.print_odd, args=(0,))
    t2 = Thread(target=th.print_even, args=(1,))
    t1.start()
    t2.start()
    t1.join()
    t2.join()


if __name__ == "__main__":
    main()
