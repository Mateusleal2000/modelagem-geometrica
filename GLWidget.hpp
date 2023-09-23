#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	GLWidget(QWidget *parent = 0);
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

private:
	QMatrix4x4 m_projection;
	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
	// Index buffer to draw two rectangles
	QOpenGLBuffer m_indexBufferObject;
	QOpenGLShaderProgram *m_program;
	QOpenGLShader *m_shader;
};