#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class OptionsWidget : public QWidget
{
	Q_OBJECT
	public:
	OptionsWidget(QWidget * parent = 0);


	private:
	QHBoxLayout * layout;
  QPushButton * addSolidButton;
  // QPushButton * addDepthButton;
  // QPushButton * subtractDepthButton;
};