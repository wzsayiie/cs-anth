#pragma once

#define clampv(v, min, max) ((v) < (min) ? (min) : ((v) > (max) ? (max) : (v)))

#define minv(a, b)  ((a) < (b) ? (a) : (b))
#define maxv(a, b)  ((a) > (b) ? (a) : (b))
