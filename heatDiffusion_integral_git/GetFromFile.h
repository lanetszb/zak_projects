#ifndef GETFROMFILE_H
#define GETFROMFILE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


class GetFromFile { // класс для считывания данных из файла

public:

    GetFromFile(const std::string &fileName) : fileName(fileName) {};

    virtual ~GetFromFile() {};


    template<typename T>
    T getWord(const std::string &variableKey, const int &count); // метод для считывания слова с параметром

    template<typename T>
    T getWord(const std::string &variableKey); // метод для считывания слова без параметра

    template<typename T>
    std::vector<T> getVector(const std::string &variableKey); // метод для считывания вектора


private:

    std::string fileName;

};


template<typename T>
T GetFromFile::getWord(const std::string &variableKey, const int &count) {

    T variable;

    std::ifstream inStream;

    inStream.open(fileName.c_str());

    std::string word;

    while (inStream >> word)
        if (word == variableKey)
            break;


    for (int i = 0; i < count; i++)
        inStream >> word;

    inStream >> variable;

    inStream.close();

    return variable;

}


template<typename T>
T GetFromFile::getWord(const std::string &variableKey) {
    return getWord<T>(variableKey, 0);
}


template<typename T>
std::vector<T> GetFromFile::getVector(const std::string &variableKey) {

    std::vector<T> variable;

    std::ifstream inStream;

    inStream.open(fileName.c_str());

    std::string word;

    while (inStream >> word)
        if (word == variableKey)
            break;

    std::stringstream sStream;

    while (inStream >> word)
        if (word != "\\")
            sStream << word << std::endl;
        else
            break;

    inStream.close();

    T clipboard;

    while (sStream >> clipboard)
        variable.push_back(clipboard);

    return variable;

}

#endif
