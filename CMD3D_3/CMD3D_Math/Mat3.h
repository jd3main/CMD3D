#ifndef MAT3_H
	#define MAT3_H

#include"Vector.h"

// === Mat3 ====
typedef struct Mat3
{
	union{
		struct {
			float _a11, _a12, _a13;
			float _a21, _a22, _a23;
			float _a31, _a32, _a33;
		};
		struct { float a[3][3]; };
		struct { Vec3 v[3]; };
	};
	
	void Identity()
	{
		(*this)={1,0,0,
				 0,1,0,
				 0,0,1};
	};
	void Zero()
	{
		(*this)={0,0,0,
				 0,0,0,
				 0,0,0};
	}
	
	Mat3& InitRot(float _x, float _y, float _z);
	Mat3& InitRot(const Vec3 & v);
	
	Mat3& InitScale(float _x, float _y, float _z);
	Mat3& InitScale(const Vec3 & v);
	Mat3& InitScale(float k);


	Mat3& InitCamRot(const Vec3 &dir, const Vec3 &up);
	
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
	Mat3 operator * (const Mat3 &B) const
	{
		Mat3 C;
		C.Zero();
		for(int i = 0 ; i < 3 ; i++)
			for(int j = 0 ; j < 3 ; j++)
				for(int k = 0 ; k < 3 ; k++)
					C[i][k] += a[i][j]*B[j][k];
		return C;
	}
	
	inline Vec3& operator[](int x) { return v[x]; }
	inline const Vec3 operator[](int x) const{ return v[x]; }
	
	Mat3(){ Identity(); };
	Mat3(float _b11, float _b12, float _b13,
		 float _b21, float _b22, float _b23,
		 float _b31, float _b32, float _b33){
		
		_a11=_b11; _a12=_b12; _a13=_b13;
		_a21=_b21; _a22=_b22; _a23=_b23;
		_a31=_b31; _a32=_b32; _a33=_b33;
		
	};
	Mat3(const Vec3 &v1,
		 const Vec3 &v2,
		 const Vec3 &v3){
		_a11=v1.x; _a12=v1.y; _a13=v1.z;
		_a21=v2.x; _a22=v2.y; _a23=v2.z;
		_a31=v3.x; _a32=v3.y; _a33=v3.z;
	}
	Mat3(const Mat3 &B){
		for(int i = 0 ; i < 3 ; i++)
			for(int j = 0 ; j < 3 ; j++)
				a[i][j] = B.a[i][j];
	};
} Mat33, Mat3f;



// Rot
Mat3 GetRotX(float theta)
{
	return Mat3(
		1,0,0,
		0,cosf(theta), -sinf(theta),
		0,sinf(theta), cosf(theta)
	);
}
Mat3 GetRotY(float theta)
{
	return Mat3(
		cosf(theta), 0, -sinf(theta),
		0, 1, 0,
		sinf(theta),0, cosf(theta)
	);
}
Mat3 GetRotZ(float theta)
{
	return Mat3(
		cosf(theta), -sinf(theta), 0,
		sinf(theta), cosf(theta), 0,
		0, 0, 1
	);
}
Mat3& Mat3::InitRot(float x, float y, float z)
{
	return (*this) = GetRotZ(z)*GetRotY(y)*GetRotX(x);
}
Mat3& Mat3::InitRot(const Vec3 &v)
{
	return (*this) = GetRotZ(v.z)*GetRotY(v.y)*GetRotX(v.x);
}

// Scale
Mat3& Mat3::InitScale(float x, float y, float z)
{
	return (*this) = Mat3(
		x,0,0,
		0,y,0,
		0,0,z
	);
}
Mat3& Mat3::InitScale(const Vec3 &v)
{
	return (*this) = Mat3(
		v.x, 0, 0,
		0, v.y, 0,
		0, 0, v.z
	);
}
Mat3& Mat3::InitScale(float k)
{
	return (*this) = Mat3(
		k,0,0,
		0,k,0,
		0,0,k
	);
}


// Camera
Mat3& Mat3::InitCamRot(const Vec3 &dir, const Vec3 &up)
{
	Vec3 N = dir.Normal();		// Z
	Vec3 L = up.Normal()^N;	// X
	Vec3 U = N^L;				// Y

	return (*this) = Mat3{
		L,	// X
		U,	// Y
		N,	// Z
	};
}



// Get Matrix
Mat3 Rot(float x, float y, float z){
	return Mat3().InitRot(x,y,z);
}
Mat3 Rot(const Vec3 &v) {
	return Mat3().InitRot(v);
}

Mat3 Scale(float x, float y, float z) {
	return Mat3().InitScale(x, y, z);
}
Mat3 Scale(const Vec3 &v) {
	return Mat3().InitScale(v);
}


Mat3 CamRot(const Vec3 &dir, const Vec3 &up){
	return Mat3().InitCamRot(dir,up);
}

#endif
