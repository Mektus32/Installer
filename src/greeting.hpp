#ifndef GREETING_HPP
#define GREETING_HPP

#include <QWidget>

namespace Ui {
class Greeting;
}

class Greeting : public QWidget
{
    Q_OBJECT

public:
    explicit Greeting(QWidget *parent = nullptr);
    ~Greeting();

private:
    Ui::Greeting *ui;
};

#endif // GREETING_HPP
