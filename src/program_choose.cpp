#include "program_choose.hpp"
#include "ui_program_choose.h"
#include "finish.hpp"

#include <filesystem>
#include <regex>

#include <managers/registry_manager.hpp>
#include <managers/network_manager.hpp>
#include <utils/utils.hpp>


ProgramChoose::ProgramChoose(QWidget *parent, AbstractScreen *previous,
                             Functional functional, const QString &dir /* = "" */) :
        AbstractScreen(parent, previous),
        ui_(new Ui::program_choose),
        functional_(functional),
        dir_(dir) {
    ui_->setupUi(this);
    {
        std::unordered_map<QString, Program> programs;
        if (functional_ == Functional::kUpdate) {
            programs = RegistryManager::GetAvailablePrograms();
            const auto &[available_programs, error] = NetworkManager::GetAvailablePrograms();
            if (error) {
                ShowMessage(*error);
                exit(3);
            }
            for (const auto &available_program: available_programs) {
                if (programs.count(available_program.first)) {
                    new_program_versions_[available_program.first] = available_program.second.versions;
                    for (auto it = new_program_versions_[available_program.first].begin();
                         it != new_program_versions_[available_program.first].end(); ++it) {
                        for (const auto &current_version: programs.at(available_program.first).versions) {
                            if (*it == current_version) {
                                it = new_program_versions_[available_program.first].erase(it);
                            }
                        }
                    }
                }
            }
        } else {
            ui_->new_version_caption->hide();
            ui_->new_program_version->hide();
            ui_->new_version_caption->setDisabled(true);
            ui_->new_program_version->setDisabled(true);
            std::unordered_map<QString, Program> new_programs;
            if (functional_ == Functional::kDelete) {
                programs = RegistryManager::GetAvailablePrograms();
                if (programs.empty()) {
                    ShowMessage("Unexpected state. No programs to delete. Installer will be closed!");
                    exit(1);
                }
            } else if (functional_ == Functional::kInstall) {
                const auto &[available_programs, error] = NetworkManager::GetAvailablePrograms();
                if (error) {
                    ShowMessage(*error);
                    exit(3);
                }
                new_programs = available_programs;
            } else {
                ShowMessage("Unexpected state. Installer will be closed!");
                exit(2);
            }
            programs.merge(new_programs);
        }
        std::transform(programs.begin(), programs.end(), std::back_inserter(programs_), [](const auto &value) {
            return value.second;
        });
    }
    QList<QString> inserts;
    std::transform(programs_.begin(), programs_.end(), std::back_inserter(inserts), [](const Program &program) {
        return program.name;
    });
    ui_->program_name->addItems(inserts);
    ui_->program_version->addItems({programs_.begin()->versions.begin(), programs_.begin()->versions.end()});
    if (!new_program_versions_.empty()) {
        ui_->new_program_version->addItems({new_program_versions_.at(programs_[0].name).begin(),
                                            new_program_versions_.at(programs_[0].name).end()});
    }
}

ProgramChoose::~ProgramChoose() {
    delete ui_;
}

void ProgramChoose::on_program_name_activated(int index) {
    if (index == -1) { return; }
    if (index < programs_.size()) {
        ui_->program_version->clear();
        ui_->program_version->addItems({programs_[index].versions.begin(), programs_[index].versions.end()});
        ui_->program_version->setCurrentIndex(0);
        if (new_program_versions_.count(programs_[index].name)) {
            ui_->new_program_version->addItems({new_program_versions_.at(programs_[index].name).begin(),
                                                new_program_versions_.at(programs_[index].name).end()});
            ui_->new_program_version->setCurrentIndex(0);
        }
    } else {
        ShowMessage("Unexpected program index{name}. Installer will be closed!");
        exit(2);
    }
}

void ProgramChoose::UpdateButtonsState(Buttons &buttons) {
}

AbstractScreen *ProgramChoose::MakeActionAndChangeState() {
    QString program_name, program_version;
    switch (functional_) {
        namespace fs = std::filesystem;
        case Functional::kInstall: {
            program_name = ui_->program_name->currentText();
            program_version = ui_->program_version->currentText();
            const auto &[zip_file, error] = NetworkManager::GetArchiveFile(program_name, program_version);
            if (error) {
                ShowMessage(*error);
                return this;
            }
            if (auto dir = UnzipFileInDirGetDir(*zip_file, dir_); dir) {
                CreateLinkToExec(*dir, program_name + '_' + program_version);
                RegistryManager::AddProgram(std::move(program_name), std::move(program_version), std::move(*dir));
            } else {
                ShowMessage("Can`t install program. Try to start program from Administrator.");
            }
        } break;
        case Functional::kDelete:
            program_name = ui_->program_name->currentText();
            program_version = ui_->program_version->currentText();
            if (const auto &path = RegistryManager::DeleteProgram(ui_->program_name->currentText(),
                                                                  ui_->program_version->currentText()); path
                                                                  && fs::remove(path->toStdString())) {
                DeleteLinkToExec(program_name, program_version);
                ShowMessage("Program successfully deleted.");
            } else {
                ShowMessage("Can`t delete program. Try to start program from Administrator.");
            }
            break;
        case Functional::kUpdate: {
            program_name = ui_->program_name->currentText();
            program_version = ui_->new_program_version->currentText();
            const auto& error = UpdateProgram(ui_->program_name->currentText(), ui_->program_version->currentText(),
                                              ui_->new_program_version->currentText());
            if (error) {
                ShowMessage(*error);
                return this;
            }
        } break;
        default:
            ShowMessage("Unexpected state. Installer will be closed!");
            exit(2);
    }

    return new Finish(parent_, this);
}
