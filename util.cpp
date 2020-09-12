#include "util.h"
#include <GL/gl.h>

void drawCube()
{
	const GLfloat vertexes[] =
	{
		-0.5f, -0.5f,  0.5f, /*  1 */
		 0.5f, -0.5f,  0.5f, /*  2 */
		 0.5f,  0.2f,  0.5f, /*  3 */
		 0.5f,  0.5f,  0.2f, /*  4 */
		 0.2f,  0.5f,  0.5f, /*  5 */
		-0.5f,  0.5f,  0.5f, /*  6 */
		-0.5f, -0.5f, -0.5f, /*  7 */
		 0.5f, -0.5f, -0.5f, /*  8 */
		 0.5f,  0.5f, -0.5f, /*  9 */
		-0.5f,  0.5f, -0.5f  /* 10 */
	};
	
	const GLubyte frontIndexes[]    = { 0, 1, 2, 4, 5 };
	const GLubyte backIndexes[]     = { 7, 6, 9, 8 };
	const GLubyte topIndexes[]      = { 5, 4, 3, 8, 9 };
	const GLubyte bottomIndexes[]   = { 6, 7, 1, 0 };
	const GLubyte rightIndexes[]    = { 1, 7, 8, 3, 2 };
	const GLubyte leftIndexes[]     = { 6, 0, 5, 9 };
	const GLubyte triangleIndexes[] = { 4, 2, 3 };

	const GLfloat normals[6][3] =
	{
		{  0.0,  0.0,  2.0 },
		{  0.0,  0.0, -2.0 },
		{  0.0, -2.0,  0.0 },
		{  0.0,  2.0,  0.0 },
		{  2.0,  0.0,  0.0 },
		{ -2.0,  0.0,  0.0 }
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexes);

	// Front face
	glColor3f(0.0f, 0.0f, 1.0f);
	glNormal3fv(normals[0]);
	glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, frontIndexes);

	// Back face
	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3fv(normals[1]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, backIndexes);
	
	// Bottom face
	glColor3f(0.8f, 0.6f, 0.1f);
	glNormal3fv(normals[2]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, bottomIndexes);

	// Top face
	glColor3f(1.0f, 0.0f, 1.0f);
	glNormal3fv(normals[3]);
	glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, topIndexes);

	// Right face
	glColor3f(0.0f, 1.0f, 0.0f);
	glNormal3fv(normals[4]);
	glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, rightIndexes);

	// Left face
	glColor3f(1.0f, 1.0f, 0.0f);
	glNormal3fv(normals[5]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, leftIndexes);

	// Triangle face
	glColor3f(0.6f, 0.6f, 0.6f);
	glNormal3fv(normals[0]);
	glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_BYTE, triangleIndexes);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void drawAxis()
{
	// eixo x
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(-5.0f, 0.0f, 0.0f);
	glVertex3f( 5.0f, 0.0f, 0.0f);
	glEnd();

	// eixo y
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, -5.0f, 0.0f);
	glVertex3f(0.0f,  5.0f, 0.0f);
	glEnd();

	// eixo z
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -5.0f);
	glVertex3f(0.0f, 0.0f,  5.0f);
	glEnd();
}
