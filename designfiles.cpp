#include <cstring>
#include <dirent.h>
#include <filesystem>
#include <QString>
#include <sys/stat.h>
#include "designfiles.h"

namespace fs = std::filesystem;

DesignFiles::DesignFiles(DesignDirectory *designDirectory, QObject *parent) : QObject{parent} {
    if (designDirectory) {
    const QString dir_path = designDirectory->dir_path();
    const fs::path path{dir_path.toStdString()};
    for (const auto& file : fs::directory_iterator(path)) {
        QString file_name = QString::fromStdString(file.path().filename().string());

        d_files.append(file_name);
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
