#include "designfiles.h"
#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>

DesignFiles::DesignFiles(QObject *parent) : QObject{parent} {
    const char* path = "/Users/au4/git/artchive/data";

    DIR* dir = opendir(path);
    if (dir == nullptr) {
        std::cerr << "Error: Unable to open directory." << std::endl;
    }

    struct dirent* file;
    struct stat fileStat;

    while ((file= readdir(dir)) != nullptr) {
        std::string fullPath = std::string(path) + "/" + file->d_name;

        if (stat(fullPath.c_str(), &fileStat) == -1) {
            std::cerr << "Error: Unable to stat: " << file->d_name << std::endl;
            continue;
        }

        // Skip "." and ".." entries
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
            continue;
        }

        d_files << file->d_name;
    }

    closedir(dir);

    std::sort(d_files.begin(), d_files.end());
}

QStringList DesignFiles::items() const {
    return d_files;
}
