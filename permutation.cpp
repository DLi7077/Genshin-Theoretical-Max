#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <stdexcept>
/**
 * @brief given a list of integers, return a list of lists that contains all possible permutations of that list
 * 
 * @param list
 * @return list of permutations
 */
/*loop thru list, branch off each value
    after removing the chosen value, branch off again for each values
    at end case where there is nothing left in list to branch, backtrack and add the removed value to the final list
    ex: [1,2,3,4]->[2,3,4]->[3,4]->[4]->3,4 ->2,3,4 ->1,2,3,4
                    take 2->[4,3]->[3]->4,3 ->2,4,3 ->1,2,4,3
                    take 4->[2,4]->[2]->4,2 ->3,4,2 ->1,3,4,2
                    .......         ^base case if size=1, return that partList as a list
*/
void removeDuplicatePermutations(std::vector<std::vector<double>> &list){
    //sort each element
    for(int i=0;i<list.size();i++){
        std::sort(list[i].begin(),list[i].end());
    }

    //sort the list
    std::sort(list.begin(),list.end());

    //all vectors now sorted, remove dups
    for(int i=1;i<list.size();i++){
        if(list[i]==list[i-1]){
            list.erase(list.begin()+i);
            i--;
        }
    }
}

std::vector<std::vector<double>>permuations(std::vector<double> list){
    if(list.size()<=1) return {list};

    std::vector<std::vector<double>> results;

    for(int i=0;i<list.size();i++){
        std::vector<double>part(list.begin(),list.end());
        part.erase(part.begin()+i);

        //will perform permutation on the shortened list
        std::vector<std::vector<double>> backTrack=permuations(part);

        //work thru the backTracked list
        for(int x=0;x<backTrack.size();x++){
            //insert removed value back to front
            backTrack[x].insert(backTrack[x].begin(),list[i]);
            //add value to final result
            results.push_back(backTrack[x]);
        }
    }
    return results;
}

/**
 * @brief Generates unique permutations of a given vector
 * same as before, just with hashmap
 * @param list 
 */
std::vector<std::vector<double>>UniquePermutations(std::vector<double> list){
    if(list.size()<2) return {list};

    std::vector<std::vector<double>> results;
    std::map<int,int> freq;
    for(int i=0;i<list.size();i++){
        if(freq[list[i]]>0){//if exists in map, do nothing
        }
        else{//add to map;
            freq[list[i]]++;
            std::vector<double>part(list.begin(),list.end());
            part.erase(part.begin()+i);

            //will perform permutation on the shortened list
            std::vector<std::vector<double>> backTrack=UniquePermutations(part);

            //work thru the backTracked list
            for(int x=0;x<backTrack.size();x++){
                //insert removed value back to front
                backTrack[x].insert(backTrack[x].begin(),list[i]);
                //add value to final result
                results.push_back(backTrack[x]);
            }
        }
        
    }
    return results;
}

/**
 * @brief given a number of possible substats (s), and an amount of rolls (r)
 * generate a list of possible sub stat distributions
 * ex:
 * 4 subs 5 rolls
 * 5 0 0 0
 * 4 1 0 0
 * 3 2 0 0
 * 3 1 1 0
 * 2 2 1 0
 * 2 1 1 1
 * there are 6 different distributions, We will generate unique permutations of this using another function
 * */

//idea: generate a distribution given a number of subs and rolls, then generate permutations


std::vector<std::vector<double>> distributions;
/**
 * @brief recursive function that generates the possible distributions of x rolls going into a given list
 * @param rollsToAdd
 * @param rollsLeft
 * @param index
 * @param list 
 * @return std::vector<double> 
 * 
 * TIME COMPLEXITY: O(substat * rolls)~= O(n^2)
 * MEMORY: O(n^2)
 */
void singleDistribution(int rollsToAdd, int rollsLeft, int idx, std::vector<double> list){
    std::vector<double> artifact(list.begin(),list.end());
    
    if(rollsToAdd<1||idx>=list.size()||rollsLeft<1){//end cases
    
        if(rollsLeft==0){
            distributions.push_back(artifact);
        }
        return;
    }
    artifact[idx]+=rollsToAdd;//rolled x amount into substat idx
    rollsLeft-=rollsToAdd;//reduce possible amount rolled into next substat
    //consider all possible rolls with remaining
    for(int i=rollsLeft;i>=0;i--){
        singleDistribution(i,rollsLeft,idx+1,artifact);
    }
}

