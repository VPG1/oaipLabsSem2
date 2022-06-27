#ifndef LISTANDFILE_H
#define LISTANDFILE_H
#include "list.h"
#include <string>
#include <fstream>
#include "statement.h"
#include "advance_and_distance.h"


class ListAndFile{
    List<Statement> m_list;
    std::string m_path = "";
public:
    ListAndFile() = default;

    void setFilePath(const std::string &path)
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

            m_list.push_back(Statement(objectString));
        }

        fin.close();
    }
//    static void rowNumbersInFile(const std::string &path);

    static bool fileIsCorrect(const std::string &path){
        std::ifstream fin(path);
        assert(fin.is_open());
        while(!fin.eof()){
            std::string str;
            std::getline(fin, str);
            if(!Statement::statementStringIsCorrect(str)){
                fin.close();
                return false;
            }
        }

        fin.close();
        return true;
    }

    const List<Statement> &getList() const
    {
        return m_list;
    }
    List<Statement> &getList()
    {
        return m_list;
    }

    void clear(){
        m_path = "";
        m_list.clear();
    }

    static bool fileIsEmpty(std::string path){
        std::ifstream fin(path);
        assert(fin.is_open());
        std::string tmp;
        fin >> tmp;
        if(tmp.empty()){
            return true;
        }
        return false;
    }

    void setList(List<Statement> &&newList){
        m_list = std::move(newList);

        std::ofstream fout(m_path);
        assert(fout.is_open());
        for(auto it = m_list.begin(); it != m_list.end(); ++it){
            fout << *it << '\n';
        }
        fout.close();
    }

    void updateFile(){
        std::ofstream fout(m_path);
        assert(fout.is_open());
        for(auto it = m_list.begin(); it != m_list.end(); ++it){
            fout << (*it) << '\n';
        }
        fout.close();
    }

    void pushBack(Statement &&statement){
        m_list.push_back(std::move(statement));
        std::ofstream fout(m_path, std::ios::app);
        assert(fout.is_open());
        fout << *(--m_list.end()) << '\n';
        fout.close();
    }

    void erase(int pos){
        m_list.erase(pos);
        updateFile();
    }

    List<Statement> search(const std::string &str)
    {
        List<Statement> list;

        for(auto it = m_list.begin(); it != m_list.end(); ++it){
            if((*it).address() == str){
                list.push_back(*it);
            }
        }

        return list;
    }

    void qsort(){
//        qsort(0, m_list.size() - 1);
        qsort(m_list.begin(), --m_list.end());
        updateFile();
    }
private:

//    void qsort(typename List<Statement>::iterator firstIt,
//               typename List<Statement>::iterator lastIt){
//        double pivot = firstIt->grade();
//        auto f = firstIt;
//        auto l = lastIt;
//        do{
//            while((f != l) && (f->grade() < pivot)){
//                ++f;
//            }
//            while((l != f) && (pivot < l->grade())){
//                --l;
//            }

//            if(f != l){
//                std::swap(*f, *l);
//                --l;
////                ++f;
////                if(f != l)
////                    --l;
////                else
////                    break;
//            }

//        }while(f != l);

//        if(l != firstIt)
//            qsort(firstIt, l);
//        if(lastIt != f)
//            qsort(++f, lastIt);
//    }

    List<Statement>::iterator partition(
            List<Statement>::iterator l,
            List<Statement>::iterator h)
    {
        Statement pivot = *h;

        auto tempL = l;
        auto i = --tempL;

        for(auto j = l; j != h; ++j){
            if(j->grade() >= pivot.grade()){
                (i == List<Statement>::iterator(nullptr)) ? i = l : ++i;
                std::swap(*i, *j);
            }
        }
        (i == List<Statement>::iterator(nullptr)) ? i = l : ++i;
        std::swap(*i, *h);
        return i;
    }


    void qsort(List<Statement>::iterator l,
                                List<Statement>::iterator h)
    {
        if(h != List<Statement>::iterator(nullptr) && h != m_list.end() && l != h && l != ++h){
            --h;
            auto p = partition(l, h);
            auto tempP = p;
            qsort(l, --tempP);
            qsort(++p, h);
        }
    }




};









#endif // LISTANDFILE_H
