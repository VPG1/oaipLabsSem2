#include "informationlist.h"

const ListOnArray<Information> &InformationList::list() const
{
    return m_list;
}

void InformationList::setList(ListOnArray<Information> &&newList)
{
    m_list = std::move(newList);

    std::ofstream fout(m_path);
    assert(fout.is_open());
    for(auto it = m_list.begin(); it != m_list.end(); ++it){
        fout << *it << '\n';
    }
    fout.close();
}

void InformationList::pushBack(Information &&statement)
{
    m_list.push_back(std::move(statement));
    std::ofstream fout(m_path, std::ios::app);
    assert(fout.is_open());
    fout << *(--m_list.end()) << '\n';
    fout.close();
}

void InformationList::erase(int pos)
{
    m_list.erase(pos);
    updateFile();
}

void InformationList::updateFile(){
    std::ofstream fout(m_path);
    assert(fout.is_open());
    for(auto it = m_list.begin(); it != m_list.end(); ++it){
        fout << (*it) << '\n';
    }
    fout.close();
}


void InformationList::qsort(){
    qsort(m_list.begin(), --m_list.end());
    updateFile();
}


ListOnArray<Information>::iterator InformationList::partition(
        ListOnArray<Information>::iterator l,
        ListOnArray<Information>::iterator h)
{
    Information pivot = *h;
    auto i = --l;
    ++l;
    for(auto j = l; j != h; ++j){
        if(j->grade() >= pivot.grade()){
            ++i;
            std::swap(*i, *j);
        }
    }
    ++i;
    std::swap(*i, *h);
    return i;
}


void InformationList::qsort(ListOnArray<Information>::iterator l,
                            ListOnArray<Information>::iterator h)
{
    if(h != m_list.end() && l != h && l != ++h){
        --h;
        auto p = partition(l, h);
        qsort(l, --p);
        ++p;
        qsort(++p, h);
    }
}


ListOnArray<Information> InformationList::searchByLastName(const std::string &str)
{
    ListOnArray<Information> list;

    for(auto it = m_list.begin(); it != m_list.end(); ++it){
        if(it->lastName() == str){
            list.push_back(*it);
        }
    }

    return list;
}

ListOnArray<Information> InformationList::searchByIncome(unsigned long long value)
{
    ListOnArray<Information> list;

    for(auto it = m_list.begin(); it != m_list.end(); ++it){
        if(it->income() >= value){
            list.push_back(*it);
        }
    }

    return list;
}

ListOnArray<Information> InformationList::searchByIncome()
{
    ListOnArray<Information> list;

    unsigned long long minIncome = m_list.begin()->income();
    for(auto it = m_list.begin(); it != m_list.end(); ++it){
        if(it->income() < minIncome){
            minIncome = it->income();
        }
    }

    return searchByIncome(2 * minIncome);
}



void InformationList::setFilePath(const std::string &path)
{
    m_path = path;
    m_list.clear();

    if(fileIsEmpty(path)){
        return;
    }

    std::ifstream fin(path);
    assert(fin.is_open());
    while(!fin.eof()){
        std::string objectString;
        std::getline(fin, objectString);

        if(objectString == "")
            return;

        m_list.push_back(Information(objectString));
    }

    fin.close();
}

bool InformationList::fileIsCorrect(const std::string &path)
{
    std::ifstream fin(path);
    assert(fin.is_open());
    while(!fin.eof()){
        std::string str;
        std::getline(fin, str);
        if(!Information::informationStringIsCorrect(str)){
            fin.close();
            return false;
        }
    }
    fin.close();
    return true;
}

//bool fileIsEmpty(const std::string &path){
//    std::ifstream fin(path);
//    assert(fin.is_open());
//    std::string tmp;
//    fin >> tmp;
//    if(tmp.empty()){
//        return true;
//    }
//    return false;
//}
