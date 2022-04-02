#ifndef FINISH_HPP
#define FINISH_HPP

#include <QWidget>

namespace Ui {
class finish;
}

class Finish : public QWidget
{
    Q_OBJECT

public:
    explicit Finish(QWidget *parent = nullptr);
    ~Finish();

private:
    Ui::finish *ui;
};

#endif // FINISH_HPP
