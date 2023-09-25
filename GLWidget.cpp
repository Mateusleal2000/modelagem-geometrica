#include "GLWidget.hpp"
#include <iostream>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), m_program(0), m_shader(0)
{
	verticesVector = new std::vector<float>();
	indicesVector = new std::vector<unsigned int>();
	colorVector = new std::vector<QColor>();
	m_projection = new QMatrix4x4();
}

void GLWidget::initializeGL()
{
	// Set up the rendering context, load shaders and other resources, etc.:
	initializeOpenGLFunctions();

	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// this function is called once, when the window is first shown, i.e. when
	// the the window content is first rendereds
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	std::cout << glGetError() << std::endl;
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
std::cout << glGetError() << std::endl;
	//glEnable(GL_NORMALIZE);
std::cout << glGetError() << std::endl;
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
std::cout << glGetError() << std::endl;
	std::vector<Point3> *vv = octtree->getGlobalVerticesVector();
	for (int i = 0; i < vv->size(); i++)
	{
		verticesVector->push_back(vv->at(i).x()/5.0);
		verticesVector->push_back(vv->at(i).y()/5.0);
		verticesVector->push_back(vv->at(i).z()/5.0);
		colorVector->push_back(QColor("#49eb34"));
	}


	float *vertices = verticesVector->data();
	QColor *vertexColors = colorVector->data();
	

	Node *root = octtree->getRoot();
	treeWalk(root);

	unsigned int *indices = indicesVector->data();



	// percorre a arvore

	// float vertices[] = {
	// 		-0.5f, -0.5f, -0.5f,
	// 		-0.5f, 0.5f, -0.5f,
	// 		0.5f, 0.5f, -0.5f,
	// 		0.5f, -0.5f, -0.5f,

	// 		-0.5f, -0.5f, 0.5f,
	// 		-0.5f, 0.5f, 0.5f,
	// 		0.5f, 0.5f, 0.5f,
	// 		0.5f, -0.5f, 0.5f,

	// 		0.5f, -0.5f, -0.5f,
	// 		0.5f, 0.5f, -0.5f,
	// 		0.5f, 0.5f, 0.5f,
	// 		0.5f, -0.5f, 0.5f,

	// 		-0.5f, -0.5f, -0.5f,
	// 		-0.5f, 0.5f, -0.5f,
	// 		-0.5f, 0.5f, 0.5f,
	// 		-0.5f, -0.5f, 0.5f,

	// 		-0.5f, 0.5f, -0.5f,
	// 		0.5f, 0.5f, -0.5f,
	// 		0.5f, 0.5f, 0.5f,
	// 		-0.5f, 0.5f, 0.5f,

	// 		-0.5f, -0.5f, -0.5f,
	// 		0.5f, -0.5f, -0.5f,
	// 		0.5f, -0.5f, 0.5f,
	// 		-0.5f, -0.5f, 0.5f

	// };

	// QColor vertexColors[] = {
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34"),
	// 		QColor("#49eb34")};

	// m_projection = new QMatrix4x4(1, 0, 0, 0,
	// 															0, 0.81, 0.5, 0,
	// 															0, -0.5, 0.81, 0,
	// 															0, 0, 0, 1);

	// QMatrix4x4 *rot = new QMatrix4x4(0.81, 0, 0.5, 0,
	// 																 0, 1, 0, 0,
	// 																 -0.5, 0, 0.81, 0,
	// 																 0, 0, 0, 1);

	// int matrixLocation = m_program->uniformLocation("matrix");
	// int rotLocation = m_program->uniformLocation("rot");
	// std::cout << matrixLocation << "\n";

	// std::cout << rotLocation << "\n";

	// create buffer for 2 interleaved attributes: position and color, 4 vertices, 3 floats each
	// std::vector<float> vertexBufferData(2*4*3);
	std::vector<float> vertexBufferData(2 * vv->size() * 3);

	// create new data buffer - the following memory copy stuff should
	// be placed in some convenience class in later tutorials
	// copy data in interleaved mode with pattern p0c0|p1c1|p2c2|p3c3
	float *buf = vertexBufferData.data();
	for (int v = 0; v < vv->size(); ++v, buf += 6)
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
	std::cout << glGetError() << std::endl;
	m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
std::cout << glGetError() << std::endl;
	m_vbo.bind();
std::cout << glGetError() << std::endl;

	// now copy buffer data over: first argument pointer to data, second argument: size in bytes
	m_vbo.allocate(vertexBufferData.data(), vertexBufferData.size() * sizeof(float));
std::cout << glGetError() << std::endl;
	// create and bind Vertex Array Object - must be bound *before* the element buffer is bound,
	// because the VAO remembers and manages element buffers as well
	m_vao.create();
std::cout << glGetError() << std::endl;
	m_vao.bind();
std::cout << glGetError() << std::endl;
	/*
	unsigned int indices[] = {// note that we start from 0!
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
							  33, 34, 35};
	*/
	// create a new buffer for the indexes
	m_indexBufferObject = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer); // Mind: use 'IndexBuffer' here
	m_indexBufferObject.create();
