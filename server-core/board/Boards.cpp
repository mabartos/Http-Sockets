//
// Created by mabartos on 10/29/19.
//

#include "Boards.h"


bool Boards::createBoard(const string &name) {
    if (isValidBoardName(name)) {
        NoticeBoard notice(name);
        boards.push_back(notice);
        return true;
    } else {
        fprintf(stderr, "Name '%s' for Board is INVALID!!!\n", name.c_str());
        return false;
    }
}

bool Boards::deleteBoard(const string &name) {
    for (int i = 0; i < boards.size(); i++) {
        if (boards.at(0).getName() == name) {
            boards.erase(boards.begin() + i);
            return true;
        }
    }
    fprintf(stderr, "Cannot delete board. Board '%s' doesn't exist!\n", name.c_str());
    return false;
}

vector<NoticeBoard> Boards::getAllBoards() {
    return boards;
}


NoticeBoard &Boards::getBoard(const string &name) {
    for (auto &board:boards) {
        if (board.getName() == name)
            return board;
    }
}

bool Boards::isValidBoardName(const string &name) {
    for (char i : name) {
        if (!isalnum(i))
            return false;
    }
    return true;
}

int Boards::getCount() {
    return boards.size();
}

string Boards::getNamesAllBoards() {
    string result;
    for (auto &board:boards) {
        result.append(board.getName()).append("\r\n");
    }
    return result;
}

bool Boards::existsBoard(const string &name) {
    for (auto &board:boards) {
        if (board.getName() == name)
            return true;
    }
    return false;
}



