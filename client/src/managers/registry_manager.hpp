#pragma once

#include <unordered_map>

#include <types/types.hpp>

class RegistryManager {
public:
    static const std::unordered_map<QString, Program>& GetAvailablePrograms();
    static void AddProgram(QString&& program_name,
                    QString&& program_version,
                    QString&& program_path);
    static std::optional<QString> UpdateProgram(const QString& program_name,
                       const QString& program_version,
                       const QString& new_program_version);
    static std::optional<QString> DeleteProgram(const QString& program_name,
                       const QString& program_version);
    static std::optional<QString> GetProgramPath(const QString& program_name,
                                                 const QString& program_version);
private:
    static std::unordered_map<QString, Program> available_programs_;
};