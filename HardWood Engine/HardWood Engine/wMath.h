#pragma once

/*
* Description - This header is to define all math functions that are used in graphics and 3D math. Simply a math header
* 
* Author - Kody Wood
* 
*/

// Defines
#ifndef WMATH_H
#define WMATH_H

#include <string.h>
#include <iostream>
#include <math.h>

#ifdef WMATH_NO_INLINE
#define WMATH_H_FUNC static
#else
#define WMATH_H_FUNC static inline
#endif // WMATH_NO_INLINE

#define WMATH_H_DEFINE_VEC(n)\
/*Define new vector types of size(n)*/\
typedef float vec##n[n];\
\
/* Scalar Multiplication */\
WMATH_H_FUNC void vec##n##_scale(vec##n ret, const vec##n a, const float b)\
{\
	for(int i = 0; i < n; ++i)\
	{\
		ret[i] = a[i] * b;\
	}\
}\
/* Scalar Division */\
WMATH_H_FUNC void vec##n##_scaleDiv(vec##n ret, const vec##n a, const float b)\
{\
	float s = 1.0f/b;\
	for(int i = 0; i < n; ++i)\
	{\
		ret[i] = a[i] * s;\
	}\
}\
/* Negate */\
WMATH_H_FUNC void vec##n##_negate(vec##n ret, const vec##n a)\
{\
	for(int i = 0; i < n; ++i)\
	{\
		ret[i] = a[i] * -1;\
	}\
}\
/* Magnitude */\
WMATH_H_FUNC float vec##n##_magnitude(const vec##n a)\
{\
	float b = 0.0f;\
	for(int i =0; i<n;++i)\
	{\
		b += a[i]*a[i];\
	}\
	return sqrt(b);\
}\
/* Normalize */\
WMATH_H_FUNC void vec##n##_normalize(vec##n ret, const vec##n a)\
{\
	float s = 1.0f / vec##n##_len(a);\
	vec##n##_scale(ret,a,s);\
}\
/* Multiplication Inner - Used for Normalizing */\
WMATH_H_FUNC float vec##n##_mulInner(const vec##n a, const vec##n b)\
{\
	float r = 0.0f;\
	for(int i = 0; i < n;++i)\
	{\
		r += b[i]*a[i];\
	}\
	return r;\
}\
/* Length - Used for Normalizing - Same as calling _magnitude */\
WMATH_H_FUNC float vec##n##_len(const vec##n a)\
{ \
	return sqrtf(vec##n##_mulInner(a,a));\
} \
/* Add */\
WMATH_H_FUNC void vec##n##_add(vec##n ret, const vec##n a, const vec##n b)\
{\
	for(int i = 0; i < n; ++i)\
	{\
		ret[i]=a[i]+b[i];\
	}\
}\
/* Sub */\
WMATH_H_FUNC void vec##n##_sub(vec##n ret, const vec##n a, const vec##n b)\
{\
	for(int i = 0; i < n; ++i)\
	{\
		ret[i]=a[i]-b[i];\
	}\
}\
/* Multiplication */\
WMATH_H_FUNC float vec##n##_mul(vec##n ret, const vec##n a, const vec##n b)\
{\
	for(int i = 0; i < n;++i)\
	{\
		ret[i] = b[i]*a[i];\
	}\
}\
/* Division */\
WMATH_H_FUNC float vec##n##_div(vec##n ret, const vec##n a, const vec##n b)\
{\
	for(int i = 0; i < n;++i)\
	{\
		float s=1.0f/b[i];\
		ret[i] = a[i]*s;\
	}\
}\
/* print */\
WMATH_H_FUNC void vec##n##_print(vec##n a)\
{\
	std::cout<< "Vector" << ##n << ": ";\
	for(int i = 0; i < n; ++i)\
	{\
		std::cout<< a[i] << " ";\
	}\
	std::cout<< std::endl;\
}\

//Defining Vector2, Vector3 and Vector4 types
WMATH_H_DEFINE_VEC(2);
WMATH_H_DEFINE_VEC(3);
WMATH_H_DEFINE_VEC(4);




//------------------------- MATRIX 3X3 --------------------------------//

typedef vec3 mat3[3];
#define MAT3IDENTITY { 1, 0, 0, \
                       0, 1, 0, \
                       0, 0, 1  }

WMATH_H_FUNC void mat3_identity(mat3 ret)
{
	//TODO
}

WMATH_H_FUNC void mat3_add(mat3 ret, const mat3 A, const mat3 B)
{
	for (int i = 0; i < 3; ++i)
	{
		vec3_add(ret[i],A[i],B[i]);
	}
}
WMATH_H_FUNC void mat3_sub(mat3 ret, const mat3 A, const mat3 B)
{
	for (int i = 0; i < 3; ++i)
	{
		vec3_sub(ret[i], A[i], B[i]);
	}
}
WMATH_H_FUNC void mat3_scale(mat3 ret, const mat3 A, const float s)
{
	for (int i = 0; i < 3; ++i)
	{
		vec3_scale(ret[i], A[i], s);
	}
}


//------------------------- MATRIX 4X4 --------------------------------//

typedef vec4 mat4[4];
#define MAT4IDENTITY { {1, 0, 0, 0}, \
                       {0, 1, 0, 0}, \
                       {0, 0, 1, 0}, \
                       {0, 0, 0, 1}  }

/* Set Mat4 based on 4 vectors */
WMATH_H_FUNC void mat4_set(mat4 ret, const vec4 a, const vec4 b, const vec4 c, const vec4 d)
{
	ret[0][0] = a[0]; ret[1][0] = a[1]; ret[2][0] = a[2]; ret[3][0] = a[3];
	ret[0][1] = b[0]; ret[1][1] = b[1]; ret[2][1] = b[2]; ret[3][1] = b[3];
	ret[0][2] = c[0]; ret[1][2] = c[1]; ret[2][2] = c[2]; ret[3][2] = c[3];
	ret[0][3] = d[0]; ret[1][3] = d[1]; ret[2][3] = d[2]; ret[3][3] = d[3];
}

WMATH_H_FUNC void mat4_identity(mat4 ret)
{
	//TODO
}

WMATH_H_FUNC void mat4_add(mat4 ret, const mat4 A, const mat4 B)
{
	for (int i = 0; i < 4; i++)
	{
		vec4_add(ret[i], A[i], B[i]);
	}
}

WMATH_H_FUNC void mat4_sub(mat4 ret, const mat4 A, const mat4 B)
{
	for (int i = 0; i < 4; i++)
	{
		vec4_sub(ret[i], A[i], B[i]);
	}
}


/* --- TODO ---
* - Add
* - Sub
* -
*/


#endif //WMATH_H