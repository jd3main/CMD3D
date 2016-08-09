#ifndef CMD3D_MATH_H
	#define CMD3D_MATH_H

#include<math.h>
#include"CMD3D_Math/Vector.h"
#include"CMD3D_Math/Mat3.h" 

#define PI 3.141592653589793
#define toRad(a) ((a)/180.0*PI)
#define toDeg(a) ((a)/PI*180.0)


#define deg(a) (toRad(a))
#define Rad(a) (a)

#define sq(a) ((a)*(a))

float Range(float x, float L, float R)
{
	if(x < L)
		return L;
	if(x > R)
		return R;
	return x;
}
int Range(int x, int L, int R)
{
	if (x < L)
		return L;
	if (x > R)
		return R;
	return x;
}

#endif
