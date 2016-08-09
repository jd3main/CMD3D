

#ifndef VEC4_H
	#define VEC4_H

#include"Vec_Declare.h"
#include<math.h>


struct Vec4
{
	union{
		struct{ float x,y,z,w; };
		struct{ float a[4]; };
	};
	
	
	// Init
	Vec4(){ x=0; y=0; z=0; w=0; };
	Vec4(const Vec3& v);
	Vec4(const Vec4& v){ x=v.x; y=v.y; z=v.z; w=v.w; };
	Vec4(float _x, float _y, float _z, float _w=0){ x=_x; y=_y; z=_z; w=_w; };
	
	
	// operator
	Vec4 operator + (const Vec4 &v)const{ return Vec4(x+v.x, y+v.y, z+v.z, w+v.w); }
	Vec4 operator - (const Vec4 &v)const{ return Vec4(x-v.x, y-v.y, z-v.z, w-v.w); }
	Vec4 operator * (float f)const{ return Vec4(x*f, y*f, z*f, w*f); }
	Vec4 operator - ()const{return Vec4(-x,-y,-z,-w);};
	
	
	// []
	float operator [] (int i) const { return a[i]; }
	float& operator [] (int i) { return a[i]; }
	
	// x=
	Vec4& operator += (const Vec4 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	Vec4& operator -= (const Vec4 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	Vec4& operator *= (float f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return *this;
	}
	
	
	// Lenth
	float lenth()
	{
		return sqrt(x*x + y*y + z*z + w*w);
	}
	
	// cout
	friend ostream& operator << (ostream& s, const Vec4 &v)
	{
		s << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
		return s;
	}
};


Vec4 operator * (const Vec4& v, float f){ return Vec4(f*v.x, f*v.y, f*v.z); };
Vec4 operator * (float f, const Vec4& v){ return Vec4(f*v.x, f*v.y, f*v.z); };



#ifdef VEC3_H
Vec3::Vec3(const Vec4 &v) { x=v.x; y=v.y; z=v.z; };
Vec4::Vec4(const Vec3 &v) { x=v.x; y=v.y; z=v.z; w = 0; };
#endif

#endif
