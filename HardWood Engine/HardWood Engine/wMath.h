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
/* Magnitude */\
WMATH_H_FUNC float vec##n##_mag(const vec##n a)\
{\
	float b = 0.0f;\
	for(int i =0; i<n;++i)\
	{\
		b += a[i]*a[i];\
	}\
	return sqrt(b);\
}\
/* Scalar Multiplication */\
WMATH_H_FUNC void vec##n##_scale(vec##n ret, const vec##n a, const float b)\
{\
	for(int i = 0; i < n; ++i)\
	{\
		ret[i] = a[i] * b;\
	}\
}\
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

typedef vec3 mat3[3];
#define MAT3IDENTITY { 1, 0, 0, \
                       0, 1, 0, \
                       0, 0, 1  }

WMATH_H_FUNC void mat3_identity(mat3 ret)
{
	mat3 identity = MAT3IDENTITY;
	ret = identity;
}


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

/* --- TODO ---
* - Add
* - Sub
* -
*/


#endif //WMATH_H