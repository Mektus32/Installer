#pragma once

#include <unordered_map>

#include <types/types.hpp>

class RegistryManager {
public:
    static const std::unordered_map<QString, Program>& GetAvailablePrograms();
    static void AddProgram(std::string&& program_name,
                    std::string&& program_version,
                    std::string&& program_path);
    static void UpdateProgram(const std::string& program_name,
                       const std::string& program_version,
                       std::string&& new_program_version);
    static void DeleteProgram(const std::string& program_name,
                       const std::string& program_version);
private:
    static std::unordered_map<QString, Program> available_programs_;
};