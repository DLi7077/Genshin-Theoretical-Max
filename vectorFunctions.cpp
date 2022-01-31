#include<iostream>
#include<vector>
#include<string>
/*prints out an integer list in the following format (new line)
list = 
[1,2,3,4,6,8]
*/
void displayVector(std::vector<int> list){
    std::cout<<"[";
    for(int i=0;i<list.size()-1;i++){//exclude last value for commas
        std::cout<<list[i]<<", ";
    }
    std::cout<<list[list.size()-1]<<"]\n";
}
void displayNestedVector(std::vector<std::vector<int>> list){
    for(int i=0;i<list.size();i++){//exclude last value for commas
        displayVector(list[i]);
    }
}
void displayVector(std::vector<double> list){
    std::cout<<"[";
    for(int i=0;i<list.size()-1;i++){//exclude last value for commas
        std::cout<<list[i]<<"\t|";
    }
    std::cout<<list[list.size()-1]<<"\t]\n";
}
void displayNestedVector(std::vector<std::vector<double>> list){
    for(int i=0;i<list.size();i++){//exclude last value for commas
        displayVector(list[i]);
    }
}
std::string vectortoString(std::vector<int>){
    
}