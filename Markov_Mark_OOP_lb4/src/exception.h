#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>


class GameFieldException : public std::invalid_argument {
public: 
    GameFieldException(const char* msg) : std::invalid_argument(msg) {}
};

class OutOfBoundsException : public GameFieldException {
public:
    explicit OutOfBoundsException(const char* msg, int width_field, int height_field) : 
    GameFieldException(msg), width_field_state(width_field), height_field_state(height_field) {}
    int get_height_state() {return height_field_state; }
    int get_width_state() {return width_field_state; }
private:
    int height_field_state;
    int width_field_state;
};

class OrientationShipException : public GameFieldException {
public:
    explicit OrientationShipException(const char* msg) : GameFieldException(msg) {}
};

class InvalidShipPlacementException : public GameFieldException {
public:
    explicit InvalidShipPlacementException(const char* msg, int coordinate_occupied_cell_x, int coordinate_occupied_cell_y) : 
    GameFieldException(msg), coordinate_occupied_cell_x(coordinate_occupied_cell_x), coordinate_occupied_cell_y(coordinate_occupied_cell_y) {}
    int get_y_state() {return coordinate_occupied_cell_y; }
    int get_x_state() {return coordinate_occupied_cell_x; }
private:
    int coordinate_occupied_cell_x;
    int coordinate_occupied_cell_y;
};

class NoAbilitiesException : public GameFieldException {
public:
    explicit NoAbilitiesException(const char* msg) : GameFieldException(msg) {}
};

#endif