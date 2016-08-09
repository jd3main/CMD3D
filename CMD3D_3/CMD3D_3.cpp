#include<iostream>
#include<cstring>
#include<ctime>


#include<Windows.h>
#include<conio.h>

#include"CMD3D_Math.h"
#include"Camera.h"
#include"WireMDL.h"

using namespace std; 



struct Canvas
{
	int w,h;
	char *data;
	float *depth;
	
	char* operator[](const int a){ return data+a*w; }
	char& operator[](const Vec2i &v){ return data[v.y*w + v.x]; }
	
	void Clip_Line(Vec3 &a, Vec3 &b)
	{
		// A
		if(a.x < 0) {
			float k = (0-a.x)/(b.x-a.x);
			a += (b-a)*k;
		}
		else if(a.x >= w) {
			float k = ((w-1)-a.x)/(b.x-a.x);
			a += (b-a)*k;
		}
		if(a.y < 0) {
			float k = (0-a.y)/(b.y-a.y);
			a += (b-a)*k;
		}
		else if(a.y >= h) {
			float k = ((h-1)-a.y)/(b.y-a.y);
			a += (b-a)*k;
		}
		
		// B
		if(b.x < 0) {
			float k = (0-b.x)/(a.x-b.x);
			b += (a-b)*k;
		}
		else if(b.x >= w) {
			float k = ((w-1)-b.x)/(a.x-b.x);
			b += (a-b)*k;
		}
		if(b.y < 0) {
			float k = (0-b.y)/(a.y-b.y);
			b += (a-b)*k;
		}
		else if(b.y >= h) {
			float k = ((h-1)-b.y)/(a.y-b.y);
			b += (a-b)*k;
		}
	}
	
	void Draw_Line(Vec3 a, Vec3 b, char c='*')
	{
//		cout << "Draw:" << a << "," << b << endl;
		
		a.y = -a.y;
		b.y = -b.y;
		a += Vec3(w/2.0, h/2.0, 0);
		b += Vec3(w/2.0, h/2.0, 0);
		 
		if(a.x < 0 && b.x < 0)	return;
		if(a.y < 0 && b.y < 0)	return;
		if(a.x >= w && b.x >= w)return;
		if(a.y >= h && b.y >= h)return;
		
		Clip_Line(a,b);
		
//		cout << "Cliped :" << a << "," << b << endl;
		
		
		float dx = b.x-a.x;
		float dy = b.y-a.y;
		float dz = b.z-a.z;
		if(fabs(dx) > fabs(dy))
		{
			int xL = round(min(a.x,b.x));
			int xR = round(max(a.x,b.x));
			float m = dy/dx;
			float mz = dz/dx;
			for(int x = xL ; x <= xR ; x++)
			{
				int y = round( a.y + (x-a.x)*m );
				float z = (a.z + (x-a.x)*mz);
				
				if(0 < z && z < 1 && depth[y*w+x]>z)
				{
					data[y*w+x] = c;
					depth[y*w+x] = z;
				}
			}
		}
		else
		{
			int yL = round(min(a.y,b.y));
			int yR = round(max(a.y,b.y));
			float m = dx/dy;
			float mz = dz/dy;
			for(int y = yL ; y <= yR ; y++)
			{
				int x = round( a.x + (y-a.y)*m );
				float z = (a.z + (x-a.x)*mz);
				if(0 < z && z < 1 && depth[y*w+x]>z)
				{
					data[y*w+x] = c;
					depth[y*w+x] = z;
				}
			}
		}
	}
	
	void Resize(int _w, int _h)
	{
		w = _w;
		h = _h;
		if(data != NULL)
			delete [] data;
		data = new char[w*h+1];
		
		if(depth != NULL)
			delete [] depth;
		depth = new float[w*h+1];
	}
	
	void Clear(char c)
	{
		memset(data,c,w*h);
		for(int i = 0 ; i < w*h ; i++)
			depth[i] = 1;
	}
};


int w=70,h=30;
float z_far=1024, z_near=0.1;
Canvas canvas;


Camera cam;
Vec3 p_buff[1023];
WMDL cube;
WMDL sq;


void Init()
{
	canvas.Resize(w,h);
	
	cube.Load("cube.wmdl");
	sq.Load("square.wmdl");
	
	cam.Look_At(
		{-4,2,-3},
		{0,0,0},
		{0,1,0}
	);
}


