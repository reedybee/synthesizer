#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include <util/util.h>
#include <util/song.h>

Song::Song(const char* songFilePath) {
    std::fstream file = std::fstream(songFilePath);

    if (!file.is_open()) {
        std::cout << "Song file at " << songFilePath << " failed to load.\n";
        return;
    } else {
        std::cout << "Song file at " << songFilePath << " has been loaded.\n";
    }

    std::string line;
    std::string fileContents;

    std::ostringstream stringstream;
    stringstream << file.rdbuf();
    const std::string& s = stringstream.str();
    std::vector<char> fileChar(s.begin(), s.end());

    for (int i = 0; i < fileChar.size(); i++) {
        std::cout << fileChar[i];
    }
    
    
}