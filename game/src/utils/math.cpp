#include "math.h"

MATH_MAT3_r64 math_matrix_identity_multiple(const r64 scalar)
{
    return
    {
        scalar * (r64)1,          (r64)0, (r64)0,
                 (r64)0,  scalar * (r64)1, (r64)0,
                 (r64)0,          (r64)0, scalar * (r64)1
    };
}

MATH_MAT3_r64 math_matrix_product(const MATH_MAT3_r64& m1, const MATH_MAT3_r64& m2) // m1 * m2
{
    const MATH_VEC3_r64 res_m1_col1 = { m1.a11, m1.a21, m1.a31 };
    const MATH_VEC3_r64 res_m1_col2 = { m1.a12, m1.a22, m1.a32 };
    const MATH_VEC3_r64 res_m1_col3 = { m1.a13, m1.a23, m1.a33 };

    const MATH_VEC3_r64 res_m2_row1 = { m2.a11, m2.a12, m2.a13 };
    const MATH_VEC3_r64 res_m2_row2 = { m2.a21, m2.a22, m2.a23 };
    const MATH_VEC3_r64 res_m2_row3 = { m2.a31, m2.a32, m2.a33 };

    const r64 res_m11 = math_dot_product_3d(res_m1_col1, res_m2_row1);
    const r64 res_m12 = math_dot_product_3d(res_m1_col1, res_m2_row2);
    const r64 res_m13 = math_dot_product_3d(res_m1_col1, res_m2_row3);

    const r64 res_m21 = math_dot_product_3d(res_m1_col2, res_m2_row1);
    const r64 res_m22 = math_dot_product_3d(res_m1_col2, res_m2_row2);
    const r64 res_m23 = math_dot_product_3d(res_m1_col2, res_m2_row3);

    const r64 res_m31 = math_dot_product_3d(res_m1_col3, res_m2_row1);
    const r64 res_m32 = math_dot_product_3d(res_m1_col3, res_m2_row2);
    const r64 res_m33 = math_dot_product_3d(res_m1_col3, res_m2_row3);

    return {
        res_m11, res_m12, res_m13,
        res_m21, res_m22, res_m23,
        res_m31, res_m32, res_m33
    };
}

MATH_MAT3_r64 math_matrix_addition(const MATH_MAT3_r64& m1, const MATH_MAT3_r64& m2)
{
    return
    {
        m1.a11 + m2.a11, m1.a12 + m2.a12, m1.a13 + m2.a13,
        m1.a21 + m2.a21, m1.a22 + m2.a22, m1.a23 + m2.a23,
        m1.a31 + m2.a31, m1.a32 + m2.a32, m1.a33 + m2.a33
    };
}

void math_matrix_display(const MATH_MAT3_r64& m)
{
    using namespace std;
    cout << "\n\n";
    cout << m.a11 << " " << m.a12 << " " << m.a13 << "\n";
    cout << m.a21 << " " << m.a22 << " " << m.a23 << "\n";
    cout << m.a31 << " " << m.a32 << " " << m.a33 << "\n";
    cout << "\n\n";
}

r64 math_dot_product_3d(const MATH_VEC3_r64& v1, const MATH_VEC3_r64& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

r32 math_dot_product_3d(const MATH_VEC3_r32& v1, const MATH_VEC3_r32& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

r64 math_dot_product_2d(const MATH_VEC2_r64& v1, const MATH_VEC2_r64& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

r32 math_dot_product_2d(const MATH_VEC2_r32& v1, const MATH_VEC2_r32& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

