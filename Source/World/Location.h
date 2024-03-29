#pragma once
#include "Direction.h"

#define directionalLocation(location, direction) Location::getDirectionalLocation(location, direction)

struct Location{
    public:
        Location(int row = 0, int column = 0) : _row(row), _column(column){}
        ~Location(){}

        bool operator<(const Location& location) const;
        bool operator<=(const Location& location) const;
        bool operator>(const Location& location) const;
        bool operator>=(const Location& location) const;
        bool operator==(const Location& location) const;
        bool operator!=(const Location& location) const;

        Location& operator++();
        void operator++(int);
        Location& operator--();
        void operator--(int);
        
        Location operator+(const int& value) const;
        Location operator+(const Location& location) const;
        Location operator-(const int& value) const;
        Location operator-(const Location& location) const;
        Location operator*(const int& value) const;
        Location operator*(const Location& location) const;
        Location operator/(const int& value) const;
        Location operator/(const Location& location) const;
        Location operator%(const int& value) const;
        Location operator%(const Location& location) const;

        static Location getDirectionalLocation(Location location, Direction direction);

        int& row(){return _row;}
        const int& row() const{return _row;}
        int& column(){return _column;}
        const int& column() const{return _column;}
    private:
        int _row;
        int _column;
};

struct RelativeLocation{
    public:
        RelativeLocation(Location regionLocation, Location localLocation) : _regionLocation(regionLocation), _localLocation(localLocation){}
        ~RelativeLocation(){}

        Location& regionLocation(){return _regionLocation;}
        const Location& regionLocation() const{return _regionLocation;}
        Location& localLocation(){return _localLocation;}
        const Location& localLocation() const{return _localLocation;}
    private:
        Location _regionLocation;
        Location _localLocation;
};