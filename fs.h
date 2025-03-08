#pragma once

#include <array.h>
#include <tree.h>
#include <map.h>

#define PATH_DELIM '/'
#define FS_ROOT_NAME ""

typedef Array<Array<char>> Path;
typedef Array<Array<char>> FileList;
typedef TreeNode<Array<char>> FileTreeNode;
typedef Map<FileTreeNode*, Array<char>> FileMap;

class FileSystem {
    FileTreeNode root;
    FileMap files;
    public:
        FileSystem();
        Array<char>& getRootName();
        bool directoryExists(Path& path);
        int create(Array<char>& fn, Path& parentFolder, bool is_file) ;
        int remove(FileTreeNode* ptr);
        int remove(Array<char>& fn, Path& parentFolder) ;
        int writeFile(Array<char>& fn, Path& parentFolder, Array<char>& data) ;
        Array<char>* readFile(Array<char>& fn, Path& parentFolder) ;
        FileList* listFiles(Path& parentFolder) ;
        Array<Path>* search(Array<char>& fn,Path& parentFolder) ;
};