/**
 * Given a vector of strings representing unsigned numbers, convert the
 * numbers to a collection of std::uint16_t in which the odd numbers appear
 * before the even ones and output the data
 */


#include <bits/stdc++.h>

using namespace std;

auto input = std::vector<std::string>{
    "9", "0", "49", "2", "100", "not a number", "12 not a number too"};

bool is_number(const std::string &s)
{
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

std::vector<std::uint16_t>
getOddEvenNums(const std::vector<std::string> &input)
{
	std::vector<std::uint16_t> oen;
	for (auto &a : input) {
		std::uint16_t d = 0;
		try {
			if (is_number(a)) {
				d = static_cast<std::uint16_t>(std::stoul(a));
				oen.push_back(d);
			}
		} catch (std::invalid_argument const &ex) {
			std::cout
			    << "std::invalid_argument::what(): " << ex.what()
			    << '\n';
		} catch (std::out_of_range const &ex) {
			std::cout
			    << "std::out_of_range::what(): " << ex.what()
			    << '\n';
		}
	}

	std::size_t s = 0;
	std::size_t e = oen.size() - 1;
	while (s < e) {
		while (oen.at(s) % 2 == 0 && s < e) s++;
		while (oen.at(e) % 2 != 1 && s < e) e--;
		// similar to bubble sort swap odd & even numbers
		if (s < e) {
			std::swap(oen.at(s), oen.at(e));
			s++;
			e--;
		}
	}
	return oen;
}

int main(int, char **)
{
	std::vector<std::uint16_t> oen = getOddEvenNums(input);
	for (auto &a : oen) { std::cout << a << " "; }
	return 0;
}
