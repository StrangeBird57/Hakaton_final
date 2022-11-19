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
typedef vector <ll> vec;

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
    Json::Value cmd;
    Markers markers_screen, markers_floor;
    Point robot_screen, robot_floor;
    ld x_coefficient_1, x_coefficient_2, y_coefficient_1, y_coefficient_2;
    ld dist_coefficient_x, dist_coefficient_y;
    vector <Point> targets_screen, targets_floor;
public:
    Workspace() {}
    Workspace(Json::Value);
    void calculate_coefficiet();
    void calculate_robot_floor();
    void calculate_targets_floor();
};

Workspace::Workspace(Json::Value file){
    cmd = file;
    cout << stold(cmd["markers_screen"][0]["x"].asString()) << endl;
    markers_screen = Markers(
        Point(stold(cmd["markers_screen"][0]["x"].asString()), stold(cmd["markers_screen"][0]["y"].asString())),
        Point(stold(cmd["markers_screen"][1]["x"].asString()), stold(cmd["markers_screen"][1]["y"].asString())),
        Point(stold(cmd["markers_screen"][2]["x"].asString()), stold(cmd["markers_screen"][2]["y"].asString())),
        Point(stold(cmd["markers_screen"][3]["x"].asString()), stold(cmd["markers_screen"][3]["y"].asString()))
    );

    markers_floor = Markers(
        Point(stold(cmd["markers_floor"][0]["x"].asString()), stold(cmd["markers_floor"][0]["y"].asString())),
        Point(stold(cmd["markers_floor"][1]["x"].asString()), stold(cmd["markers_floor"][1]["y"].asString())),
        Point(stold(cmd["markers_floor"][2]["x"].asString()), stold(cmd["markers_floor"][2]["y"].asString())),
        Point(stold(cmd["markers_floor"][3]["x"].asString()), stold(cmd["markers_floor"][3]["y"].asString()))
    );

    for (auto elem : cmd["targets_screen"]){
        targets_screen.push_back(Point(stod(elem["x"].asString()), stod(elem["y"].asString())));
    }

    robot_screen = Point(stold(cmd["robot_screen"][0]["x"].asString()), stold(cmd["robot_screen"][0]["y"].asString()));
}

void Workspace::calculate_coefficiet() {
    x_coefficient_1 = markers_screen.get_marker_1().get_x() / markers_floor.get_marker_1().get_x();
    x_coefficient_2 = markers_screen.get_marker_2().get_x() / markers_floor.get_marker_2().get_x();
    y_coefficient_1 = markers_screen.get_marker_1().get_y() / markers_floor.get_marker_1().get_y();
    y_coefficient_2 = markers_screen.get_marker_4().get_y() / markers_floor.get_marker_4().get_y();
    dist_coefficient_x = (robot_screen.get_x() - markers_screen.get_marker_1().get_x()) / (markers_screen.get_marker_2().get_x() - markers_screen.get_marker_1().get_x());
    dist_coefficient_y = (robot_screen.get_y() - markers_screen.get_marker_1().get_y()) / (markers_screen.get_marker_4().get_y() - markers_screen.get_marker_1().get_y());
}

void Workspace::calculate_robot_floor() {
    ld robot_floor_x = robot_screen.get_x() * (x_coefficient_1 + x_coefficient_2) * dist_coefficient_x;
    ld robot_floor_y = robot_screen.get_y() * (y_coefficient_1 + y_coefficient_2) * dist_coefficient_y;
    Point tmp(robot_floor_x, robot_floor_y);
    robot_floor = tmp;
}

void Workspace::calculate_targets_floor() {
    targets_floor.resize(targets_screen.size());
    for (int i = 0; i < targets_screen.size(); ++i) {
        ld target_floor_x = robot_screen.get_x() * (x_coefficient_1 + x_coefficient_2) * dist_coefficient_x;
        ld target_floor_y = robot_screen.get_y() * (y_coefficient_1 + y_coefficient_2) * dist_coefficient_y;
        Point target_floor(target_floor_x, target_floor_y);
        targets_floor[i] = target_floor;
    }
}

class InputHandler {
public:
    InputHandler();
};

InputHandler::InputHandler(){
    Json::Value cmd;
    cmd_file >> cmd;
    if (cmd["cmd"] == "left") {
        cout << "levo" << endl; // debug
        ld val = stold(cmd["val"].asString());
    }
    if (cmd["cmd"] == "right") {
        cout << "pravo" << endl; // debug
        ld val = stold(cmd["val"].asString());
    }
    if (cmd["cmd"] == "forward") {
        cout << "vpered" << endl; // debug
        ld val = stold(cmd["val"].asString());
    }
    if (cmd["cmd"] == "back") {
        cout << "zad" << endl; // debug
        ld val = stold(cmd["val"].asString());
    }
    if (cmd["cmd"] == "stop") {
        cout << "hare" << endl; // debug
    }
    if (cmd["cmd"] == "auto") {
        cout << "rabota" << endl; // debug
        Workspace w(cmd);
    }
}

int main() {
    InputHandler();
    return 0;
}