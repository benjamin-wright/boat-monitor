#ifndef LOAD_FILE_H
#define LOAD_FILE_H

class FileLoader {
  public:
    static void setup();
    static String readFile(const char* file);
};

#endif