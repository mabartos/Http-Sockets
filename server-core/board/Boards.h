//
// Created by mabartos on 10/29/19.
//

#ifndef ISA_BOARDS_H
#define ISA_BOARDS_H

#include "string"
#include "vector"
#include "NoticeBoard.h"
#include <bits/unique_ptr.h>


using namespace std;

class Boards {
private:
    vector<NoticeBoard> boards;
public:
    Boards() = default;

    ~Boards() = default;

    vector<NoticeBoard> getAllBoards();

    bool createBoard(const string &name);

    bool deleteBoard(const string &name);

    NoticeBoard &getBoard(const string &name);

    static bool isValidBoardName(const string &name);

    int getCount();
};


#endif //ISA_BOARDS_H
