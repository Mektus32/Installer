#include "utils.hpp"

#include <filesystem>
#include <regex>
#include <cstdlib>
#include <random>

#include <QMessageBox>
#include <private/qzipreader_p.h>

#include <managers/network_manager.hpp>
#include <managers/registry_manager.hpp>

namespace {

namespace fs = std::filesystem;
#if defined(__WIN32__)

#include <windows.h>
#include <Lmcons.h>

std::string GetDesktopFileName(const std::string& file_name) {
    char username[UNLEN+1];
    DWORD username_len = UNLEN+1;
    GetUserName(username, &username_len);

  return std::string("/users/") + username + "/desktop/" + file_name;
}

#else

#include <unistd.h>

std::string GetDesktopFileName(const std::string& file_name) {
    return std::string(std::getenv("HOME")) + "/Desktop/" + file_name;
}

#endif

std::string RandomString()
{
    static auto& chrs = "0123456789"
                        "abcdefghijklmnopqrstuvwxyz"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static std::mt19937 rg{std::random_device{}()};
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    std::size_t length{10};
    s.reserve(length);

    while(length--)
        s += chrs[pick(rg)];

    return s;
}
}

void ShowMessage(const QString &str) {
    QMessageBox messageBox;
    messageBox.setText(str);
    messageBox.exec();
}

std::optional<QString> UnzipFileInDirGetDir(const QString &file_path, const QString &dir) {
    QZipReader reader{file_path};
    if (reader.exists()) {
        reader.extractAll(dir);
        return dir;
    }
    return std::nullopt;
}

void CreateLinkToExec(const QString &dir, const QString& name) {
    namespace fs = std::filesystem;
    const std::regex base_regex((name.split('_')[0] + ".exe").toStdString());
    for (const auto &entry: fs::recursive_directory_iterator(dir.toStdString())) {
        if (std::regex_search(entry.path().string(), base_regex)) {
            const auto desktop_file_name = GetDesktopFileName(name.toStdString());
            if (fs::exists(desktop_file_name)) {
                fs::remove(desktop_file_name);
            }
            fs::create_symlink(entry.path().string(), desktop_file_name);
            break;
        }
    }
}

void DeleteLinkToExec(const QString& program_name, const QString& version) {
    fs::remove(GetDesktopFileName((program_name + '_' + version).toStdString()));
}

std::optional<QString> UpdateProgram(const QString& program_name, const QString& version,
                   const QString& new_version) {
    const auto &[zip_file, error] = NetworkManager::GetArchiveFile(program_name, new_version);
    if (error) {
        return error;
    }

    const auto& tmp_dir = fs::temp_directory_path().string() + '/' + RandomString();
    const auto& dir = UnzipFileInDirGetDir(*zip_file, tmp_dir.c_str());
    if (!dir) {
        return "Can`t get new program version";
    }
    const auto& current_path = RegistryManager::UpdateProgram(program_name, version, new_version);
    if (!current_path) {
        return "Can`t update program. Try to start program from Administrator.";
    }
    if (fs::remove(current_path->toStdString()) && fs::create_directories(current_path->toStdString())) {
        DeleteLinkToExec(program_name, version);
        fs::copy(tmp_dir, current_path->toStdString(), fs::copy_options::recursive);
    } else {
        return "Can`t update program. Try to start program from Administrator.";
    }
    fs::remove(tmp_dir);
    return std::nullopt;
}
