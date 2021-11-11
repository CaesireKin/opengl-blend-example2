#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>


void DrawGround()
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	glBegin(GL_QUADS);

	for(int row = 0; row < 200;row++)
	{
		for(int col = 0; col < 200; col++)
		{
			x = col * 20.0f;
			
			glVertex3f(x,y,z-20.0f);
			glVertex3f(x,y,z);
			glVertex3f(x+20.0f,y,z);
			glVertex3f(x+20.0f,y,z-20.0f);
		}
		z += 20.0f;
	}

	glEnd();
}

void DrawCube(float x,float y,float z,float width,float height)
{
	glBegin(GL_QUADS);

	glVertex3f(x,y+height,z);
	glVertex3f(x,y,z);
	glVertex3f(x+width,y,z);
	glVertex3f(x+width,y+height,z);

	glVertex3f(x+width,y+height,z);
	glVertex3f(x+width,y,z);
	glVertex3f(x+width,y,z+width);
	glVertex3f(x+width,y+height,z+width);

	glVertex3f(x+width,y+height,z+width);
	glVertex3f(x+width,y,z+width);
	glVertex3f(x,y,z+width);
	glVertex3f(x,y+height,z+width);

	glVertex3f(x,y+height,z+width);
	glVertex3f(x,y+height,z);
	glVertex3f(x+width,y+height,z);
	glVertex3f(x+width,y+height,z+width);

	glVertex3f(x,y+height,z+width);
	glVertex3f(x,y,z+width);
	glVertex3f(x,y,z);
	glVertex3f(x,y+height,z);

	glVertex3f(x,y,z+width);
	glVertex3f(x,y,z);
	glVertex3f(x+width,y,z);
	glVertex3f(x+width,y,z+width);
	
	glEnd();
}
void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluLookAt(0.0,0.0,0.0,0.0,0.0,-1.0,0.0,1.0,0.0);

	DrawGround();
	DrawCube(50.0f,50.0f,-50.0f,50.0f,50.0f);
}

void Resize(int width,int height)
{
	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(0.0,width,0.0,height,1.0,1000.0);
}

void Configure(void)
{
	glClearColor(0.0,0.0,0.0,1.0);

	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
}

void SetDCPixelFormat(HDC hdc)
{
	int iPfdNum;

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		0,0,
		0,0,0,0,0,
		16,
		0,
		0,
		0,
		0,
		0,0,0
	};

	iPfdNum = ChoosePixelFormat(hdc,&pfd);

	SetPixelFormat(hdc,iPfdNum,&pfd);
}