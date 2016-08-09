#ifndef VEC2_H
	#define VEC2_H

#include"Vec_Declare.h"
#include<math.h>

struct Vec2f;
struct Vec2i;


struct Vec2f
{
	union{
		struct{ float x,y; };
		struct{ float a[2]; };
	};
	
	
	// Init
	Vec2f(){ x=0; y=0; };
	Vec2f(float _x, float _y){ x=_x; y=_y; };
	
	
	// x=
	Vec2f& operator += (const Vec2f &v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2f& operator -= (const Vec2f &v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vec2f& operator *= (float f)
	{
		x *= f;
		y *= f;
		return *this;
	}
	Vec2f& operator /= (const float f)
	{
		x /= f;
		y /= f;
		return *this;
	}
	
	
	// dot & cross
	float operator * (const Vec2f &v){ return x*v.x + y*v.y; }
	float operator ^ (const Vec2f &v){ return x*v.y - y*v.x; }
	
	// Normal
	Vec2f Normal()
	{
		const float R = sqrt(x*x + y*y);
		return Vec2f(x/R, y/R);
	}
	Vec2f& Normalize()
	{
		const float R = sqrt(x*x + y*y);
		x /= R;
		y /= R;
		return *this;
	}
	
};

struct Vec2i
{
	union{
		struct{ int x,y; };
		struct{ int a[2]; };
	};
	
	
	// Init
	Vec2i(){ x=0; y=0; };
	Vec2i(int _x, int _y){ x=_x; y=_y; };
	
	
	// x=
	Vec2i& operator += (const Vec2i &v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2i& operator -= (const Vec2i &v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vec2i& operator *= (float f)
	{
		x *= f;
		y *= f;
		return *this;
	}
	Vec2i& operator *= (int i)
	{
		x *= i;
		y *= i;
		return *this;
	}
	Vec2i& operator /= (const float f)
	{
		x /= f;
		y /= f;
		return *this;
	}
	
	
	// dot & cross
	int operator * (const Vec2i &v){ return x*v.x + y*v.y; }
	int operator ^ (const Vec2i &v){ return x*v.y - y*v.x; }
	
};



Vec2f operator + (const Vec2f &A, const Vec2f &B){ return Vec2f(A.x+B.x, A.y+B.y); }
Vec2f operator - (const Vec2f &A, const Vec2f &B){ return Vec2f(A.x-B.x, A.y-B.y); }



Vec2f operator * (float f, const Vec2f& v){ return Vec2f(f*v.x, f*v.y); };
Vec2i operator * (float f, const Vec2i& v){ return Vec2i(f*v.x, f*v.y); };
Vec2i operator * (int i, const Vec2i& v){ return Vec2i(i*v.x, i*v.y); };




#endif



