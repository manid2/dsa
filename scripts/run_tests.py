#!/usr/bin/env python3


import os
import re
import subprocess


from dataclasses import dataclass


@dataclass
class CppTestsSummary():
    sources: int = 0
    implementations: int = 0
    tests: int = 0

    def parse_ts(self, result):
        pat1 = r'Executed (\d+) implementations'
        pat2 = r'with (\d+) tests'

        mat1 = re.search(pat1, result)
        mat2 = re.search(pat2, result)

        n1 = int(mat1.group(1)) if mat1 else 0
        n2 = int(mat2.group(1)) if mat2 else 0

        self.sources += 1
        self.implementations += n1
        self.tests += n2


def main():
    git_ls = ["git", "ls-files", "--cached", "--others", "--exclude-standard"]

    # get all cpp source files
    cpp_pat =["cpp/**/*.cpp"]
    cpp_srcs_cmd =git_ls + ["--"] + cpp_pat
    cpp_srcs_proc = subprocess.Popen(cpp_srcs_cmd, stdout=subprocess.PIPE,
                                     stderr=subprocess.PIPE)
    result = cpp_srcs_proc.stdout.readlines()

    cpp_srcs = []
    for line in result:
        cpp_srcs.append(line.decode("utf-8").rstrip())

    # create cpp bin files from source files
    cpp_bins = []
    for line in cpp_srcs:
        line = line.removeprefix("cpp/")
        line = line.removesuffix(".cpp")
        cpp_bins.append("cpp/build/" + line)

    print("")
    print("# " + ''.join(["="]*76))
    print("# Running C++ tests")
    print("# " + ''.join(["="]*76))
    print("")

    cpp_ts = CppTestsSummary()

    # run each cpp bin file
    for cmd in cpp_bins:
        result = subprocess.check_output([cmd])
        result = result.decode("utf-8").rstrip()
        result = result.partition('\n')[0] if len(result) else ""
        print(cmd + " --> " + result)
        cpp_ts.parse_ts(result)

    print("")
    print("# " + ''.join(["="]*76))
    print("# C++ tests summary")
    print("# " + ''.join(["="]*76))
    print("")
    print(f"Successfully tested {cpp_ts.sources} sources with " +
          f"{cpp_ts.implementations} implementations {cpp_ts.tests} tests.")
    print("")
    print("# " + ''.join(["="]*76))
    print("")


if __name__ == "__main__":
    main()
