#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <chrono>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define MIN_PLAYERS_NUMBER 2
#define MAX_PLAYERS_NUMER 4

#define CLOCK_NOW std::chrono::system_clock::now
typedef std::chrono::duration<double> ElapsedTime;
typedef std::chrono::system_clock::time_point Moment;

struct Time
{
    Moment begin;
    Moment end;

    double calculateDuration() const
    {
        ElapsedTime duration = end - begin;
        return duration.count();
    }
};

struct Size
{
    int w;
    int h;

    Size operator+(const Size &_size) const
    {
        Size res = {w + _size.w, h + _size.h};
        return res;
    }
    Size operator-(const Size &_size) const
    {
        Size res = {w - _size.w, h - _size.h};
        return res;
    }
    Size operator*(const int &_num) const
    {
        Size res = {w * _num, h * _num};
        return res;
    }
    Size operator/(const int &_num) const
    {
        if (_num == 0)
        {
            std::cout << "Divide by zero error." << std::endl;
            exit(0);
        }
        Size res = {w / _num, h / _num};
        return res;
    }
};

struct Coordinate
{
    int x;
    int y;

    Coordinate operator+(const Size &_size) const
    {
        Coordinate res = {x + _size.w, y + _size.h};
        return res;
    }
    Coordinate operator-(const Size &_size) const
    {
        Coordinate res = {x - _size.w, y - _size.h};
        return res;
    }
    Coordinate operator+(const Coordinate &_other) const
    {
        Coordinate res = {x + _other.x, y + _other.y};
        return res;
    }
    Coordinate operator-(const Coordinate &_other) const
    {
        Coordinate res = {x - _other.x, y - _other.y};
        return res;
    }
    Coordinate operator*(const int &_num) const
    {
        Coordinate res = {x * _num, y * _num};
        return res;
    }
    Coordinate operator/(const int &_num) const
    {
        if (_num == 0)
        {
            std::cout << "Divide by zero error." << std::endl;
            exit(0);
        }
        Coordinate res = {x / _num, y / _num};
        return res;
    }
    bool operator==(const Coordinate &_other) const
    {
        return (x == _other.x && y ==_other.y);
    }
    double calculateNorm() const
    {
        return sqrt(pow(x, 2) + pow(y, 2));
    }
    void calculateAngle(double &_angle) const
    {
        if (!(x == 0 && y == 0))
        {
            double norm = this->calculateNorm();
            _angle = acos(x / norm);
            if (y < 0)
            {
                _angle = -_angle;
            }
        }
    }
    double calculateAngle() const
    {
        if (!(x == 0 && y == 0))
        {
            double norm = this->calculateNorm();
            double angle = acos(x / norm);
            if (y < 0)
            {
                return -angle;
            }
            else
            {
                return angle;
            }
        }
        else
        {
            return 0.0;
        }
    }
};

struct MovementControl
{
    unsigned char up;
    unsigned char down;
    unsigned char left;
    unsigned char right;
};

struct ShootingControl
{
    unsigned char p1;
    unsigned char p2;
    unsigned char p3;
    unsigned char p4;
};

enum Side
{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    TOTAL_SIDES
};

enum ObjectType
{
    BARRIER,
    ROCKET,
    TRACKER,
    SPACESHIP,
    TOTAL_TYPES,
    NONE_TYPE
};

enum Player
{
    PLAYER_1,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4,
    TOTAL_PLAYERS,
    NONE_PLAYER
};

enum Sound
{
    EXPLOSION_SOUND,
    TRACKED_SOUND,
    BUTTON_SOUND,
    TOTAL_SOUNDS,
    NONE_SOUND
};

enum Music
{
    CHASING_MUSIC,
    TOTAL_MUSICS
};

enum ButtonType
{
    START_BUTTON,
    RESTART_BUTTON,
    RESUME_BUTTON,
    GUIDE_BUTTON,
    EXIT_BUTTON,
    TWO_PLAYER_BUTTON,
    THREE_PLAYER_BUTTON,
    FOUR_PLAYER_BUTTON,
    TOTAL_BUTTONS
};

enum Status
{
    BEGIN_STATUS,
    RUNNING_STATUS,
    PAUSE_STATUS,
    END_STATUS,
    GUIDE_STATUS,
    EXIT_STATUS,
    NONE_STATUS
};

