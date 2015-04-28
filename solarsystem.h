#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include "patch.h"

const float PI = 3.14159;
const float PI_double = PI * 2.0f;
const float days_a_year = 365.0f;
const float days_a_month = 28.0f;
const float days_a_year_mercury = 88.0f;
const float days_a_year_venus = 224.7f;
const float sun_spin_x = 180.0f;
const float earth_to_sun_distance = 8.0f; // 地球離太陽的假設值
const float mercury_to_sun_distance = 3.0f; // 水星離太陽的假設值
const float venus_to_sun_distance = 5.0f; // 水星離太陽的假設值
const float moon_to_earth_distance = 2.0f; // 月球離地球的假設值
const float simulation_speed = 60.0f; // 1秒相當於60天


class solarsystem
{
public:
    solarsystem();
    void draw();


private:

    Geometry* geom;
    Patch* sun;
    Patch* earth;

    int g_iNumSphereVertices;
    int g_iNumSphereTriangles;
    int g_iNumSphereIndices;

    bool CreateSphere(float radius, Patch* patch,  Geometry* geom, float *color=NULL, int stacks = 20, int pieces = 20);


};

#endif // SOLARSYSTEM_H
