#include "registry_manager.hpp"

#include <QSettings>

std::unordered_map<QString, Program> RegistryManager::available_programs_ = {};
QString RegistryManager::register_path_{"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\TInstaller"};

const std::unordered_map<QString, Program> &RegistryManager::GetAvailablePrograms() {
    if (!available_programs_.empty()) {
        return available_programs_;
    }
    QSettings settings(register_path_, QSettings::NativeFormat);
    QStringList key_list = settings.allKeys();
    for(const auto& key : key_list) {
        available_programs_[settings.value(key).toString()];
    }
    return available_programs_;
}

void RegistryManager::AddProgram(QString &&program_name,
                                 QString &&program_version,
                                 QString &&program_path) {
    QSettings settings(register_path_, QSettings::NativeFormat);

    settings.beginWriteArray("programs");
    settings.setArrayIndex(static_cast<int>(available_programs_.size()));
    settings.setValue("program_name", std::move(program_name));
    settings.setValue("program_version", std::move(program_version));
    settings.setValue("program_path", std::move(program_path));
    settings.endArray();
}

std::optional<QString> RegistryManager::UpdateProgram(const QString &program_name,
                                    const QString &program_version,
                                    const QString &new_program_version) {
    QSettings settings(register_path_, QSettings::NativeFormat);

    settings.beginWriteArray("programs");
    for (int i = 0; i < available_programs_.size(); ++i) {
        if (!available_programs_.count(program_name)) {
            continue;
        }
        settings.setArrayIndex(i);
        settings.setValue("program_name", program_name);
        settings.setValue("program_version", new_program_version);
        settings.setValue("program_path", available_programs_[program_name].installed_versions_paths.value()[program_version]);
        settings.endArray();
        break;
    }
    return available_programs_[program_name].installed_versions_paths.value()[program_version];
}

std::optional<QString> RegistryManager::DeleteProgram(const QString &program_name,
                                    const QString &program_version) {
    QSettings settings(register_path_, QSettings::NativeFormat);
    settings.remove(program_version);
    return program_name;
}

std::optional<QString> RegistryManager::GetProgramPath(const QString& program_name,
                                      const QString& program_version) {
    if (available_programs_.count(program_name) &&
            available_programs_[program_name].installed_versions_paths &&
            available_programs_[program_name].installed_versions_paths.value().count(program_version)) {
        return available_programs_[program_name].installed_versions_paths.value()[program_version];
    }
    return std::nullopt;
}


