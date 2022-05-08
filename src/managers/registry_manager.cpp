#include "registry_manager.hpp"

#include <QSettings>

std::unordered_map<QString, Program> RegistryManager::available_programs_ = {};

const std::unordered_map<QString, Program> &RegistryManager::GetAvailablePrograms() {
//    available_programs_.emplace(Program{"some_name", "some_version", "some_path"});
    return available_programs_;
}

void RegistryManager::AddProgram(std::string &&program_name,
                                 std::string &&program_version,
                                 std::string &&program_path) {

}

void RegistryManager::UpdateProgram(const std::string &program_name,
                                    const std::string &program_version,
                                    std::string &&new_program_version) {

}

void RegistryManager::DeleteProgram(const std::string &program_name,
                                    const std::string &program_version) {

}


