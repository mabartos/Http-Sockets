#include <utility>

#include <utility>

//
// Created by mabartos on 10/29/19.
//

#include "NoticeBoard.h"

NoticeBoard::NoticeBoard(string name) : name(move(name)) {
}

string NoticeBoard::getName() {
    return std::__cxx11::string();
}

string NoticeBoard::getAllContent() {
    string result;
    result.append("[ " + getName() + " ]\n");
    for (int i = 0; i < items.size(); i++) {
        result.append("%d. ", i + 1);
        result.append(items.at(i));
        result.append("\n");
    }
    return result;
}

void NoticeBoard::addItem(const string &content) {
    items.push_back(content);
}

bool NoticeBoard::changeItemContent(int id, const string &content) {
    if (id > 0 && id < items.size()) {
        items.at(id - 1) = content;
        return true;
    }
    return false;
}

bool NoticeBoard::removeItem(int id) {
    if (id > 0 && id < items.size()) {
        items.erase(items.begin() + id);
        return true;
    }
    return false;
}
