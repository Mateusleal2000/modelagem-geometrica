#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include "OctTree.hpp"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	GLWidget(QWidget *parent = 0);
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void mousePressEvent(QMouseEvent *event);
	void setOctTree(OctTree *octtree);

private:
	void treeWalk(Node *root);
	OctTree *octtree;
	std::vector<float> *verticesVector;
	std::vector<unsigned int> *indicesVector;
	std::vector<QColor> *colorVector;
	QMatrix4x4 *m_projection;
	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
	// Index buffer to draw two rectangles
	QOpenGLBuffer m_indexBufferObject;
	QOpenGLShaderProgram *m_program;
	QOpenGLShader *m_shader;
};