//
// Created by mabartos on 10/29/19.
//

#ifndef ISA_NOTICEBOARD_H
#define ISA_NOTICEBOARD_H

#include "string"
#include "vector"

using namespace std;

class NoticeBoard {
private:
    string name;
    vector<string> items;

public:
    explicit NoticeBoard(string name);

    ~NoticeBoard() = default;

    string getName();

    string getAllContent();

    void addItem(const string &content);

    bool changeItemContent(int id, const string &content);

    bool removeItem(int id);

};


#endif //ISA_NOTICEBOARD_H
