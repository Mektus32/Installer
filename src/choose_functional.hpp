#ifndef CHOOSE_FUNCTIONAL_HPP
#define CHOOSE_FUNCTIONAL_HPP

#include <QWidget>

namespace Ui {
class choose_functional;
}

class ChooseFunctional : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseFunctional(QWidget *parent = nullptr);
    ~ChooseFunctional();

private:
    Ui::choose_functional *ui;
};

#endif // CHOOSE_FUNCTIONAL_HPP
