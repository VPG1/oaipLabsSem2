#ifndef ADVANCE_AND_DISTANCE_H
#define ADVANCE_AND_DISTANCE_H

template<typename Iter>
void advance(Iter &it, int n){
    for(int i = 0; i < n; ++i, ++it);
}

template<typename Iter>
int distance(Iter it1, Iter it2){
    int res = 0;
    for(auto it = it1; it != it2; ++it, ++res);
    return res;
}


#endif // ADVANCE_AND_DISTANCE_H
