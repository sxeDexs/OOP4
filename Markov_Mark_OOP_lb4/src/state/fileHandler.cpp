#include "fileHandler.h"

void FileHandler::openForRead() {
    infile.open(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file for reading.");
    }
}

void FileHandler::openForWrite() {
    outfile.open(filename);
    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open file for writing.");
    }
}

void FileHandler::write(const json& j) {
    if (outfile.is_open()) {
        outfile << j.dump(4);
    } else {
        throw std::runtime_error("File not open for writing.");
    }
}

void FileHandler::read(json& j) {
    if (infile.is_open()) {
        infile >> j;
    } else {
        throw std::runtime_error("File not open for reading.");
    }
}

void FileHandler::closeRead() {
    if (infile.is_open()) {
        infile.close();
    }
}

void FileHandler::closeWrite() {
    if (outfile.is_open()) {
        outfile.close();
    }
}