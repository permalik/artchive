#include <cstring>
#include <dirent.h>
#include <filesystem>
#include <sys/stat.h>
#include "designfiles.h"

namespace fs = std::filesystem;

DesignFiles::DesignFiles(QObject *parent) : QObject{parent} {

    // TODO: Get from db
    const fs::path path{"/Users/au4/git/artchive/data"};

    for (const auto& file : fs::directory_iterator(path)) {
        QString file_name = QString::fromStdString(file.path().filename().string());

        d_files.append(file_name);
    }

    std::sort(d_files.begin(), d_files.end(), [](const QString &a, const QString &b) {
        return a < b;
    });
}

QStringList DesignFiles::items() const {
    return d_files;
}
