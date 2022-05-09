#pragma once

#include <QString>

void ShowMessage(const QString& str);
std::optional<QString> UnzipFileInDirGetDir(const QString& file_path, const QString& dir);
void CreateLinkToExec(const QString& dir);