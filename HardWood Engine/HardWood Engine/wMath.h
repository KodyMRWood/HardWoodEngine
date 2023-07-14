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
/* Normalize */\
WMATH_H_FUNC void vec##n##_normalize(vec##n ret, const vec##n a)\
{\
	float s = 1.0f / vec##n##_len(a);\
	vec##n##_scale(ret,a,s);\
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
/* Multiplication */\
WMATH_H_FUNC void vec##n##_mul(vec##n ret, const vec##n a, const vec##n b)\
{\
	for(int i = 0; i < n;++i)\
	{\
		ret[i] = b[i]*a[i];\
	}\
}\
/* Division */\
WMATH_H_FUNC void vec##n##_div(vec##n ret, const vec##n a, const vec##n b)\
{\
	for(int i = 0; i < n;++i)\
	{\
		float s=1.0f/b[i];\
		ret[i] = a[i]*s;\
	}\
}\
/* Dot Product */\
WMATH_H_FUNC float vec##n##_dot(const vec##n a, const vec##n b)\
{\
	float ret = 0.0f;\
	for(int i = 0; i < n; ++i)\
	{\
		ret += a[i] * b[i];\
	}\
	return ret; \
}\
WMATH_H_FUNC float vec##n##_dotWithAngle(const vec##n a, const vec##n b, const float angle)\
{\
	float ret = 0.0f;\
	ret = vec##n##_magnitude(a) * vec##n##_magnitude(b) * cos(angle);\
	return ret;\
}\
/* Duplicate */\
WMATH_H_FUNC void vec##n##_dup(vec##n ret, const vec##n a)\
{\
	for(int i = 0; i < n;++i)\
	{\
		ret[i] = a[i];\
	}\
}\
/* print */\
WMATH_H_FUNC void vec##n##_print(const vec##n a)\
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

//------------------------- Vector 3 --------------------------------//
WMATH_H_FUNC void vec3_cross(vec3 ret, const vec3 a, const vec3 b)
{
	ret[0] = { a[1] * b[2] - a[2] * b[1] };
	ret[1] = { a[2] * b[0] - a[0] * b[2] };
	ret[2] = { a[0] * b[1] - a[1] * b[0] };
}
//Used for area of a parallelipiped
WMATH_H_FUNC float vec3_scalar_triple_product(const vec3 a, const vec3 b, const vec3 c)
{
	vec3 ret = { 0,0,0 };
	vec3_cross(ret, a, b);
	return vec3_dot(ret,c);
}

//------------------------- Vector 4 --------------------------------//
WMATH_H_FUNC void vec4_cross(vec4 ret, const vec4 a, const vec4 b)
{
	ret[0] = { a[1] * b[2] - a[2] * b[1] };
	ret[1] = { a[2] * b[0] - a[0] * b[2] };
	ret[2] = { a[0] * b[1] - a[1] * b[0] };
	ret[3] = { 1.0f};
}
WMATH_H_FUNC float vec4_scalar_triple_product(const vec4 a, const vec4 b, const vec4 c)
{
	vec4 ret = { 0,0,0,0 };
	vec4_cross(ret, a, b);
	return vec4_dot(ret, c);
}

//------------------------- MATRIX 3X3 --------------------------------//

typedef vec3 mat3[3];
#define MAT3IDENTITY { 1, 0, 0, \
                       0, 1, 0, \
                       0, 0, 1  }

WMATH_H_FUNC void mat3_identity(mat3 ret)
{

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
WMATH_H_FUNC void mat3_dup(mat3 ret, const mat3 A)
{
	for (int i = 0; i < 3; ++i)
	{
		vec3_dup(ret[i], A[i]);
	}
}
WMATH_H_FUNC void mat3_mul(mat3 ret, const mat3 A, const mat3 B)
{
	mat3 temp;
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			temp[row][col] = 0.0f;
			for (int k = 0; k < 3; ++k)
			{
				temp[row][col] += A[row][k] * B[k][col];
			}
		}
	}
	mat3_dup(ret,temp);
}
WMATH_H_FUNC void mat3_print(const mat3 A)
{
	for (int i = 0; i < 3; ++i)
	{
		vec3_print(A[i]);
	}
	std::cout << std::endl;
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
WMATH_H_FUNC void mat4_scale(mat4 ret, const mat4 A, const float s)
{
	for (int i = 0; i < 4; ++i)
	{
		vec4_scale(ret[i], A[i], s);
	}
}
WMATH_H_FUNC void mat4_dup(mat4 ret, const mat4 A)
{
	for (int i = 0; i < 4; ++i)
	{
		vec4_dup(ret[i], A[i]);
	}
}
WMATH_H_FUNC void mat4_mul(mat4 ret, const mat4 A, const mat4 B)
{
	mat4 temp;
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			temp[row][col] = 0.0f;
			for (int k = 0; k < 4; ++k)
			{
				temp[row][col] += A[row][k] * B[k][col];
			}
		}
	}
	mat4_dup(ret, temp);
}
WMATH_H_FUNC void mat4_print(const mat4 A)
{
	for (int i = 0; i < 4; ++i)
	{
		vec4_print(A[i]);
	}
	std::cout << std::endl;
}


/* --- TODO ---
* - Add
* - Sub
* -
*/


#endif //WMATH_H