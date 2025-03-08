#include <fs.h>
        FileSystem::FileSystem () {
            char* s = FS_ROOT_NAME;
            Array<char> rootName;
            for (size_t i = 0 ; i < strlen(s); i++) rootName.add(s[i]);
            root.getValue() = rootName;
        }
        Array<char>& FileSystem::getRootName() {
            return root.getValue();
        };
        bool FileSystem::directoryExists(Path& path) {
            FileTreeNode* pf = root.getNode(path);
            return (pf && !(pf -> isTerminal()));
        }
        int FileSystem::create(Array<char>& fn, Path& parentFolder, bool is_file) {
            FileTreeNode* pf = root.getNode(parentFolder);
            bool isfile = pf->isTerminal();
            if (!pf || isfile) return -1;
            char sp = ' ', path_delim=PATH_DELIM;
            if ((fn.length() == 0) || (fn.find(sp) != fn.length()) || (fn.find(path_delim) != fn.length())) return -1;
            size_t s1 = pf->childCount();
            size_t s2 = pf->addChild(fn,is_file);
            if (s1 == s2) return -1;
            if (is_file) {
                Array<char> empty;
                FileTreeNode* child = pf->nthchild(s2-1);
                files.set(child,empty);
            }
            return 0;
        }
        int FileSystem::remove(FileTreeNode* ptr) {
            if (!ptr) return -1;
            size_t ind = ptr - ptr->parent->children.begin();
            if (ptr->isTerminal()) {
                files.del(ptr);
            } else {
                for (size_t i = 0; i < ptr->childCount(); i++) {
                    remove(ptr->nthchild(i));
                }
            }
            ptr->parent->removeChild(ind);
            return 0;
        }
        int FileSystem::remove(Array<char>& fn, Path& parentFolder) {
            FileTreeNode* pf = root.getNode(parentFolder);
            if (!pf || pf -> isTerminal()) return -1;
            FileTreeNode* ptr = pf->nthchild(pf->findChild(fn));
            return remove(ptr);
        }
        int FileSystem::writeFile(Array<char>& fn, Path& parentFolder, Array<char>& data) {
            FileTreeNode* pf = root.getNode(parentFolder);
            if (!pf || pf -> isTerminal()) return -1;
            size_t ind = pf->findChild(fn);
            if (ind == pf->childCount()) return -1;
            FileTreeNode* file = pf->nthchild(ind);
            if (!(file->isTerminal())) return -1;
            files.set(file,data);
            return 0;
        }
        Array<char>* FileSystem::readFile(Array<char>& fn, Path& parentFolder) {
            FileTreeNode* pf = root.getNode(parentFolder);
            if (!pf || pf -> isTerminal()) return nullptr;
            size_t ind = pf->findChild(fn);
            if (ind == pf->childCount()) return nullptr;
            FileTreeNode* file = pf->nthchild(ind);
            if (!(file->isTerminal())) return nullptr;
            return files.get(file);
        }
        FileList* FileSystem::listFiles(Path& parentFolder) {
            FileTreeNode* pf = root.getNode(parentFolder);
            if (!pf || pf -> isTerminal()) return nullptr;
            FileList* fnl = new FileList();
            for (size_t i = 0; i < pf->childCount(); i++) {
                fnl->add(pf->nthchild(i)->getValue());
                char t = PATH_DELIM;
                if (!(pf -> nthchild(i)->isTerminal())) (*fnl)[i].add(t);
            }
            return fnl;
        }
        Array<Path>* FileSystem::search(Array<char>& fn,Path& parentFolder) {
            FileTreeNode* pf = root.getNode(parentFolder);
            if (!pf || pf -> isTerminal()) return nullptr;
            Array<Path>* ptr = pf->search(fn);
            return ptr;
        }
