
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

class testGL : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	testGL(QWidget *parent = 0);
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

private:
	std::vector<QColor> *colorVector;
	QMatrix4x4 *m_projection;
	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
	// Index buffer to draw two rectangles
	QOpenGLBuffer m_indexBufferObject;
	QOpenGLShaderProgram *m_program;
	QOpenGLShader *m_shader;
};