#include <QColor>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <filesystem>
#include <fstream>
// #include <string>
#include "designfiles.h"
#include <sys/stat.h>
#include <unistd.h>

namespace fs = std::filesystem;

// /Users/tymalik/Documents/git/artchive_data

std::string sys_file_path() {
    std::string current_user;
    if (const char *system_user = std::getenv("USER")) {
        current_user = std::string(system_user);
    }
    return "/Users/" + current_user + "/.config/artchive_directory_path.txt";
}

std::string bak_file_path() {
    std::string current_user;
    if (const char *system_user = std::getenv("USER")) {
        current_user = std::string(system_user);
    }
    return "/Users/" + current_user + "/.config/artchive_directory_path.txt.bak";
}

void chown_chmod(const fs::path &file_path) {
    uid_t current_uid = getuid();
    gid_t current_gid = getgid();

    if (chown(file_path.c_str(), current_uid, current_gid) != 0) {
        qWarning() << "Failed to change ownership: " << strerror(errno);
        return;
    }

    if (chmod(file_path.c_str(), S_IRUSR | S_IWUSR) != 0) {
        qWarning() << "Failed to change permissions: " << strerror(errno);
        return;
    }
}

QString init_directory_path() {
    const std::string dir_file_path = sys_file_path();
    chown_chmod(dir_file_path);
    std::ifstream file(dir_file_path);
    if (!file.is_open()) {
        qWarning() << "Cannot open directory_path.txt: ";
    }

    std::string file_path;
    std::string line;
    while (std::getline(file, line)) {
        file_path = line;
    }

    file.close();
    return QString::fromStdString(file_path);
}

QString DesignFiles::dir_path() const { return m_dir_path; }

// TODO: system error handling
void DesignFiles::set_dir_path(const QString &dir_path) {
    if (m_dir_path != dir_path) {
        m_dir_path = dir_path;

        std::string move_file_path = sys_file_path();
        std::string mv_cmd = "mv " + move_file_path + " " + move_file_path + ".bak";
        chown_chmod(move_file_path);
        int move_res = std::system(mv_cmd.c_str());
        if (move_res != 0) {
            qWarning() << "Failed to move move_file_path: ";
        }

        std::string redirect_file_path = sys_file_path();
        std::string redirect_cmd =
            "echo \"" + dir_path.toStdString() + "\" > " + redirect_file_path;
        int redirect_res = std::system(redirect_cmd.c_str());
        if (redirect_res != 0) {
            qWarning() << "Failed to redirect redirect_file_path: ";
        }

        std::string remove_file_path = bak_file_path();
        chown_chmod(remove_file_path);
        std::string remove_cmd = "rm " + remove_file_path;
        int remove_res = std::system(remove_cmd.c_str());
        if (remove_res != 0) {
            qWarning() << "Failed to remove bak_file_path: ";
        }

        emit dir_path_changed();
        items();
    }
}

    // const std::string git_status_file = "git_status.txt";

    // std::string redirect_new_file = "cd " + dir_path +
    //                                 " && git status | grep " + "'new file:'" +
    //                                 " > " + git_status_file;
    // std::string parsing_string = "\tnew file:/ / / ";
    // std::vector<std::string> new_files = parse_git_status(
    //     dir_path, git_status_file, redirect_new_file, parsing_string);
// std::vector<std::string> git_status(std::string dir_path, std::string
// git_status_file, std::string redirect_command, std::string parsing_string) {
//     int result = std::system(redirect_command.c_str());
//     if (result != 0) {
//         qWarning() << "Failed to redirect git_status: ";
//     }
//
//     std::ifstream file(dir_path + "/" + git_status_file);
//     if (!file.is_open()) {
//         qWarning() << "Cannot open git_status_file: ";
//     }
//
//     std::string line;
//     std::vector<std::string> file_list;
//     while (std::getline(file, line)) {
//         line = line.find(parsing_string);
//
//         qDebug() << "file_name: " << line;
//         file_list.push_back(line);
//     }
//
//     file.close();
//     return file_list;
// }

void DesignFiles::design_assets() {
    std::vector<std::string> all_files;
    const fs::path path{m_dir_path.toStdString()};
    if (fs::exists(m_dir_path.toStdString()) && fs::is_directory(m_dir_path.toStdString())) {
        for (const std::filesystem::directory_entry &file : fs::directory_iterator(path)) {
            std::string file_name = file.path().filename().string();

            all_files.push_back(file_name);
            qDebug() << "init file_name: " << file_name;
        }
    } else {
        qWarning() << "Path does not exist or is not a directory: ";
    }

    std::vector<std::tuple<std::string, std::string>> assets(all_files.size());
    for (size_t i = 0; i < all_files.size(); i++) {
        assets[i] = std::make_tuple(all_files[i], "red");
    }

    for (auto& asset : assets) {
        qDebug() << "assets file_name: " << std::get<0>(asset);
    }
}

// TODO: sort asset_map
// std::sort(all_files.begin(), all_files.end(), [](const QString &a, const QString &b) { return a < b; });

QStringList DesignFiles::items() {
    design_assets();
    QStringList files;
    int i = 0;
    qDebug() << "Processing items";
    for (auto& asset : assets) {
        QString file_name = QString::fromStdString(std::get<0>(asset));
        files[i] = file_name;
        i++;
    }

    d_files = files;
    emit items_changed();

    return d_files;
}

QVector<QColor> DesignFiles::colors() const { return file_colors; }

DesignFiles::DesignFiles(QObject *parent) : QObject{parent} {
    m_dir_path = init_directory_path();
}
