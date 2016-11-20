#ifndef sort_hpp
#define sort_hpp
#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

struct A{
    std::ifstream *ptr;
    std::string data;
};

inline bool operator< (const A &s1, const A &s2)
{
    return  s1.data > s2.data;
}

class File_sort{
public:
    File_sort(std::string str);
    File_sort(File_sort const &) = delete;
    auto operator=(File_sort const &)-> File_sort& = delete;
    File_sort(File_sort &&) = delete;
    auto operator=(File_sort &&)-> File_sort& = delete;

    void sort();
private:

    auto remove_create_file()-> void;
    auto generate()-> void;
    std::vector<std::string> arr_name_file;
    std::string name_file;
};

File_sort::File_sort(std::string str)
    :   name_file(str) {
    generate();
}

auto File_sort::generate()-> void {
    std::ifstream file(name_file);

    std::string tmp2 = "0";
    std::string tmp1;
    std::vector<std::string> tmp;

    while (getline(file, tmp1)) {
        tmp.push_back(tmp1);
        if (tmp.size() == 3) {
            arr_name_file.push_back(tmp2);
            std::ofstream a(tmp2);
            tmp2 += arr_name_file.size();
            std::sort(tmp.begin(), tmp.end());
            for (int j = 0; j < tmp.size(); ++j) {
                a << tmp[j] << std::endl;
            }
            a.close();
            tmp.clear();
        }
    }
    file.close();
}

void File_sort::sort() {
    std::priority_queue<A> other;
    for (int i = 0; i < arr_name_file.size(); ++i) {
        A tmp = {new std::ifstream(arr_name_file[i])};
        getline(*tmp.ptr, tmp.data);
        other.push(tmp);
    }
    std::ifstream *ptr = other.top().ptr;
    std::ofstream tmp(name_file);
    while(!other.empty()){
        if (other.size() == arr_name_file.size()) {
            tmp << other.top().data << std::endl;
            if (other.top().ptr->eof()) {
                other.pop();
                ptr = other.top().ptr;
            } else {
                ptr = other.top().ptr;
                other.pop();
            }
        }
        if (ptr->eof()){
            tmp << other.top().data << std::endl;
            other.pop();
            ptr = other.top().ptr;
            ptr->close();
        } else {
            A tmp1 = {ptr};
            getline(*tmp1.ptr, tmp1.data);
            other.push(tmp1);
        }
    }
    remove_create_file();
}

auto File_sort::remove_create_file()-> void {
    for (int i = 0; i < arr_name_file.size(); ++i) {
        auto a = arr_name_file[i].c_str();
        std::remove(a);
    }
}
#endif
