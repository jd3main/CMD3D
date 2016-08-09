#ifndef VEC3_H
	#define VEC3_H


#include"Vec_Declare.h"
#include<math.h>
#include<iostream>
using std::ostream;

struct Vec3
{
	union{
		struct{ float x,y,z; };
		struct{ float a[3]; };
	};
	
	
	// Init
	Vec3(){ x=0; y=0; z=0; };
	Vec3(const Vec3 &v){ x=v.x; y=v.y; z=v.z; };
	Vec3(const Vec4 &v);
	Vec3(float _x, float _y, float _z){ x=_x; y=_y; z=_z; };
	
	// []
	const float operator [] (int i) const { return a[i]; }
	float& operator [] (int i) { return a[i]; }
	
	// operator
	Vec3 operator + (const Vec3 &v)const{ return Vec3(x+v.x, y+v.y, z+v.z); }
	Vec3 operator - (const Vec3 &v)const{ return Vec3(x-v.x, y-v.y, z-v.z); }
	Vec3 operator * (float f)const{ return Vec3(x*f, y*f, z*f); }
	Vec3 operator / (float f)const{ return Vec3(x/f, y/f, z/f); }
	Vec3 operator - ()const{return Vec3(-x,-y,-z);};
	
	// x=
	Vec3& operator += (const Vec3 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vec3& operator -= (const Vec3 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	Vec3& operator *= (float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}
	Vec3& operator /= (const Vec3 &v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.y;
		return *this;
	}
	
	
	
	// dot & cross
	float operator * (const Vec3 &v){ return x*v.x + y*v.y + z*v.z; }
	Vec3 operator ^ (const Vec3 &v){ return Vec3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
	
	// Normal
	Vec3 Normal() const
	{
		const float R = sqrt(x*x + y*y + z*z);
		return Vec3(x/R, y/R, z/R);
	}
	Vec3& Normalize()
	{
		const float R = sqrt(x*x + y*y + z*z);
		x /= R;
		y /= R;
		z /= R;
		return *this;
	}
	
	// cout
	friend ostream& operator << (ostream& s, const Vec3 &v)
	{
		s << "(" << v.x << "," << v.y << "," << v.z << ")";
		return s;
	}
};


Vec3 operator * (float f, const Vec3& v){ return Vec3(f*v.x, f*v.y, f*v.z); };

#ifdef VEC4_H
Vec3::Vec3(const Vec4 &v){ x=v.x; y=v.y; z=v.z; };
Vec4::Vec4(const Vec3 &v) { x=v.x; y=v.y; z=v.z; w=0;};
#endif

#endif
