#pragma once

#include "math.h"
#include "stdint.h"

//compare.
static inline int imax(int x, int y) { return x > y ? x : y; }
static inline int imin(int x, int y) { return x < y ? x : y; }

//vectors:
typedef union _u_VDOUBLE2 VDOUBLE2;
typedef union _u_VDOUBLE3 VDOUBLE3;
typedef union _u_VDOUBLE4 VDOUBLE4;

union _u_VDOUBLE2 {
    struct {
        double x;
        double y;
    };
    double p[2];
};
union _u_VDOUBLE3 {
    struct {
        union { double x; double r; };
        union { double y; double g; };
        union { double z; double b; };
    };
    double p[3];
};
union _u_VDOUBLE4 {
    struct {
        union { double x; double r; };
        union { double y; double g; };
        union { double w; double b; };
        union { double h; double a; };
    };
    double p[4];
};

typedef union _u_VINT2 VINT2;
typedef union _u_VINT3 VINT3;
typedef union _u_VINT4 VINT4;

union _u_VINT2 {
    struct {
        int x;
        int y;
    };
    int p[2];
};
union _u_VINT3 {
    struct {
        union { int x; int r; };
        union { int y; int g; };
        union { int z; int b; };
    };
    int p[3];
};
union _u_VINT4 {
    struct {
        union { int x; int r; };
        union { int y; int g; };
        union { int w; int b; };
        union { int h; int a; };
    };
    int p[4];
};
