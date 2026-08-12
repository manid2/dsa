#pragma once

#include <bits/stdc++.h>

using namespace std;

/* =============================================================================
 * Common Type Definitions & Macros
 * =============================================================================
 */
// clang-format off
#define FOR_I2N_(i, n, type) for (type i = 0; i < (n); i++)
#define FOR_N2I_(i, n, type) for (type i = (n); i >= 0; i--)
// clang-format on

#define fii(i, n) FOR_I2N_(i, (n), int)
#define fsi(i, n) FOR_I2N_(i, (n), size_t)
#define frii(i, n) FOR_N2I_(i, (n), int)
#define frsi(i, n) FOR_N2I_(i, (n), size_t)

#define vi_t vector<int>
#define vi2_t vector<vi_t>
#define umi_t unordered_map<int, int>
#define pii_t pair<int, int>
#define vpi_t vector<pii_t>
#define v2pi_t vector<vpi_t>

#define vi_v(v, n, i) vi_t v((n), (i))
#define vi2_v(v, n, i) vi2_t v((n), vi_t((n), (i)))

/* =============================================================================
 * Common Output Streams & Utilities
 * =============================================================================
 */
template <class T>
inline ostream &operator<<(ostream &out, const pair<T, T> &p) {
  out << "{" << format("{}, {}", p.first, p.second) << "}";
  return out;
}

template <class T>
inline ostream &operator<<(ostream &out, const vector<T> &c) {
  out << "{";
  for (int i = 0; const auto &e : c)
    out << (i++ ? ", " : "") << e;
  out << "}";
  return out;
}

template <class T>
inline ostream &operator<<(ostream &out, const vector<vector<T>> &c) {
  out << "{";
  for (int i = 0; const auto &e : c)
    out << (i++ ? ", " : "") << e;
  out << "}";
  return out;
}

template <class T> inline string to_string(const vector<T> &c) {
  ostringstream oss;
  oss << c;
  return oss.str();
}

inline string to_string(const string &s) {
  string q("\"");
  return q + s + q;
}
