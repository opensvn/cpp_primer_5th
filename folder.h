#ifndef FOLDER_H
#define FOLDER_H

#include <set>
#include "message.h"

class Message;
class Folder
{
public:
    void addMsg(Message *msg);
    void remMsg(Message *msg);
private:
    std::set<Message *> messages;
};

#endif
