#ifndef GL_WIDGET_H
#define GL_WIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QEvent>
#include <QKeyEvent>
#include "Camera.hpp"
#include "OctTree.hpp"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	GLWidget(QWidget *parent = 0);
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void mousePressEvent(QMouseEvent *event);
	void setOctTree(OctTree *octtree);
	bool event(QEvent *event) override;
	void addSolid(Solid *solid);

signals:
	void leftClicked();
	void rightClicked();
	void upClicked();
	void downClicked();
	void upArrowClicked();
	void downArrowClicked();
	void mouseMoved(float xoffset, float yoffset);

public slots:
	void updateViewMatrix(QMatrix4x4 newView);
	void renderScene();

private:
	void treeWalk(Node *root);
	OctTree *octtree;
	std::vector<float> *verticesVector;
	std::vector<unsigned int> *indicesVector;
	std::vector<QColor> *colorVector;

	QMatrix4x4 *viewMatrix;
	QMatrix4x4 *lookatmatrix;
	QMatrix4x4 *m_projection;
	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
	// Index buffer to draw two rectangles
	QOpenGLBuffer m_indexBufferObject;
	QOpenGLShaderProgram *m_program;
	QOpenGLShader *m_shader;

	Camera camera;
};

#endif