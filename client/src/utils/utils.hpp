#pragma once

#include <QString>

void ShowMessage(const QString& str);
std::optional<QString> UnzipFileInDirGetDir(const QString& file_path, const QString& dir);
void CreateLinkToExec(const QString &dir, const QString& name);
void DeleteLinkToExec(const QString& program_name, const QString& version);
std::optional<QString> UpdateProgram(const QString& program_name, const QString& version,
                                     const QString& new_version);