#pragma once

#include"CMD3D_Math.h"

#include<iostream>
using namespace std;


class Camera
{
private:
	Vec3 pos;
	Vec3 dir;
	Vec3 up;

	Mat3 mat;
	
	float H_angle;
	float V_angle;
	float max_angle = toRad(89.999), min_angle = toRad(-89.999);

	void set_angle()
	{
		// V angle 
		V_angle = asin(up*dir);

//		Vec3 L = (up+Vec3(0,0,1))^up;
		H_angle = PI*0.5 - atan2(dir.z,dir.x);
	}

public:
	
	Vec3 GetPos(){ return pos; }
	Vec3 GetDir(){
		return Rot(0, -H_angle, 0)*Rot(-V_angle, 0, 0)*Vec3(0,0,1);
	}
	Vec3 GetUp(){ return up; }

	void Look_At(const Vec3 &_pos, const Vec3 &_tar, const Vec3 &_up)
	{
		pos = _pos;
		dir = (_tar-_pos).Normal();
		up = _up.Normal();
		set_angle();
	}

	void Look(const Vec3 &_pos, const Vec3 &_dir, const Vec3 &_up)
	{
		pos = _pos;
		dir = _dir;
		up = _up;
		dir.Normalize();
		up.Normalize();
		set_angle();
	}

	void Trans_Vec(Vec3 *p, const int cnt)
	{
		mat = Rot(V_angle,0,0)*Rot(0,H_angle,0);
		for(int i = 0 ; i < cnt ; i++)
			p[i] = mat * (p[i]-pos);
		return;
	}

	void move(const Vec3 &dpos)
	{
		pos += dpos;
	}
	void walk(float F_side, float L_side, float U_side)
	{
 		Vec3 dpos = GetDir()*F_side + (GetDir()^up)*L_side + GetUp()*U_side;
		pos += dpos;
	}

	void turn_R(float theta)
	{
		H_angle += deg(theta);
	}
	void turn_L(float theta)
	{
		H_angle -= deg(theta);
	}
	void turn_U(float theta)
	{
		theta = deg(theta);
		V_angle += theta;

		V_angle = Range( V_angle, min_angle,max_angle );
	}
	void turn_D(float theta)
	{
		theta = deg(theta);
		V_angle -= theta;

		V_angle = Range(V_angle, min_angle, max_angle);
	}
};

