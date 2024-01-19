#pragma once
#include <BearLibTerminal.h>
#include "Location.h"

struct Light{
    public:
        Light(Location source, color_t color, float intensity, float range) : _source(source), _color(color), _intensity(intensity), _range(range){}
        ~Light(){}

        Location& source(){return _source;}
        const Location& source() const{return _source;}
        color_t& color(){return _color;}
        const color_t& color() const{return _color;}
        float& intensity(){return _intensity;}
        const float& intensity() const{return _intensity;}
        float& range(){return _range;}
        const float& range() const{return _range;}
    private:
        Location _source;
        color_t _color;
        float _intensity;
        float _range;
};