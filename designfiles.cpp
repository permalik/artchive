#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <filesystem>
#include <fstream>
#include <QString>
#include <string>
#include <sys/stat.h>
#include "designfiles.h"

namespace fs = std::filesystem;

DesignFiles::DesignFiles(DesignDirectory *designDirectory, QObject *parent) : QObject{parent} {
    if (designDirectory) {
        const QString dir_path = designDirectory->dir_path();
        const std::string git_status_file = "git_status.txt";

        file_colors = {QColor(Qt::red),  QColor(Qt::green),
                       QColor(Qt::blue), QColor(Qt::yellow),
                       QColor(Qt::cyan), QColor(Qt::magenta),
                       QColor(Qt::gray), QColor(Qt::black)};

        std::string redirect_git_status =
            "cd " + dir_path.toStdString() + " && git status | grep " +
                                          "'new file:'" + " > " + git_status_file;
        int result = std::system(redirect_git_status.c_str());
        if (result != 0) {
            qWarning() << "Failed to append redirect git_status: ";
    }

    std::ifstream file(dir_path.toStdString() + "/" + git_status_file);
    if (!file.is_open()) {
        qWarning() << "Cannot open git_status_file: ";
    }

    std::string line;
    while (std::getline(file, line)) {
        qDebug() << line;
    }

    file.close();

    const fs::path path{dir_path.toStdString()};
    for (const auto& file : fs::directory_iterator(path)) {
        QString file_name = QString::fromStdString(file.path().filename().string());

        d_files.append(file_name);
        // if (file_name.endsWith(".psd")) {
        //     file_colors.append(Qt::blue);
        // } else if (file_name.endsWith(".fig")) {
        //     file_colors.append(Qt::green);
        // } else {
        //     file_colors.append(Qt::black);
        // }
        // file_colors.append(Qt::blue);
        // file_colors.append(Qt::yellow);
        // file_colors.append(Qt::red);
        // file_colors.append(Qt::green);
        // file_colors.append(Qt::black);
        // file_colors.append(Qt::blue);
    }
    std::sort(d_files.begin(), d_files.end(), [](const QString &a, const QString &b) {
        return a < b;
    });
    } else {
        qWarning() << "DesignDirectory instance is null: ";
    }
}

QStringList DesignFiles::items() const {
    return d_files;
}

QVector<QColor> DesignFiles::colors() const {
    return file_colors;
}
