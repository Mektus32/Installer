#include "registry_manager.hpp"

#include <QSettings>

std::unordered_map<QString, Program> RegistryManager::available_programs_ = {};

const std::unordered_map<QString, Program> &RegistryManager::GetAvailablePrograms() {
    available_programs_["programName"] = Program{"programName", {"v1"}};
    return available_programs_;
}

void RegistryManager::AddProgram(QString &&program_name,
                                 QString &&program_version,
                                 QString &&program_path) {

}

std::optional<QString> RegistryManager::UpdateProgram(const QString &program_name,
                                    const QString &program_version,
                                    const QString &new_program_version) {

}

std::optional<QString> RegistryManager::DeleteProgram(const QString &program_name,
                                    const QString &program_version) {

}

std::optional<QString> RegistryManager::GetProgramPath(const QString& program_name,
                                      const QString& program_version) {
}


