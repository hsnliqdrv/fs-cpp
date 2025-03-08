#include <iostream>
#include <fstream>
#include <fs.h>

void prompt(Array<Array<char>>& cmd) {
    std::cout << "\nFileExp> ";
    Array<char> s;
    std::cin >> s;
    char sp = ' ';
    s.split(sp, cmd);
}

Path root_path;

void process(FileSystem& fs,Path& current, Array<Array<char>>& cmd) {
    char path_delim = PATH_DELIM;
    if (cmd[0].equals("move",4)) {
        Path path, path_;
        if (cmd[1].equals("..",2) && current.length() > 1) current.remove(current.length()-1);
        else {
            cmd[1].split(path_delim, path_);
            if (path_[0].length() != 0) {
                path.concat(current);
                path.concat(path_);
            } else {
                path = path_;
            }
            if (fs.directoryExists(path)) {
                current = path;
            } else {
                std::cout << "Directory does not exist";
            }
        }
    } else if (cmd[0].equals("path",4)) {
        for (size_t i = 0; i < current.length(); i++) {
            std::cout << current[i] << "/";
        }
    } else if (cmd[0].equals("show",4)) {
        FileList* fl = fs.listFiles(current);
        std::cout << *fl;
        delete fl;
    } else if (cmd[0].equals("remove",6)) {
        if (fs.remove(cmd[1],current) < 0) {
            std::cout << "Could not remove file";
        }
    } else if (cmd[0].equals("file",4)) {
        if (fs.create(cmd[1],current,true) < 0) {
            std::cout << "Could not create file";
        }
    } else if (cmd[0].equals("dir",3)) {
        if (fs.create(cmd[1],current,false) < 0) {
            std::cout << "Could not create directory";
        }
    } else if (cmd[0].equals("write",5)) {
        size_t c = 0;
        Array<char> data;
        char sp = ' ';
        for (size_t i = 2; i < cmd.length(); i++) {
            data.concat(cmd[i]);
            if (i<cmd.length()-1) data.add(sp);
        }
        if (fs.writeFile(cmd[1], current, data) < 0) {
            std::cout << "Could not write file";
        }
    } else if (cmd[0].equals("read",4)) {
        Array<char>* data = fs.readFile(cmd[1],current);
        if (data) {
            std::cout << *data;
        } else {
            std::cout << "Could not read file";
        }
    } else if (cmd[0].equals("search",6)) {
        Array<Path>* arr = fs.search(cmd[1],root_path);
        if (arr) {
            for (size_t i = 0; i < arr->length(); i++) {
                for (size_t j = 0; j < (*arr)[i].length(); j++) {
                    std::cout << (*arr)[i][j];
                    if (j < (*arr)[i].length() - 1) std::cout << "/";
                }
                if (i < arr->length() - 1) std::cout << std::endl;
            }
            delete arr;
        }
    } else if (cmd[0].equals("exit",4)) {
        exit(0);
    } else if (cmd[0].equals("help",4)) {
        std::cout << "Commands:" << std::endl;
        std::cout << "move <path> | move .. | move - 1. move into the directory 2. move into the parent directory 3. move into the root dir" << std::endl;
        std::cout << "path - shows path of current directory" << std::endl;
        std::cout << "show - lists files in the current directory" << std::endl;
        std::cout << "remove <file_name> - removes the file in current directory" << std::endl;
        std::cout << "file <file_name> - creates the file in current directory" << std::endl;
        std::cout << "dir <dir_name> - creates the directory in current directory" << std::endl;
        std::cout << "write <file_name> <data> - writes the given data into the file" << std::endl;
        std::cout << "read <file_name> - reads the data inside the file" << std::endl;
        std::cout << "search <file_or_dir_name> - searches the file or dir in the filesystem" << std::endl;
        std::cout << "exit - exits program" << std::endl;
        std::cout << "help - show command descriptions" << std::endl;
    }
};

int main() {
    // set path to root
    FileSystem fs;
    root_path.add(fs.getRootName());
    Path current = root_path;
    // command loop
    while (1) {
        Array<Array<char>> cmd;
        prompt(cmd);
        process(fs,current,cmd);
    }
}