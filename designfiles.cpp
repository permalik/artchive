#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <filesystem>
#include <fstream>
#include <QString>
#include <QVariant>
// #include <string>
#include <sys/stat.h>
#include <unistd.h>
#include "designfiles.h"

namespace fs = std::filesystem;

// /Users/tymalik/Documents/git/artchive_data

// std::vector<std::string> parse_git_status(std::string dir_path, std::string git_status_file, std::string redirect_command, std::string parsing_string) {
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

std::string sys_file_path() {
    std::string current_user;
    if (const char* system_user = std::getenv("USER")) {
        current_user = std::string(system_user);
    }
    return "/Users/" + current_user + "/artchive_directory_path.txt";
}

std::string bak_file_path() {
    std::string current_user;
    if (const char* system_user = std::getenv("USER")) {
        current_user = std::string(system_user);
    }
    return "/Users/" + current_user + "/artchive_directory_path.txt.bak";
}

void chown_chmod(const fs::path& file_path) {
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

DesignFiles::DesignFiles(QObject *parent) : QObject{parent} {
    m_dir_path = init_directory_path();
    // const std::string dir_path = "/Users/tymalik/Documents/git/artchive_data";

    // const std::string git_status_file = "git_status.txt";

    // std::string redirect_new_file = "cd " + dir_path +
    //                                 " && git status | grep " + "'new file:'" +
    //                                 " > " + git_status_file;
    // std::string parsing_string = "\tnew file:/ / / ";
    // std::vector<std::string> new_files = parse_git_status(
    //     dir_path, git_status_file, redirect_new_file, parsing_string);

    // const fs::path path{dir_path};
    // for (const auto &file : fs::directory_iterator(path)) {
    //     QString file_name =
    //         QString::fromStdString(file.path().filename().string());

    //     d_files.append(file_name);
    //     file_colors.append("blue");
    //     }

    //     std::sort(d_files.begin(), d_files.end(), [](const QString &a, const QString &b) {
    //         return a < b;
    //     });
    // }
}

QString DesignFiles::dir_path() const {
    return m_dir_path;
}

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
        std::string redirect_cmd = "echo \"" + dir_path.toStdString() + "\" > " + redirect_file_path;
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
    }
}

QStringList DesignFiles::items() const {
    return d_files;
}

QVector<QColor> DesignFiles::colors() const {
    return file_colors;
}
