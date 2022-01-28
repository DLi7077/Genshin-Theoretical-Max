#include <vector>
/**
 * @brief given an integer n, return a list of all combinations of size k
 * ex: n=3, k=2;
 * returns [ [1,2], [1,3] [2,3]]
 * note that [1,2] and [2,1] are the same
 * 
 * @return std::vector<std::vector<int>> 
 */
/*
    n=3, k=2-> [1,2,3]-> 1[2,3] k=1;-> 1,2 [3] k=0; ->return 1,2
                                    <backtrack>
                                k=1;-> 1,3 [2] k=0; ->return 1,3
                        <backtrack>
                removed 1 from previous call
                [2,3] k=2-> 2[3] k=1;-> 2,3 k=0; ->return 2,3
                removed 2 from previous call

*/
//global variable
std::vector<std::vector<int>> result;
void helper(int start, std::vector<int> addTo,int n, int k){
    if(addTo.size()==k){//no more to add
        result.push_back(addTo);//add to our global list
    } 
    for(int i=start;i<=n;i++){
        //add to list until it has k elements
        addTo.push_back(i);
        //recursive call
        helper(i+1,addTo,n,k);
        //back track, pop_back to allow for other combinations
        addTo.pop_back();
    }
}
std::vector<std::vector<int>> combinations(int n, int k){
    std::vector<int> hold;
    helper(1,hold,n,k);
    return result;
}