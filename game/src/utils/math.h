#ifndef MATH_H
#define MATH_H

#include <iostream>

/* A C-style mini math library */

#include "../defines.h"

struct MATH_MAT3_r64;

struct MATH_VEC3_r64;
struct MATH_VEC2_r64;

struct MATH_VEC3_r32;
struct MATH_VEC2_r32;

extern MATH_MAT3_r64 math_matrix_identity_multiple(const r64 scalar = (r64)1);
extern MATH_MAT3_r64 math_matrix_product(const MATH_MAT3_r64& m1, const MATH_MAT3_r64& m2);
extern MATH_MAT3_r64 math_matrix_addition(const MATH_MAT3_r64& m1, const MATH_MAT3_r64& m2);

extern void math_matrix_display(const MATH_MAT3_r64& m1);

extern r64 math_dot_product_3d(const MATH_VEC3_r64& v1, const MATH_VEC3_r64& v2);
extern r32 math_dot_product_3d(const MATH_VEC3_r32& v1, const MATH_VEC3_r32& v2);

extern r64 math_dot_product_2d(const MATH_VEC2_r64& v1, const MATH_VEC2_r64& v2);
extern r32 math_dot_product_2d(const MATH_VEC2_r32& v1, const MATH_VEC2_r32& v2);

struct MATH_MAT3_r64 {
	r64 a11, a12, a13,
		a21, a22, a23,
		a31, a32, a33;
};

struct MATH_VEC3_r64
{
	r64 x, y, z;
};
struct MATH_VEC2_r64
{
	r64 x, y;
};
struct MATH_VEC3_r32
{
	r32 x, y, z;
};
struct MATH_VEC2_r32
{
	r32 x, y;
};


#endif // !MATH_H

