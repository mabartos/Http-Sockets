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

/**
 * Persist and manage all boards
 */
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

    bool existsBoard(const string &name);

    static bool isValidBoardName(const string &name);

    string getNamesAllBoards();

    int getCount();
};


#endif //ISA_BOARDS_H
