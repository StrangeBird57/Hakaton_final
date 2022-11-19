#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <json/json.h>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
ifstream cmd_file("abot/command.json", ifstream::binary);

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
    ld x, y;
public:
    Point();
    Point(ld new_x, ld new_y);
    Point operator=(Point p);
    ld get_x();
    ld get_y();
};

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(ld new_x, ld new_y) {
    x = new_x;
    y = new_y;
}

Point Point::operator=(Point p) {
    x = p.get_x();
    y = p.get_y();
    return *this;
}

ld Point::get_x() {
    return x;
}

ld Point::get_y() {
    return y;
}

class Markers {
private:
    Point marker_1, marker_2, marker_3, marker_4;
public:
    Markers();
    Markers(Point new_marker_1, Point new_marker_2, Point new_marker_3, Point new_marker_4);
    Point get_marker_1();
    Point get_marker_2();
    Point get_marker_3();
    Point get_marker_4();
};

Markers::Markers(){
    Point p(0, 0);
    marker_1 = p;
    marker_2 = p;
    marker_3 = p;
    marker_4 = p;
}

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
    ld x_coefficient_1, x_coefficient_2, y_coefficient_1, y_coefficient_2;
public:
    Workspace();
    void calculate_coefficiet();
    void calculate_robot_floor();

};

Workspace::Workspace(){
    Json::Value cmd;
    cmd_file >> cmd;

    markers_screen = Markers(
        Point(stold(cmd["markers_screen"][0]["x"].asString()), stold(cmd["markers_screen"][0]["y"].asString())),
        Point(stold(cmd["markers_screen"][1]["x"].asString()), stold(cmd["markers_screen"][0]["y"].asString())),
        Point(stold(cmd["markers_screen"][2]["x"].asString()), stold(cmd["markers_screen"][0]["y"].asString())),
        Point(stold(cmd["markers_screen"][3]["x"].asString()), stold(cmd["markers_screen"][0]["y"].asString()))
    );

    markers_floor = Markers(
        Point(stold(cmd["markers_floor"][0]["x"].asString()), stold(cmd["markers_floor"][0]["y"].asString())),
        Point(stold(cmd["markers_floor"][1]["x"].asString()), stold(cmd["markers_floor"][0]["y"].asString())),
        Point(stold(cmd["markers_floor"][2]["x"].asString()), stold(cmd["markers_floor"][0]["y"].asString())),
        Point(stold(cmd["markers_floor"][3]["x"].asString()), stold(cmd["markers_floor"][0]["y"].asString()))
    );

    robot_screen = Point(stold(cmd["robot_screen"]["x"].asString()), stold(cmd["robot_screen"]["x"].asString()));
}

void Workspace::calculate_coefficiet() {
    x_coefficient_1 = markers_screen.get_marker_1().get_x() / markers_floor.get_marker_1().get_x();
    x_coefficient_2 = markers_screen.get_marker_2().get_x() / markers_floor.get_marker_2().get_x();
    y_coefficient_1 = markers_screen.get_marker_1().get_y() / markers_floor.get_marker_1().get_y();
    y_coefficient_2 = markers_screen.get_marker_4().get_y() / markers_floor.get_marker_4().get_y();
}

void Workspace::calculate_robot_floor() {
    ld robot_floor_x = 0, robot_floor_y = 0;

    robot_floor = { robot_floor_x, robot_floor_y };
}

int main() {
    fast_io;

    return 0;
}