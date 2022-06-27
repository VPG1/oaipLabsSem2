#ifndef INFORMATIONLIST_H
#define INFORMATIONLIST_H
#include "information.h"
#include "listonarray.h"
#include <fstream>
#include <string>

class InformationList
{
    ListOnArray<Information> m_list;
    std::string m_path = "";
public:
    InformationList() = default;

    void setFilePath(const std::string &path);

    static bool fileIsEmpty(const std::string &path){
        std::ifstream fin(path);
        assert(fin.is_open());
        std::string tmp;
        fin >> tmp;
        if(tmp.empty()){
            return true;
        }
        return false;
    }

    static bool fileIsCorrect(const std::string &path);
    const ListOnArray<Information> &list() const;

    void setList(ListOnArray<Information> &&newList);

    void pushBack(Information &&statement);

    void erase(int pos);

    void updateFile();

    ListOnArray<Information> searchByLastName(const std::string &str);
    ListOnArray<Information> searchByIncome(unsigned long long value);
    ListOnArray<Information> searchByIncome();

    void qsort();

private:
    ListOnArray<Information>::iterator partition(ListOnArray<Information>::iterator f,
                                                 ListOnArray<Information>::iterator l);
    void qsort(typename ListOnArray<Information>::iterator firstIt,
               typename ListOnArray<Information>::iterator lastIt);


};
#endif // INFORMATIONLIST_H
