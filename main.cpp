#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "classes/glwindow.h"
#include "util.h"
#include "keyaction.h"

class RenderWindow: public GLWindowBase
{
private:
	KeyAction actionEixoX;
	KeyAction actionEixoY;
	KeyAction actionEixoZ;
	float ax, ay, az;
	float rot_vel;
	bool perspectiva3D;
protected:
	bool onInit(int argc, char** argv)
	{
		// qualidade do anti serrilhado
#ifdef _WIN32
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
#endif
		return GLWindowBase::onInit(argc, argv);
	}

	virtual void getWindowInfo(int& width, int& height, int& bpp, bool& fullscreen, bool& resizable)
	{
		GLWindowBase::getWindowInfo(width, height, bpp, fullscreen, resizable);
		resizable = false;
	}

	virtual void onResize(int newWidth, int newHeight)
	{
		onCreate();
	}

	/**
	 * desenha no plano 3D
	 */
	void setPerspectiva3D()
	{
		int width = getWidth();
		int height = getHeight();
		
		if (height == 0)									// Prevent A Divide By Zero
			height = 1;
		glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix
		glViewport(0, 0, width, height);					// Set The Current Viewport
		// Calculate The Aspect Ratio Of The Window
		glMatrixMode( GL_MODELVIEW );						// Select The Modelview Matrix
		glLoadIdentity();									// Reset The Modelview Matrix
		gluPerspective(45.0f, (GLfloat)width / height, 0.1f, 100.0f);
	}

	/**
	 * desenha no plano 2D
	 */
	void setPerspectiva2D()
	{
		int width = getWidth();
		int height = getHeight();
		
		glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix
		glViewport(0, 0, width, height);					// Set The Current Viewport
		// Set up the orthographic projection
		glMatrixMode( GL_MODELVIEW );						// Select The Modelview Matrix
		glLoadIdentity();									// Reset The Modelview Matrix
		glOrtho( width / 2.0, -width / 2.0, -height / 2.0, height / 2.0, -5.0, 5.0 );
		glDisable( GL_DEPTH_TEST );
	}

	virtual void onCreate()
	{
		GLfloat col[] = {0.2f, 0.2f, 0.2f, 1.0f};
		GLfloat pos[] = { -4.0f, 0.0f, 4.0f, 1.0f};
		int width = getWidth();
		int height = getHeight();
		int min = (width > height)? height: width;

		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		if(perspectiva3D)
		{
			setPerspectiva3D();
			// Habilita teste de profundidade
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glClearDepth(1.0f);
			glDepthFunc(GL_LEQUAL);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			glTranslatef(0.0f, 0.0f, -4.1f);
		}
		else
		{
			setPerspectiva2D();
			glScalef(min / 3.0f, min / 3.0f, 1.0f);
			glTranslatef(0.0f, 0.0f, -1.0f);
			glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		}
		// Habilita luz
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		// Habilita cor nor objetos
		glEnable(GL_COLOR_MATERIAL);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );

		//Add ambient light
		GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color(0.2, 0.2, 0.2)
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
		// move todos os desenhos para o fundo
		glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
	}

	/**
	 * trata os eventos do teclado
	 */
	virtual void onKeyDown(int key, int state)
	{
		char ch = translateKey(key, state);
		actionEixoX.update(ch, true);
		actionEixoY.update(ch, true);
		actionEixoZ.update(ch, true);
		switch(ch)
		{
		case 't':
			ax = 90.0f;
			ay = az = 0.0f;
			break;
		case 'f':
			ax = -90.0f;
			ay = az = 0.0f;
			break;
		case 'T':
			ay = 180.0f;
			ax = az = 0.0f;
			break;
		case 'F':
			ax = ay = az = 0.0f;
			break;
		case 'd':
			ay = -90.0f;
			ax = az = 0.0f;
			break;
		case 'e':
			ay = 90.0f;
			ax = az = 0.0f;
			break;
		case 'c':
			ax = 45.0f;
			ay = -45.0f;
			az = 0.0f;
			break;
		case 'O':
		case 'o':
			perspectiva3D = false;
			onCreate();
			break;
		case 'P':
		case 'p':
			perspectiva3D = true;
			onCreate();
			break;
		default:
			break;
		}
		GLWindowBase::onKeyDown(key, state);
	}


	/**
	 * trata os eventos do teclado
	 */
	virtual void onKeyUp(int key, int state)
	{
		char ch = translateKey(key, state);
		actionEixoX.update(ch, false);
		actionEixoY.update(ch, false);
		actionEixoZ.update(ch, false);
		GLWindowBase::onKeyUp(key, state);
	}

	/**
	 * desenha o braço e o suporte
	 */
	virtual void render()
	{
		// limpa o buffer
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glPushMatrix();

		// rotaciona do 3 ângulos
		glRotatef(ax, 1.0f, 0.0f, 0.0f);
		glRotatef(ay, 0.0f, 1.0f, 0.0f);
		glRotatef(az, 0.0f, 0.0f, 1.0f);
		//drawAxis();
		drawCube();

		glPopMatrix();
		// mostra os desenhos
		swapBuffers();

		// atualiza os movimentos
		updateAction();
	}

	/**
	 * Atualiza os ângulos
	 */
	inline void updateAction()
	{
		if(actionEixoX.inAction())
		{
			ax += rot_vel * actionEixoX.getSide();
		}
		if(actionEixoY.inAction())
		{
			ay += rot_vel * actionEixoY.getSide();
		}
		if(actionEixoZ.inAction())
		{
			az += rot_vel * actionEixoZ.getSide();
		}
	}

public:
	RenderWindow()
	{
		actionEixoX.setKeys('x', 'X');
		actionEixoY.setKeys('y', 'Y');
		actionEixoZ.setKeys('z', 'Z');
		ax = az = ay = 0.0f;
		rot_vel = 1.0f;
		perspectiva3D = true;
	}
	~RenderWindow() {}
};

int main(int argc, char *argv[])
{
	RenderWindow lp;

	lp.setTitle("Cubo");
	return lp.start(argc, argv);
}

