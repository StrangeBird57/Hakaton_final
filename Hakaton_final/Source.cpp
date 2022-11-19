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

class BotOperation {
private:
    string way;
    ld time;
public:
    BotOperation();
    BotOperation(string new_way, ld new_time = 0);
    void print_data();
};

BotOperation::BotOperation() {
    way = "stop";
    time = 0;
}

BotOperation::BotOperation(string new_way, ld new_time = 0) {
    way = new_way;
    time = new_time;
}

void BotOperation::print_data() {
    cout << way << " " << time << "\n";
}

class Workspace {
private:
    Markers markers_screen, markers_floor;
    Point robot_screen, robot_floor;
    ld x_coefficient_1, x_coefficient_2, y_coefficient_1, y_coefficient_2;
    ld dist_coefficient_x, dist_coefficient_y;
    vector <Point> targets_screen, targets_floor;
public:
    Workspace();
    void calculate_coefficiet();
    void calculate_robot_floor();
    void calculate_targets_floor();
    Point get_robot();
    vector <Point> get_targets();
};

Workspace::Workspace(){
    Json::Value cmd;
    cmd_file >> cmd;
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

Point Workspace::get_robot() {
    return robot_floor;
}

vector <Point> Workspace::get_targets() {
    return targets_floor;
}

class Work {
private:
    Point robot_start, robot_test;
    vector <Point> targets;
public:
    Work();
    void process();
};

Work::Work() {
    Workspace start;
    BotOperation test_go("forward", 1);
    BotOperation test_back("back", 1);
    test_go.print_data();
    Workspace test;
    test_back.print_data();
    robot_start = start.get_robot();
    robot_test = test.get_robot();
    targets = start.get_targets();
}

void Work::process() {
    //Line first(robot_start, robot_test), second(robot_start, targets[0]);
    //ld angle = get_angle(first, second);
    //ld get_dist(robot_start, targets[0])
    //ld time_rotate = calculate_time_by_angle(angle);
    //ld time_move = calculate_time_by_dist(dist);
    //BotOperation rotate("left", time_rotate), move("forward", time_move), back("back", time_move);
    for (int i = 1; i < targets.size(); ++i) {
        //Line first(robot_start, targets[i - 1]), second(robot_start, targets[i]);
        //ld angle = get_angle(first, second);
        //ld get_dist(robot_start, targets[i])
        //ld time_rotate = calculate_time_by_angle(angle);
        //ld time_move = calculate_time_by_dist(dist);
        //BotOperation rotate("left", time_rotate), move("forward", time_move), back("back", time_move);
    }
}

int main() {
    return 0;
}
