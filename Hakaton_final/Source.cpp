#define _CRT_SECURE_NO_WARNINGS

/*#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <deque>
#include <queue>
#include <map>
#include <set>
#include <cstring>
#include <cstdio>
#include <climits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair <ll, ll> pll;
typedef vector <ll> vec;
typedef vector <pll> vecp;
typedef vector <ld> vecd;
typedef vector <vector <ll>> matrix;

const ld PI = 3.141592653589793;
const ld eps = 1e-9;
const ll INF = 1e16;
const ll MOD = 1e9 + 7;

#define pb push_back
#define mp make_pair
#define all(v) v.begin(), v.end()
#define fast_io ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define fixed_out(x) fixed << setprecision(x)

class Point {
private:
    ll x, y;
public:
    Point(ll new_x, ll new_y);
    Point operator=(Point p);
    ll get_x();
    ll get_y();
};

Point::Point(ll new_x, ll new_y) {
    x = new_x;
    y = new_y;
}

Point Point::operator=(Point p) {
    x = p.get_x();
    y = p.get_y();
}

ll Point::get_x() {
    return x;
}

ll Point::get_y() {
    return y;
}

class Markers {
private:
    Point marker_1, marker_2, marker_3, marker_4;
public:
    Markers(Point new_marker_1, Point new_marker_2, Point new_marker_3, Point new_marker_4);
    Point get_marker_1();
    Point get_marker_2();
    Point get_marker_3();
    Point get_marker_4();
};

Markers::Markers(Point new_marker_1, Point new_marker_2, Point new_marker_3, Point new_marker_4) {
    marker_1 = new_marker_1;
    marker_2 = new_marker_2;
    marker_3 = new_marker_3;
    marker_4 = new_marker_4;
}

Point Markers::get_marker_1() {
    return marker_1;
}

Point Markers::get_marker_2() {
    return marker_2;
}

Point Markers::get_marker_3() {
    return marker_3;
}

Point Markers::get_marker_4() {
    return marker_4;
}

class Workspace {
private:
    Markers markers_screen, markers_floor;
    Point robot_screen, robot_floor;
    ld x_coefficient, y_coefficient;
public:
    Workspace();

};

int main() {
    fast_io;

    return 0;
}