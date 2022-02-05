//crit DMG max roll:    7.77%   62.2main(rounded)
//crit rate max roll:   3.89%
//atk% max roll :       5.83%   46.6 main (rounded)
//em max roll:          23.31   187 main (rounded)
//er% max roll:         6.48
//flat atk max roll:    19.45
#include <iostream>
#include "permutation.cpp"
#include "combination.cpp"
#include "Character.h"
#include <vector>
#include <fstream>

/**
 * @brief given base character build,
 * ofstream linked to csv file
 * substat distribution
 * post all permutations to the given csv file
 * 
 */
void fillCSV(std::ofstream &file, const Character &BaseStats, const std::vector<std::vector<double>> &substats){
    std::vector<Character> build(substats.size(),BaseStats);
    std::map<std::vector<double>,int> freq;//check for character dupes
    for(int i=0;i<build.size();i++){
        
        if(freq[substats[i]]==0){
            //add artifact stats to base stats
            build[i].setCritDMG(0.01*substats[i][0]+build[i].getCritDmg());
            build[i].setTotalAttack(build[i].getBaseAtk()*(1+(substats[i][1]*0.01)+build[i].getAtkPercent()) +substats[i][4]);
            build[i].setEM(build[i].getEM()+substats[i][2]);
            build[i].setER(build[i].getER()+(20+substats[i][3])*0.01);//20 from emblem
            build[i].setDMGBonus(build[i].getDMGBonus()+.466);

            file<<90<<","<<build[i].getBaseAtk()<<","<<build[i].getTotalAtk()<<","
            <<build[i].getEM()<<","<<build[i].getER()*100<<","<<5<<","<<build[i].getCritDmg()*100
            <<","<<build[i].getDMGBonus()*100<<","<<build[i].getSkill()<<","<<build[i].getBurst()<<"\n";
            freq[substats[i]]++;
        }

    }
}

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
    std::vector<std::vector<double>> MainPieces=getPossibilities(generateDistributions(4,15,3),substats,4,311);
    MainPieces=removeDuplicateVectors(MainPieces);
    // //all possible substat distributions FOR FLOWER FEATHER GOBLET ONLY

    //circlet piece
    std::vector<double> circlet(5,0);//main stat Crit Damage
    circlet[0]=5.83;    //atk%
    circlet[1]=23.31;   //em
    circlet[2]=6.48;    //er
    circlet[3]=19.45;   //flat atk
    //idea:generate circlet, create x copies of TotalPossibilities (x is circlet distribution size)
    //then for each copy, add circlet's values to it.
    std::vector<std::vector<double>> circletRolls=getPossibilities(generateDistributions(4,5),circlet,0,62.2);
    circletRolls=MergePossibilities(MainPieces,circletRolls);
    // removeDuplicatePermutations(circletRolls);

    // create ATK% timepiece
    std::vector<double> ATKtimepiece(5,0);
    ATKtimepiece[0]=7.77;   //crit dmg
    // ATKtimepiece[1]=5.83;   NOT USING ATTACK%, BUT ADD BACK AFTER CALCULATING
    ATKtimepiece[1]=23.31;  //elemental mastery
    ATKtimepiece[2]=6.48;   //energy recharge
    ATKtimepiece[3]=19.45;  //flat atk

    std::vector<std::vector<double>> atkSandsRolls=getPossibilities(generateDistributions(4,5),ATKtimepiece,1,46.6);
    atkSandsRolls=MergePossibilities(atkSandsRolls,circletRolls);
    std::sort(atkSandsRolls.begin(),atkSandsRolls.end());

    // create EM timepiece
    std::vector<double> EMtimepiece(5,0);
    EMtimepiece[0]=7.77;   //crit dmg
    EMtimepiece[1]=5.83;   //atk%
    // EMtimepiece[2]=23.31;  NOT USING EM, add to "getPossibilities" function call instead
    EMtimepiece[2]=6.48;   //energy recharge
    EMtimepiece[3]=19.45;  //flat atk

    std::vector<std::vector<double>> EMSandsRolls=getPossibilities(generateDistributions(4,5),EMtimepiece,2,187);
    EMSandsRolls=MergePossibilities(EMSandsRolls,circletRolls);
    std::sort(EMSandsRolls.begin(),EMSandsRolls.end());
    
    //create ER timepiece
    std::vector<double> ERtimepiece(5,0);
    ERtimepiece[0]=7.77;   //crit dmg
    ERtimepiece[1]=5.83;   //atk%
    ERtimepiece[2]=23.31;  //elemental mastery
    // ERtimepiece[3]=6.48;   NOT USING ER, add to function call instead
    ERtimepiece[3]=19.45;  //flat atk
    std::vector<std::vector<double>> ERSandsRolls=getPossibilities(generateDistributions(4,5),ERtimepiece,3,51.8);
    ERSandsRolls=MergePossibilities(ERSandsRolls,circletRolls);
    std::sort(ERSandsRolls.begin(),ERSandsRolls.end());

    /*
    reference:
    0) crit dmg
    1) atk%
    2) em
    3) er
    4) flat ATK
    put into csv file while after we update the true stat value
    */ 
    std::ofstream atkStats,emStats,erStats;
    atkStats.open("atkSands_distribution.csv"),
    emStats.open("emSands_distribution.csv"),
    erStats.open("erSands_distribution.csv");
    Character BaseStats= Character(733);
    BaseStats.setSkill(366);
    BaseStats.setBurst(302.6);

    BaseStats.setAtkPercent(24+41.3);//from level up and weapon
    fillCSV(atkStats,BaseStats,atkSandsRolls);
    fillCSV(emStats,BaseStats,EMSandsRolls);
    fillCSV(erStats,BaseStats,ERSandsRolls);

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