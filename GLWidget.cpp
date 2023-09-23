#include "GLWidget.hpp"
#include <iostream>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), m_program(0), m_shader(0) {}

void GLWidget::initializeGL()
{
	// Set up the rendering context, load shaders and other resources, etc.:
	initializeOpenGLFunctions();
	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// this function is called once, when the window is first shown, i.e. when
	// the the window content is first rendereds
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	
	// build and compile our shader program
	// ------------------------------------

	m_program = new QOpenGLShaderProgram();
	if (!m_program->addShaderFromSourceFile(
	    QOpenGLShader::Vertex, "/home/dejiko/Repositories/ufc/modelagem-geometrica/shaders/pass_through.vert"))
	{
		qDebug() << "Vertex shader errors :\n" << m_program->log();
	}

	if (!m_program->addShaderFromSourceFile(
	    QOpenGLShader::Fragment, "/home/dejiko/Repositories/ufc/modelagem-geometrica/shaders/simple.frag"))
	{
		qDebug() << "Fragment shader errors :\n" << m_program->log();
	}

	if (!m_program->link())
		qDebug() << "Shader linker errors :\n" << m_program->log();
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	// float vertices[] = {
	// 	0.3f,  0.3f, 0.8f,  // top right
	// 	0.3f, -0.3f, 0.0f,  // bottom right
	// 	-0.3f, -0.3f, 1.0f,  // bottom left
	// 	-0.3f,  0.3f, 0.0f   // top left
	// };

	float vertices[] = {
		-0.5f,-0.5f,-0.5f, // triangle 1 : begin
		-0.5f,-0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f, // triangle 1 : end
		0.5f, 0.5f,-0.5f, // triangle 2 : begin
		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f,-0.5f, // triangle 2 : end
		0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f, 0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f,-0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f, 0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f,-0.5f,
		-0.5f, 0.5f,-0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f,-0.5f, 0.5f
	};



	// QColor vertexColors [] = {
	// 	QColor("#f6a509"),
	// 	QColor("#cb2dde"),
	// 	QColor("#0eeed1"),
	// 	QColor("#068918"),
	// };

	QColor vertexColors [] = {
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34"),
		QColor("##49eb34")
	};

	




	// create buffer for 2 interleaved attributes: position and color, 4 vertices, 3 floats each
	//std::vector<float> vertexBufferData(2*4*3);
	std::vector<float> vertexBufferData(2*36*3);

	// create new data buffer - the following memory copy stuff should
	// be placed in some convenience class in later tutorials
	// copy data in interleaved mode with pattern p0c0|p1c1|p2c2|p3c3
	float * buf = vertexBufferData.data();
	for (int v=0; v<36; ++v, buf += 6) {
		// coordinates
		buf[0] = vertices[3*v];
		buf[1] = vertices[3*v+1];
		buf[2] = vertices[3*v+2];
		// colors
		buf[3] = vertexColors[v].redF();
		buf[4] = vertexColors[v].greenF();
		buf[5] = vertexColors[v].blueF();
	}
	// create a new buffer for the vertices and colors, interleaved storage
	m_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	m_vbo.create();
	m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_vbo.bind();

	// now copy buffer data over: first argument pointer to data, second argument: size in bytes
	m_vbo.allocate(vertexBufferData.data(), vertexBufferData.size()*sizeof(float) );
	// create and bind Vertex Array Object - must be bound *before* the element buffer is bound,
	// because the VAO remembers and manages element buffers as well
	m_vao.create();
	m_vao.bind();

	/*
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};*/
	

	 unsigned int indices[] = {  // note that we start from 0!	
	 	0, 1, 2,
	 	3, 4, 5,
	 	6, 7, 8,
	 	9, 10, 11,
	 	12, 13, 14,
	 	15, 16, 17,
	 	18, 19, 20,
	 	21, 22, 23,
	 	24, 25, 26,
	 	27, 28, 29,
	 	30, 31, 32,
	 	33, 34, 35
	 };

	// create a new buffer for the indexes
//	m_indexBufferObject = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer); // Mind: use 'IndexBuffer' here
//	m_indexBufferObject.create();
//	m_indexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
//	m_indexBufferObject.bind();
//	m_indexBufferObject.allocate(indices, sizeof(indices) );
	// stride = number of bytes for one vertex (with all its attributes) = 3+3 floats = 6*4 = 24 Bytes
	int stride = 6*sizeof(float);
	
	// layout location 0 - vec3 with coordinates
	m_program->enableAttributeArray(0);
	m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, stride);

	// layout location 1 - vec3 with colors
	m_program->enableAttributeArray(1);
	int colorOffset = 3*sizeof(float);
	m_program->setAttributeBuffer(1, GL_FLOAT, colorOffset, 3, stride);
	// Release (unbind) all
	m_vbo.release();
	m_vao.release();
}

void GLWidget::resizeGL(int w, int h)
{
	// Update projection matrix and other size related settings:
	m_projection.setToIdentity();
	m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
}

void GLWidget::paintGL()
{
	// set the background color = clear color
	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use our shader program
	m_program->bind();
	// bind the vertex array object, which in turn binds the vertex buffer object and
	// sets the attribute buffer in the OpenGL context
	m_vao.bind();
	// For old Intel drivers you may need to explicitely re-bind the index buffer, because
	// these drivers do not remember the binding-state of the index/element-buffer in the VAO
	//	m_indexBufferObject.bind();

	// now draw the two triangles via index drawing
	// - GL_TRIANGLES - draw individual triangles via elements
	glDrawArrays(GL_QUADS, 0, 36);
	// finally release VAO again (not really necessary, just for completeness)
	m_vao.release();
}
