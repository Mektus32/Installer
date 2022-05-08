#include "program_choose.hpp"
#include "ui_program_choose.h"
#include "finish.hpp"

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
                MakeError(*error);
                return;
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
                } else {
                    programs[available_program.first];
                    new_program_versions_[available_program.first] = available_program.second.versions;
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
                    MakeError("Unexpected state. No programs to delete. Installer will be closed!");
                    exit(1);
                }
            } else if (functional_ == Functional::kInstall) {
                const auto &[available_programs, error] = NetworkManager::GetAvailablePrograms();
                if (error) {
                    MakeError(*error);
                    return;
                }
                new_programs = available_programs;
            } else {
                MakeError("Unexpected state. Installer will be closed!");
                exit(2);
            }
            programs.merge(new_programs);
        }
        std::transform(programs.begin(), programs.end(), std::back_inserter(programs_), [](const auto& value){
            return value.second;
        });
    }
    ui_->program_name->clear();
    ui_->program_version->clear();
    ui_->new_program_version->clear();
    auto tmp = ui_->program_version->count();
    for (const auto& program : programs_) {
        ui_->program_name->addItem(program.name);
    }
    for (const auto& version : programs_.begin()->versions) {
        ui_->program_version->addItem(version);
        tmp = ui_->program_version->count();
    }
    tmp = ui_->program_version->count();
    if (!new_program_versions_.empty()) {
        for (const auto& new_version : new_program_versions_.at(programs_[0].name)) {
            ui_->new_program_version->addItem(new_version);
        }
        ui_->new_program_version->setCurrentIndex(0);
    }
    tmp = ui_->program_version->count();
    tmp = ui_->program_name->count();
    qDebug() << "dsfsdf";
}

ProgramChoose::~ProgramChoose() {
    delete ui_;
}

void ProgramChoose::on_program_name_currentIndexChanged(int index) {
    if (index < programs_.size()) {
        ui_->program_name->addItem(programs_[index].name);
        for (const auto &version: programs_[index].versions) {
            ui_->program_version->addItem(version);
        }
        ui_->program_version->setCurrentIndex(0);
        if (new_program_versions_.count(programs_[index].name)) {
            for (const auto &new_version: new_program_versions_.at(programs_[index].name)) {
                ui_->new_program_version->addItem(new_version);
            }
            ui_->new_program_version->setCurrentIndex(0);
        }
    } else {
        MakeError("Unexpected program index{name}. Installer will be closed!");
        exit(2);
    }
}


void ProgramChoose::on_program_version_currentIndexChanged(int index) {

}


void ProgramChoose::on_new_program_version_currentIndexChanged(int index) {

}

void ProgramChoose::UpdateButtonsState(Buttons &buttons) {
}

AbstractScreen *ProgramChoose::MakeActionAndChangeState() {
    return new Finish(parent_, this);
}
