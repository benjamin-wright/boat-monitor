#include <Arduino.h>
#include <LittleFS.h>
#include "load-file.h"

void FileLoader::setup() {

}

String FileLoader::readFile(const char* file) {
    File f = LittleFS.open(file, "r");
    if (!f) {
        Serial.println("Failed to open file for reading");
        return "";
    }

    size_t length = f.size();
    uint8_t* buffer = 0;

    buffer = (uint8_t*)malloc(length);
    size_t read = f.read(buffer, length);
    f.close();

    String content = String(buffer, length);
    free(buffer);

    return content;
}