std::cout << glGetError() << std::endl;
	m_indexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
std::cout << glGetError() << std::endl;
	m_indexBufferObject.bind();
std::cout << glGetError() << std::endl;
	//O segundo argumento deveria ser aquele mesmo???
	m_indexBufferObject.allocate(indices, sizeof(indices)/*indicesVector->size()*/);

	
	//std::cout<<sizeof(indices) <<std::endl;
	// stride = number of bytes for one vertex (with all its attributes) = 3+3 floats = 6*4 = 24 Bytes
	int stride = 6 * sizeof(float);

	// layout location 0 - vec3 with coordinates
	m_program->enableAttributeArray(0);
std::cout << glGetError() << std::endl;
	m_program->setAttributeBuffer(0, GL_FLOAT, 0,3, stride);
	std::cout << glGetError() << std::endl;
	// m_program->setUniformValue(matrixLocation, *m_projection);

	// m_program->setUniformValue(rotLocation, *rot);
	// m_program->setUniformValue(matrixLocation, *m_projection);

	// layout location 1 - vec3 with colors
	m_program->enableAttributeArray(1);
	std::cout << glGetError() << std::endl;

	int colorOffset = 3 * sizeof(float);
	m_program->setAttributeBuffer(1, GL_FLOAT, colorOffset, 3, stride);
std::cout << glGetError() << std::endl;
	// Release (unbind) all

	m_vbo.release();
std::cout << glGetError() << std::endl;
	m_vao.release();
std::cout << glGetError() << std::endl;
}

void GLWidget::resizeGL(int w, int h)
{
	// Update projection matrix and other size related settings:
	std::cout<<"proj\n";
	m_projection->setToIdentity();

	std::cout<<"dps proj\n";
	m_projection->perspective(45.0f, w / float(h), 0.01f, 100.0f);
}

void GLWidget::paintGL()
{
	// set the background color = clear color

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
	glDrawElements(GL_LINES, indicesVector->size(), GL_UNSIGNED_INT, 0);
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
void GLWidget::treeWalk(Node *root)
{
	indicesVector->push_back(root->getIndex(PointLabel::TLB));
	indicesVector->push_back(root->getIndex(PointLabel::TRB));
	indicesVector->push_back(root->getIndex(PointLabel::BLB));
	indicesVector->push_back(root->getIndex(PointLabel::BRB));
	indicesVector->push_back(root->getIndex(PointLabel::TLB));
	indicesVector->push_back(root->getIndex(PointLabel::BLB));
	indicesVector->push_back(root->getIndex(PointLabel::TRB));
	indicesVector->push_back(root->getIndex(PointLabel::BRB));

	indicesVector->push_back(root->getIndex(PointLabel::TLF));
	indicesVector->push_back(root->getIndex(PointLabel::TRF));
	indicesVector->push_back(root->getIndex(PointLabel::BLF));
	indicesVector->push_back(root->getIndex(PointLabel::BRF));
	indicesVector->push_back(root->getIndex(PointLabel::TLF));
	indicesVector->push_back(root->getIndex(PointLabel::BLF));
	indicesVector->push_back(root->getIndex(PointLabel::TRF));
	indicesVector->push_back(root->getIndex(PointLabel::BRF));

	indicesVector->push_back(root->getIndex(PointLabel::BLB));
	indicesVector->push_back(root->getIndex(PointLabel::BLF));
	indicesVector->push_back(root->getIndex(PointLabel::TLF));
	indicesVector->push_back(root->getIndex(PointLabel::TLB));
	indicesVector->push_back(root->getIndex(PointLabel::BRB));
	indicesVector->push_back(root->getIndex(PointLabel::BRF));
	indicesVector->push_back(root->getIndex(PointLabel::TRF));
	indicesVector->push_back(root->getIndex(PointLabel::TRB));

	if (root->getState() != State::GRAY)
	{
		return;
	}
	for (int i = 0; i < 8; i++)
	{
		treeWalk(root->getChild(i));
	}

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	//*m_projection = 2 * (*m_projection);
	std::cout << "dadada\n";
	update();
}

void GLWidget::setOctTree(OctTree *octtree)
{
	this->octtree = octtree;
}