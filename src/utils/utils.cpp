#include "utils.hpp"

#include <filesystem>
#include <regex>

#include <QMessageBox>
#include <private/qzipreader_p.h>

void ShowMessage(const QString& str) {
    QMessageBox messageBox;
    messageBox.setText(str);
    messageBox.exec();
}

std::optional<QString> UnzipFileInDirGetDir(const QString& file_path, const QString& dir) {
    QZipReader reader{file_path};
    if (reader.exists()) {
        reader.extractAll(dir);
        return dir;
    }
    return std::nullopt;
}

void CreateLinkToExec(const QString& dir) {
    namespace fs = std::filesystem;
    const std::regex base_regex("\\.exe"); // TODO: maybe add program_name.exe?
    for (const auto& entry : fs::recursive_directory_iterator(dir.toStdString())) {
        if (std::regex_search(entry.path().string(), base_regex)) {
            // TODO: make link to desktop
            break;
        }
    }
}