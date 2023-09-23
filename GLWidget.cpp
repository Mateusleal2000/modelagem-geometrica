#include "GLWidget.hpp"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), m_program(0), m_shader(0) {}

void GLWidget::initializeGL()
{
	// Set up the rendering context, load shaders and other resources, etc.:
	initializeOpenGLFunctions();
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::resizeGL(int w, int h)
{
	// Update projection matrix and other size related settings:
	m_projection.setToIdentity();
	m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
}

void GLWidget::paintGL()
{
	// Draw the scene:
	glClear(GL_COLOR_BUFFER_BIT);
}
