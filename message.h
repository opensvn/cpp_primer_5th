#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <set>
#include "folder.h"

class Message
{
    friend class Folder;
    friend void swap(Message&, Message&);
public:
    explicit Message(const std::string &str = ""):
        contents(str) {}
    Message(const Message &);
    Message(Message &&);
    Message &operator=(const Message &);
    Message &operator=(Message &&);
    ~Message();

    void save(Folder &);
    void remove(Folder &);
    void addFolder(Folder*);
    void remFolder(Folder*)
private:
    std::string contents;
    std::set<Folder *> folders;
    void add_to_Folders(const Message &);
    void remove_from_Folders();
    void move_Folders(Message *m);
};

#endif
