#include <cstdlib>
#include <cstring>
#include <dirent.h>
// #include <filesystem>
// #include <fstream>
#include <QString>
#include <QVariant>
// #include <string>
#include <sys/stat.h>
#include "designfiles.h"

namespace fs = std::filesystem;

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

DesignFiles::DesignFiles(QObject *parent) : QObject{parent} {
    m_dir_path = QString::fromStdString("Set directory path.");
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

void DesignFiles::set_dir_path(const QString &dir_path) {
    if (m_dir_path != dir_path) {
        m_dir_path = dir_path;
        emit dir_path_changed();
    }
}

QStringList DesignFiles::items() const {
    return d_files;
}

QVector<QColor> DesignFiles::colors() const {
    return file_colors;
}
