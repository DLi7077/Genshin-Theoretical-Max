//crit DMG max roll:    7.77%   62.2main(rounded)
//crit rate max roll:   3.89%
//atk% max roll :       5.83%   46.6 main (rounded)
//em max roll:          23.31   187 main (rounded)
//er% max roll:         6.48
//flat atk max roll:    19.45
#include <iostream>
#include "permutation.cpp"
#include "combination.cpp"
#include "vectorFunctions.cpp"
#include "Character.h"
#include <vector>
int main(){
    /*max 30 substat rolls.
    initialize base line, then roll into stats.
    0:flat atk
    1:atk%
    2:er%
    3:em
    4:Crit Rate
    5:Crit Dmg
    */
    
    //flower, feather, goblet piece will have these substats
    std::vector<double> substats(5,0);//main stat contains: 311 flat ATK, and 46.6 Dmg Bonus
    substats[0]=7.77;   //crit dmg
    substats[1]=5.83;   //atk%
    substats[2]=23.31;  //elemental mastery
    substats[3]=6.48;   //energy recharge
    substats[4]=19.45;  //flat atk

    //testing best artifact distribution with 4 emblem build
    

    //generated stats for flower, feather, and goblet
    std::vector<std::vector<double>> distributions=generateDistributions(4,5);
    //all possible substat distributions
    std::vector<std::vector<double>> TotalPossibilities=getPossibilities(distributions,substats,4,0);
    //TotalPossibilities now contains all possible distributions for a Flower, Feather, and Goblet
    // std::cout<<"-------------------------------------\n";
    // std::cout<<"All Possible Distributions:\n";//for flower feather goblet
    // std::cout<<"translated to artifact substats:\n";
    // std::cout<<"-------------------------------------\n"
    //             <<"CritDmg\t ATK%\t  EM\t  ER\t FlatATK\n";
    // displayNestedVector(TotalPossibilities);

    //circlet piece
    std::vector<double> circlet(5,0);//main stat Crit Damage
    circlet[0]=5.83;    //atk%
    circlet[1]=23.31;   //em
    circlet[2]=6.48;    //er
    circlet[3]=19.45;   //flat atk
    //idea:generate circlet, create x copies of TotalPossibilities (x is circlet distribution size)
    //then for each copy, add circlet's values to it.
    std::vector<std::vector<double>> circletRolls=generateDistributions(4,5);
    std::vector<std::vector<double>> circletDistribution=getPossibilities(circletRolls,circlet,0,62.6);
    std::cout<<"-------------------------------------\n";
    std::cout<<"All Possible Circlet Distributions:\n";//for flower feather goblet
    std::cout<<"translated to artifact substats:\n";
    std::cout<<"-------------------------------------\n"
                <<"CritDmg\t ATK%\t  EM\t  ER\t FlatATK\n";

    // displayNestedVector(TotalPossibilities);
    // std::cout<<"-------------------------------------\n";
    // displayNestedVector(circletDistribution);
    // std::cout<<"-------------------------------------\n";
    std::vector<std::vector<double>> merged=MergePossibilities(TotalPossibilities,circletDistribution);

    //create ATK% timepiece
    std::vector<double> ATKtimepiece(5,0);
    ATKtimepiece[0]=7.77;   //crit dmg
    // ATKtimepiece[1]=5.83;   NOT USING ATTACK%, BUT ADD BACK AFTER CALCULATING
    ATKtimepiece[1]=23.31;  //elemental mastery
    ATKtimepiece[2]=6.48;   //energy recharge
    ATKtimepiece[3]=19.45;  //flat atk
    std::vector<std::vector<double>> atkSandsRolls=generateDistributions(4,5);
    std::vector<std::vector<double>> atkSandsDistribution=getPossibilities(atkSandsRolls,ATKtimepiece,1,46.6);
    
    
    std::vector<double> EMtimepiece(5,0);
    EMtimepiece[0]=7.77;   //crit dmg
    EMtimepiece[1]=5.83;   //atk%
    // EMtimepiece[2]=23.31;  NOT USING EM, add to "getPossibilities" function call instead
    EMtimepiece[2]=6.48;   //energy recharge
    EMtimepiece[3]=19.45;  //flat atk
    std::vector<std::vector<double>> EMSandsRolls=generateDistributions(4,5);
    std::vector<std::vector<double>> EMSandsDistribution=getPossibilities(EMSandsRolls,EMtimepiece,2,186.6);
    
    
    std::vector<double> ERtimepiece(5,0);
    ERtimepiece[0]=7.77;   //crit dmg
    EMtimepiece[1]=5.83;   //atk%
    ERtimepiece[2]=23.31;  //elemental mastery
    // ERtimepiece[3]=6.48;   NOT USING ER, add to function call instead
    ERtimepiece[3]=19.45;  //flat atk
    std::vector<std::vector<double>> ERSandsRolls=generateDistributions(4,5);
    std::vector<std::vector<double>> ERSandsDistribution=getPossibilities(ERSandsRolls,ERtimepiece,3,51.8);

    atkSandsDistribution=MergePossibilities(atkSandsDistribution,merged);
    // EMSandsDistribution=MergePossibilities(EMSandsDistribution,merged);
    // ERSandsDistribution=MergePossibilities(ERSandsDistribution,merged);
    displayNestedVector(atkSandsDistribution);
    std::cout<<"-----------------------------------------------------------------------------\n";
    // displayNestedVector(EMSandsDistribution);
    // std::cout<<"-----------------------------------------------------------------------------\n";
    // displayNestedVector(ERSandsDistribution);
    // std::cout<<"-----------------------------------------------------------------------------\n";

    // Character optimal= Character("Chongyun");
    // double 
    // baseAtk= 733,
    // totalAtk=1789,
    // EM=166,
    // ER=120,
    // CritRate=70.3,
    // CritDmg=196.9,
    // DmgBonus=46.6,
    // SkillScaling=365.59,
    // BurstScaling=302.6;

    // optimal.setBaseAttack(baseAtk);
    // optimal.setTotalAttack(totalAtk);
    // optimal.setEM(EM);
    // optimal.setER(ER*.01);
    // optimal.setCritRate(CritRate*.01);
    // optimal.setCritDMG(CritDmg*.01);
    // optimal.setDMGBonus(DmgBonus*.01);
    // optimal.setSkill(SkillScaling*.01);
    // optimal.setBurst(BurstScaling*.01);
    // optimal.displayCharacterDetails();


    
    return 0;
}