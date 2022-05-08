#pragma once

#include "abstract_screen.hpp"

namespace Ui {
class program_choose;
}

class ProgramChoose : public AbstractScreen
{
    Q_OBJECT

public:
    explicit ProgramChoose(QWidget *parent, AbstractScreen* previous, Functional functional, const QString& dir = "");
    ~ProgramChoose();
    void UpdateButtonsState(Buttons& buttons) override;
    AbstractScreen* MakeActionAndChangeState() override;

private slots:
    void on_program_name_currentIndexChanged(int index);

    void on_program_version_currentIndexChanged(int index);

    void on_new_program_version_currentIndexChanged(int index);

private:
    Ui::program_choose *ui_;
    const Functional functional_;
    const QString& dir_;
    std::vector<Program> programs_;
    std::unordered_map<QString, std::vector<QString>> new_program_versions_;
};