std::vector<std::vector<double>> generateDistributions(int substat, int rolls){
    distributions.clear();
    std::vector<double> base(substat,1);
    for(int i=2;i<=rolls;i++){
        singleDistribution(i,rolls,0,base);
    }
    removeDuplicatePermutations(distributions);
    return distributions;
}

/**
 * @brief Get the Possibilities of a given "valued" vector
 * 
 * @param distribution unqiue distributions
 * @param substats substat values
 * @param Editindex tells us the index to place the EditValue for every sub vector
 * @return std::vector<std::vector<double>> totalPossibilities
 */
std::vector<std::vector<double>> getPossibilities(std::vector<std::vector<double>> distribution,std::vector<double> substats,int EditIndex, double EditValue){
    std::vector<std::vector<double>> TotalPossibilities;
    for(int i=0;i<distributions.size();i++){//for every base distribution
        std::vector<std::vector<double>> list=UniquePermutations(distributions[i]);//create permutations
        for(int x=0;x<list.size();x++){
            for(int s=0;s<list[x].size();s++){
                list[x][s]*=substats[s];
            }
            if(list.size()==0){
                throw "List is empty!\n";
            }
            if(EditIndex>=0&&EditIndex<=list[0].size()){//if edit needed
                list[x].insert(list[x].begin()+EditIndex,EditValue);
            }
            TotalPossibilities.push_back(list[x]);//add to totalList
        }
    }
    return TotalPossibilities;
}

/**
 * @brief merges part1 permutations with part 2, ignores part1's index ignore
 * ex: 
 * if ignore was 0, then part 2 will add to part 1 from index 0 to index 4 by default but since it ignores index 0,
 * the range will be 1-4 instead
 * ignore=3: 0,1,2,4
 * ignore=5: 0,1,2,3 (no change)
 * THIS FUNCTION ASSUMES PROPER FORMATTING
 * @param part1 size 5
 * @param ignore size 5
 * @return std::vector<std::vector<double>> 
 */
std::vector<std::vector<double>> MergePossibilities(std::vector<std::vector<double>> part1, std::vector<std::vector<double>>part2){
    std::vector<std::vector<double>> merge;
    for(int t=0;t<part2.size();t++){
        std::vector<std::vector<double>> hold(part1.begin(),part1.end());//reset point
        for(int i=0;i<part1.size();i++){//for every list in part1 aka (part1[i])
            for(int p=0;p<part1[i].size();p++){
                hold[i][p]+=part2[i][p];
            }
            merge.push_back(hold[i]);//return that distribution
        }
    }
    return merge;
}






/*SAME FUNCTIONS FOR INTEGER VECTORS
----------------------------------------------------------------------
----------------------------------------------------------------------*/
std::vector<std::vector<int>>permuations(std::vector<int> list){
    if(list.size()<=1) return {list};

    std::vector<std::vector<int>> results;

    for(int i=0;i<list.size();i++){
        std::vector<int>part(list.begin(),list.end());
        part.erase(part.begin()+i);

        //will perform permutation on the shortened list
        std::vector<std::vector<int>> backTrack=permuations(part);

        //work thru the backTracked list
        for(int x=0;x<backTrack.size();x++){
            //insert removed value back to front
            backTrack[x].insert(backTrack[x].begin(),list[i]);
            //add value to final result
            results.push_back(backTrack[x]);
        }
    }
    return results;
}
std::vector<std::vector<int>>UniquePermutations(std::vector<int> list){
    if(list.size()<2) return {list};

    std::vector<std::vector<int>> results;
    std::map<int,int> freq;
    for(int i=0;i<list.size();i++){
        if(freq[list[i]]>0){//if exists in map, do nothing
        }
        else{//add to map;
            freq[list[i]]++;
            std::vector<int>part(list.begin(),list.end());
            part.erase(part.begin()+i);

            //will perform permutation on the shortened list
            std::vector<std::vector<int>> backTrack=UniquePermutations(part);

            //work thru the backTracked list
            for(int x=0;x<backTrack.size();x++){
                //insert removed value back to front
                backTrack[x].insert(backTrack[x].begin(),list[i]);
                //add value to final result
                results.push_back(backTrack[x]);
            }
        }
        
    }
    return results;
}
