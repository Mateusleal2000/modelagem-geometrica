#include "GLWidget.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

void createIndexFile(std::vector<unsigned int> *indicesVector, std::vector<float> *verticesVector)
{
	std::ofstream MyFile("closeGL.obj", std::ios::app);

	// ISSO AQUI GERA OS PONTOS
	for (int i = 0; i < verticesVector->size(); i += 3)
	{
		MyFile << std::setprecision(4) << "v " << verticesVector->at(i) << " " << verticesVector->at(i + 1) << " " << verticesVector->at(i + 2) << "\n";
	}

	// ISSO AQUI GERA AS ARESTAS
	for (int i = 0; i < indicesVector->size(); i += 2)
	{
		MyFile << "l " << indicesVector->at(i) + 1 << " " << indicesVector->at(i + 1) + 1 << "\n";
	}
}

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), m_program(0), m_shader(0)
{
	verticesVector = new std::vector<float>();
	indicesVector = new std::vector<unsigned int>();
	colorVector = new std::vector<QColor>();
	m_projection = new QMatrix4x4();
	m_projection->perspective(45.0f, 640.0 / float(480), 0.01f, 100.0f);
}

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
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	// glEnable(GL_NORMALIZE);
	//  build and compile our shader program
	//  ------------------------------------
	// glEnable(GL_NORMALIZE);
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
	std::vector<Point3> *vv = octtree->getGlobalVerticesVector();
	for (int i = 0; i < vv->size(); i++)
	{
		verticesVector->push_back(vv->at(i).x());
		verticesVector->push_back(vv->at(i).y());
		verticesVector->push_back(vv->at(i).z());
		colorVector->push_back(QColor("#49eb34"));
	}

	float *vertices = verticesVector->data();


	QColor *vertexColors = colorVector->data();

	Node *root = octtree->getRoot();
	treeWalk(root);

	createIndexFile(indicesVector, verticesVector);

	unsigned int *indices = indicesVector->data();

	// Camera matrices creation
	//-------------------------------------------

	QMatrix4x4 viewMatrix;
	// viewMatrix.rotate(30, 0, 1, 0);
	//viewMatrix.rotate(30, 1, 0, 0);
	viewMatrix.translate(0, 0, 30);
	viewMatrix = viewMatrix.inverted();

	QMatrix4x4 modelMatrix;
	//modelMatrix.rotate(45,0,0,1);

	int projectionMatrixLocation = m_program->uniformLocation("projectionMatrix");
	int modelMatrixLocation = m_program->uniformLocation("modelMatrix");
	int viewMatrixLocation = m_program->uniformLocation("viewMatrix");

	// create buffer for 2 interleaved attributes: position and color, 4 vertices, 3 floats each
	// std::vector<float> vertexBufferData(2*4*3);
	std::vector<float> vertexBufferData(2 * vv->size() * 3);

	std::cout << vv->size() << std::endl;

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
	m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_vbo.bind();

	// now copy buffer data over: first argument pointer to data, second argument: size in bytes
	m_vbo.allocate(vertexBufferData.data(), vertexBufferData.size() * sizeof(float));
	std::cout << glGetError() << std::endl;
	// create and bind Vertex Array Object - must be bound *before* the element buffer is bound,
	// because the VAO remembers and manages element buffers as well
	m_vao.create();
	m_vao.bind();

	// create a new buffer for the indexes
	m_indexBufferObject = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer); // Mind: use 'IndexBuffer' here
	m_indexBufferObject.create();
	m_indexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_indexBufferObject.bind();
	// O segundo argumento deveria ser aquele mesmo???
	m_indexBufferObject.allocate(indices,  indicesVector->size()*sizeof(unsigned int));

	// std::cout<<sizeof(indices) <<std::endl;
	//  stride = number of bytes for one vertex (with all its attributes) = 3+3 floats = 6*4 = 24 Bytes
	int stride = 6 * sizeof(float);

	// layout location 0 - vec3 with coordinates
	m_program->enableAttributeArray(0);
	m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, stride);

	m_program->setUniformValue(modelMatrixLocation, modelMatrix);
	m_program->setUniformValue(viewMatrixLocation, viewMatrix);
	m_program->setUniformValue(projectionMatrixLocation, *m_projection);

	// layout location 1 - vec3 with colors
	m_program->enableAttributeArray(1);

	int colorOffset = 3 * sizeof(float);
	m_program->setAttributeBuffer(1, GL_FLOAT, colorOffset, 3, stride);
	// Release (unbind) all

	m_vbo.release();
	m_vao.release();
}

void GLWidget::resizeGL(int w, int h)
{
	// Update projection matrix and other size related settings:
	m_projection->setToIdentity();

	m_projection->perspective(45.0f, w / float(h), 0.01f, 100.0f);
}

void GLWidget::paintGL()
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
	//m_indexBufferObject.bind();

	// now draw the two triangles via index drawing
	// - GL_TRIANGLES - draw individual triangles via elements
	// glDrawArrays(GL_QUADS, 0, 24);
	std::cout << indicesVector->size() << std::endl;
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