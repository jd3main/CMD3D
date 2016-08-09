#ifndef MAT4_H
	#define MAT4_H

#include"Vector.h"

// === Mat4 ====
typedef struct Mat4
{
	union{
		struct {
			float _a11, _a12, _a13, _a14;
			float _a21, _a22, _a23, _a24;
			float _a31, _a32, _a33, _a34;
			float _a41, _a42, _a43, _a44;
		};
		struct { float a[4][4]; };
		struct { Vec4 v[4]; };
	};
	
	void Identity()
	{
		(*this)={1,0,0,0,
				 0,1,0,0,
				 0,0,1,0,
				 0,0,0,1};
	};
	void Zero()
	{
		(*this)={0,0,0,0,
				 0,0,0,0,
				 0,0,0,0,
				 0,0,0,0};
	}
	
	Mat4& InitRot(float _x, float _y, float _z);
	Mat4& InitRot(const Vec3 & v);
	Mat4& InitMove(float _x, float _y, float _z);
	Mat4& InitMove(const Vec3 & v);
	Mat4& InitScale(float _x, float _y, float _z);
	Mat4& InitScale(const Vec3 & v);
	Mat4& InitScale(float k);

	Mat4& InitProj(float theta, float rate, float z_near, float z_far);

	Mat4& InitCamRot(const Vec3 &dir, const Vec3 &up);
	
	Vec3 operator * (const Vec3 &B)
	{
		Vec3 C(0, 0, 0);
		for (int i = 0; i < 3; i++)
		{
			C[i] = 0;
			for (int j = 0; j < 3; j++)
				C[i] += a[i][j] * B[j];
		}
		return C;
	}
	Vec4 operator * (const Vec4 &B)
	{
		Vec4 C(0,0,0,0);
		for(int i = 0 ; i < 4 ; i++)
		{
			C[i] = 0;
			for(int j = 0 ; j < 4 ; j++)
				C[i] += a[i][j]*B[j];
		}
		return C;
	}
	Mat4 operator * (const Mat4 &B) const
	{
		Mat4 C;
		C.Zero();
		for(int i = 0 ; i < 4 ; i++)
			for(int j = 0 ; j < 4 ; j++)
				for(int k = 0 ; k < 4 ; k++)
					C[i][k] += a[i][j]*B[j][k];
		return C;
	}
	
	inline Vec4& operator[](int x) { return v[x]; }
	inline const Vec4 operator[](int x) const{ return v[x]; }
	
	Mat4(){ Identity(); };
	Mat4(float _b11, float _b12, float _b13, float _b14,
		 float _b21, float _b22, float _b23, float _b24,
		 float _b31, float _b32, float _b33, float _b34,
		 float _b41, float _b42, float _b43, float _b44){
		
		_a11=_b11; _a12=_b12; _a13=_b13; _a14=_b14;
		_a21=_b21; _a22=_b22; _a23=_b23; _a24=_b24;
		_a31=_b31; _a32=_b32; _a33=_b33; _a34=_b34;
		_a41=_b41; _a42=_b42; _a43=_b43; _a44=_b44;
		
	};
	Mat4(const Vec4 &v1,
		 const Vec4 &v2,
		 const Vec4 &v3,
		 const Vec4 &v4){
		_a11=v1.x; _a12=v1.y; _a13=v1.z; _a14=v1.w;
		_a21=v2.x; _a22=v2.y; _a23=v2.z; _a24=v2.w;
		_a31=v3.x; _a32=v3.y; _a33=v3.z; _a34=v3.w;
		_a41=v4.x; _a42=v4.y; _a43=v4.z; _a44=v4.w;
	}
	Mat4(const Mat4 &B){
		for(int i = 0 ; i < 4 ; i++)
			for(int j = 0 ; j < 4 ; j++)
				a[i][j] = B.a[i][j];
	};
} Matrix4;



// Rot
Mat4 GetRotX(float theta)
{
	return Mat4(
		1,0,0,0,
		0,cosf(theta), -sinf(theta), 0,
		0,sinf(theta), cosf(theta), 0,
		0,0,0,1
	);
}
Mat4 GetRotY(float theta)
{
	return Mat4(
		cosf(theta), 0, -sinf(theta), 0,
		0, 1, 0, 0,
		sinf(theta),0, cosf(theta), 0,
		0, 0, 0, 1
	);
}
Mat4 GetRotZ(float theta)
{
	return Mat4(
		cosf(theta), -sinf(theta), 0, 0,
		sinf(theta), cosf(theta), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}
Mat4& Mat4::InitRot(float x, float y, float z)
{
	return (*this) = GetRotZ(z)*GetRotY(y)*GetRotX(x);
}
Mat4& Mat4::InitRot(const Vec3 &v)
{
	return (*this) = GetRotZ(v.z)*GetRotY(v.y)*GetRotX(v.x);
}

// Scale
Mat4& Mat4::InitScale(float x, float y, float z)
{
	return (*this) = Mat4(
		x,0,0,0,
		0,y,0,0,
		0,0,z,0,
		0,0,0,1
	);
}
Mat4& Mat4::InitScale(const Vec3 &v)
{
	return (*this) = Mat4(
		v.x, 0, 0, 0,
		0, v.y, 0, 0,
		0, 0, v.z, 0,
		0, 0, 0, 1
	);
}
Mat4& Mat4::InitScale(float k)
{
	return (*this) = Mat4(
		k,0,0,0,
		0,k,0,0,
		0,0,k,0,
		0,0,0,1
	);
}


// Move
Mat4& Mat4::InitMove(float x, float y, float z)
{
	return (*this) = Mat4(
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	);
}
Mat4& Mat4::InitMove(const Vec3 &v)
{
	return (*this) = Mat4(
		1, 0, 0, v.x,
		0, 1, 0, v.y,
		0, 0, 1, v.z,
		0, 0, 0, 1
	);
}

// Projection
Mat4& Mat4::InitProj(float theta, float rate, float z_near, float z_far)
{
	float dz = z_far - z_near;
	float sz = z_far + z_near;
	return (*this) = Mat4(
		1/(rate*tan(theta/2)),	0,					0,			0,
		0,				1/(tan(theta/2)),		0,			0,
		0,							0,				sz/dz,		-2*z_near*z_far/dz,
		0,							0,				1,			0
	);
}


// Camera
Mat4& Mat4::InitCamRot(const Vec3 &dir, const Vec3 &up)
{
	Vec3 N = dir.Normal();		// Z
	Vec3 L = up.Normal()^N;	// X
	Vec3 U = N^L;				// Y

	return (*this) = Mat4{
		L,	// X
		U,	// Y
		N,	// Z
		{0,0,0,1}
	};
}



// Get Matrix
Mat4 Rot(float x, float y, float z){
	return Mat4().InitRot(x,y,z);
}
Mat4 Rot(const Vec3 &v) {
	return Mat4().InitRot(v);
}

Mat4 Scale(float x, float y, float z) {
	return Mat4().InitScale(x, y, z);
}
Mat4 Scale(const Vec3 &v) {
	return Mat4().InitScale(v);
}

Mat4 Move(float x, float y, float z) {
	return Mat4().InitMove(x, y, z);
}
Mat4 Move(const Vec3 &v) {
	return Mat4().InitMove(v);
}


Mat4 Projection(float theta, float rate, float z_near, float z_far) {
	return Mat4().InitProj(theta, rate, z_near, z_far);
}
Mat4 CamRot(const Vec3 &dir, const Vec3 &up){
	return Mat4().InitCamRot(dir,up);
}

#endif