//char output_buff[10011];
string output_buff;
void Output_To_Buffer()
{
	/*
	int k = 0;
	for(int i = 0 ; i < h ; i++)
	{
		for(int j = 0 ; j < w ; j++)
		{
			output_buff[k] = canvas[i][j];
			k++;
		}
		output_buff[k++] = '\n';
	}
	output_buff[k] = '\0';
	*/
	output_buff = "";
	for(int i = 0 ; i < h ; i++)
	{
		for(int j = 0 ; j < w ; j++)
		{
			output_buff += canvas[i][j];
		}
		output_buff += '\n';
	}
}

inline void Display()
{
	cout << output_buff << endl;
	cout.flush();
}


void Clip_Z(Vec3 &a, Vec3 &b)
{
	// A
	if(a.z < z_near) {
		float k = (z_near-a.z)/(b.z-a.z);
		a += (b-a)*k;
	}
	else if(a.z > z_far) {
		float k = (z_far-a.z)/(b.z-a.z);
		a += (b-a)*k;
	}
	
	// B
	if(b.z < z_near) {
		float k = (z_near-b.z)/(a.z-b.z);
		b += (a-b)*k;
	}
	else if(b.z > z_far) {
		float k = (z_far-b.z)/(a.z-b.z);
		b += (a-b)*k;
	}
}

void Draw_MDL(const WMDL &mdl, const Vec3 &pos_v, const Vec3 &rot_v, const Vec3 &scale_v)
{
	int n = mdl.point.size();
	for(int i = 0 ; i < n ; i++)
		p_buff[i] = mdl.point[i];
	
	// Model View
	Mat3 mdl_mat = Scale(scale_v)*Rot(rot_v);
	for(int i = 0 ; i < n ; i++)
		p_buff[i] = mdl_mat*p_buff[i] - pos_v;
	
	
	// Camera
	cam.Trans_Vec(p_buff, n);
	
	// Clip z
	for(int i = 0 ; i<n ; i+=2)
		Clip_Z(p_buff[i], p_buff[i+1]);
	
		
	
	// projection
	
	float rdz = 1/(z_far-z_near);
	for(int i = 0 ; i < n ; i++)
	{
		Vec3 &p = p_buff[i];
		p.x = p.x/p.z * w;
		p.y = p.y/p.z * h;
		p.z = p.z*rdz - (z_near*rdz);
	}
	
	for(int i = 0 ; i < n ; i+=2)
		canvas.Draw_Line(p_buff[i], p_buff[i+1], 'A'+i/2);
}

void Draw()
{
	static float t=0;
	
	t+=0.1;
	
	Draw_MDL(cube, {0,0,0}, {0,t,0}, {1,1,1} );
}

void MainLoop()
{
	unsigned int prev_time=0;
	unsigned int cur_time = clock();
	unsigned int sleep_time = 1000/20;
	
	
	while(1)
	{
		canvas.Clear('-');
		
		Draw();
		Output_To_Buffer();
		
		if(kbhit())
		{
			char c = getch();
			switch(c)
			{
			case 'W':
			case 'w':
				cam.walk(0.2, 0, 0);
				break;
			case 'S':
			case 's':
				cam.walk(-0.2, 0, 0);
				break;
			case 'A':
			case 'a':
				cam.walk(0, 0.2, 0);
				break;
			case 'D':
			case 'd':
				cam.walk(0, -0.1, 0);
				break;
			
			case '5':
				cam.turn_U(5);
				break;
			case '2':
				cam.turn_D(5);
				break;
			case '1':
				cam.turn_L(5);
				break;
			case '3':
				cam.turn_R(5);
				break;
				
			case 'p':
				system("pause");
				break;
			}
		}
		
		
		prev_time = cur_time;
		cur_time = clock();
		
		if(cur_time-prev_time < sleep_time)
			Sleep(sleep_time - (cur_time-prev_time));
		
		system("cls");
		Display();
	}
}

int main()
{	
	cin.tie(0);
	ios::sync_with_stdio(false);
	
	Init();
	cout << "ready.\n\n";
	cout << "<!> 記得將輸入法切換到英數模式" << "\n\n\n\n" << endl;
	system("pause");
	
	MainLoop();
}












