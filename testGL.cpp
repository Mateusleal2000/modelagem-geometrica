
#include "testGL.hpp"
#include <iostream>

testGL::testGL(QWidget *parent) : QOpenGLWidget(parent), m_program(0), m_shader(0)
{
	colorVector = new std::vector<QColor>();
  m_projection = new QMatrix4x4();
	m_projection->perspective(45.0f, 640.0 / float(480), 0.01f, 100.0f);
}

void testGL::initializeGL()
{
	// Set up the rendering context, load shaders and other resources, etc.:
	initializeOpenGLFunctions();

	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// this function is called once, when the window is first shown, i.e. when
	// the the window content is first rendereds
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
glEnable(GL_DEPTH_CLAMP);
glEnable(GL_LINE_SMOOTH);
   glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_NORMALIZE);
	// build and compile our shader program
	// ------------------------------------

	m_program = new QOpenGLShaderProgram();
	if (!m_program->addShaderFromSourceFile(
			QOpenGLShader::Vertex, ":/shaders/pass_through.vert"))
	{
		qDebug() << "Vertex shader errors :\n"
				 << m_program->log();
	}

	if (!m_program->addShaderFromSourceFile(
			QOpenGLShader::Fragment, ":/shaders/simple.frag"))
	{
		qDebug() << "Fragment shader errors :\n"
				 << m_program->log();
	}

	if (!m_program->link())
		qDebug() << "Shader linker errors :\n"
				 << m_program->log();
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	glUseProgram(m_program->programId());
  float vertices[] = {
		//BACK
  	 0.6f,  0.6f, -0.6f,  // top right
  	 0.6f, -0.6f, -0.6f,  // bottom right
  	-0.6f, -0.6f, -0.6f,  // bottom left
  	-0.6f,  0.6f, -0.6f,   // top left

    //FRONT
  	 0.6f,  0.6f, 0.6f,  // top right
  	 0.6f, -0.6f, 0.6f,  // bottom right
  	-0.6f, -0.6f, 0.6f,  // bottom left
  	-0.6f,  0.6f, 0.6f   // top left
  };


  QColor vertexColors [] = {
  	QColor("#f6a509"),
  	QColor("#cb2dde"),
  	QColor("#0eeed1"),
  	QColor("#068918"),


  	QColor("#f6a509"),
  	QColor("#cb2dde"),
  	QColor("#0eeed1"),
  	QColor("#068918"),
  };



 QMatrix4x4 rotx = QMatrix4x4(1, 0, 0, 0,
 															0, 0.81, -0.5, 0,
 															0, 0.5, 0.81, 0,
 															0, 0, 0, 1);

 QMatrix4x4 roty = QMatrix4x4(0.81, 0, 0.5, 0,
 																 0, 1, 0, 0,
 																 -0.5, 0, 0.81, 0,
 																 0, 0, 0, 1);

	QMatrix4x4 viewMatrix;
	viewMatrix.rotate(30,0,1,0);

	viewMatrix.rotate(30,1,0,0);
	viewMatrix.translate(0,3,40);

	viewMatrix = viewMatrix.inverted();


	QMatrix4x4 modelMatrix; //= (rotx)*(roty);

  int projectionpos = m_program->uniformLocation("projectionMatrix");
	int modelMatrixpos = m_program->uniformLocation("modelMatrix");
	int viewMatrixpos = m_program->uniformLocation("viewMatrix");
	//int rotxpos = m_program->uniformLocation("rotx");
	//int rotypos = m_program->uniformLocation("roty");
	
	std::vector<float> vertexBufferData(2 * 8 * 3);

	// create new data buffer - the following memory copy stuff should
	// be placed in some convenience class in later tutorials
	// copy data in interleaved mode with pattern p0c0|p1c1|p2c2|p3c3
	float *buf = vertexBufferData.data();
	for (int v = 0; v < 8; ++v, buf += 6)
	{
		// coordinates
		buf[0] = vertices[3 * v];
		buf[1] = vertices[3 * v + 1];
		buf[2] = vertices[3 * v + 2];
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
	m_vbo.allocate(vertexBufferData.data(), vertexBufferData.size() * sizeof(float));
	// create and bind Vertex Array Object - must be bound *before* the element buffer is bound,
	// because the VAO remembers and manages element buffers as well
	m_vao.create();
	m_vao.bind();

  unsigned int indices[] = {  // note that we start from 0!
  	//0, 1, 3,   // first triangle
  	//1, 2, 3    // second triangle
		0,1,
		1,2,
		2,3,
		3,0,

		4,5,
		5,6,
		6,7,
		7,4,

		0,4,
		1,5,
		2,6,
		3,7
  };

	// create a new buffer for the indexes
	m_indexBufferObject = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer); // Mind: use 'IndexBuffer' here
	m_indexBufferObject.create();
	m_indexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_indexBufferObject.bind();
	//O segundo argumento deveria ser aquele mesmo???
	m_indexBufferObject.allocate(indices, sizeof(indices)/*indicesVector->size()*/);

	
	// stride = number of bytes for one vertex (with all its attributes) = 3+3 floats = 6*4 = 24 Bytes
	int stride = 6 * sizeof(float);

	// layout location 0 - vec3 with coordinates
	m_program->enableAttributeArray(0);
	m_program->setAttributeBuffer(0, GL_FLOAT, 0,3, stride);
/*
	m_program->setUniformValue(rotxpos, *rotx);
	m_program->setUniformValue(rotypos,*roty);
	m_program->setUniformValue(projectionpos, *m_projection);
*/
	m_program->setUniformValue(modelMatrixpos,modelMatrix);	
	m_program->setUniformValue(viewMatrixpos,viewMatrix);
	m_program->setUniformValue(projectionpos,*m_projection);

	// layout location 1 - vec3 with colors
	m_program->enableAttributeArray(1);

	int colorOffset = 3 * sizeof(float);
	m_program->setAttributeBuffer(1, GL_FLOAT, colorOffset, 3, stride);
	// Release (unbind) all

	m_vbo.release();
	m_vao.release();
}

void testGL::resizeGL(int w, int h)
{
	// Update projection matrix and other size related settings:
	std::cout<<"proj\n";
	m_projection->setToIdentity();

	std::cout<<"dps proj\n";
	m_projection->perspective(45.0f, w / float(h), 0.01f, 100.0f);
}

void testGL::paintGL()
{
	// set the background color = clear color

 glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
	// glDrawArrays(GL_QUADS, 0, 24);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
	// finally release VAO again (not really necessary, just for completeness)
	m_vao.release();
}

// Arestas
// Face de Tras:
// TLB-TRB , BLB-BRB, TLB-BLB, TRB-BRB
// Face da Frente:
// TLF-TRF , BLF-BRF, TLF-BLF, TRF-BRF
// Arestas da Esquerda:
// BLB-BLF, TLF-TLB
// Face da Direita
// BRB-BRF, TRF-TRB

