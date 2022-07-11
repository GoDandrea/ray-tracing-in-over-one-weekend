#ifndef BODY_H
#define BODY_H

#include "ray.h"

struct hit_record {
    point3 p;
    vec3 normal;
    double t;
};

class body {
    public:
        virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec)
            const = 0;
};

#endif
