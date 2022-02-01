#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <vector>
#include <string>
class Character{
    private:
        std::string name="untitled Character";
        double BaseAtk, TotalAtk, DEF=0, ElementalMastery=0,
        CritRate=0.05,CritDMG=0.50,EnergyRecharge=1.00,DMGBonus=0;
        double AtkPercent=0;
        double FlatAttack=0;

        double SkillScaling=1;
        double BurstScaling=1;

        double SkillBonus=0;
        double BurstBonus=0;

        double meltBonus=0;
        
        bool Emblem=false;
        double EmblemBonus=0.25*EnergyRecharge;

    public:
        Character(std::string n){//default
            name=n;
            BaseAtk=0;
            TotalAtk=0;
        }
        Character(std::string n, double TotalB){//name and base
            name=n;
            BaseAtk=TotalB;
            TotalAtk=TotalB;
        }
        Character(double TotalB){//specifies base attack
            BaseAtk=TotalB;
            TotalAtk=TotalB;
        }
        //complete constructor
        Character(std::string n, double TotalB, double TotalA, double D, double EM, double CR, double CD, double ER, double DB){
            name=n;
            BaseAtk=TotalB;
            TotalAtk=TotalA;
            DEF=D;
            ElementalMastery=EM;
            CritRate=CR;
            CritDMG=CD;
            EnergyRecharge=ER;
            DMGBonus=DB;
        }
        void updateAtk(){
            TotalAtk=BaseAtk*(1+AtkPercent) +FlatAttack;
        }
        void setBaseAttack(double Base){
            BaseAtk=Base;
        }
        void setTotalAttack(double total){
            TotalAtk=total;
        }
        void setAtkPercent(double p){//p is taken as x percent
            AtkPercent=p*0.01;
            updateAtk();
        }
        void setEM(double e){
            ElementalMastery=e;
        }
        void setER(double e){
            EnergyRecharge=e;
        }
        void setCritRate(double c){
            CritRate=c;
        }
        void setCritDMG(double c){
            CritDMG=c;
        }
        void setDMGBonus(double b){
            DMGBonus=b;
        }
        void setSkill(double s){
            SkillScaling=s;
        }
        void setBurst(double b){
            BurstScaling=b;
        }
        void setEmblem(bool x){
            Emblem=x;
            BurstBonus+=EmblemBonus*0.01*int(Emblem);
            //will add 0 if emblem if false
            
        }


        double getBaseAtk() const{
            return BaseAtk;
        }
        double getTotalAtk() const{
            return TotalAtk;
        }
        double getEM() const {
            return ElementalMastery;
        }
        double getER() const{
            return EnergyRecharge;
        }
        double getCritRate() const{
            return CritDMG;
        }
        double getCritDmg() const{
            return CritDMG;
        }
        double getDMGBonus() const{
            return DMGBonus;
        }
        double getAtkPercent() const{
            return AtkPercent;
        }
        double getSkill() const{
            return SkillScaling;
        }
        double getBurst() const{
            return BurstScaling;
        }
        double getSkillBonus() const{
            return SkillBonus;
        }
        double getBurstBonus() const{
            return BurstBonus;
        }



        void displayCharacterDetails(){
            using namespace std;
            cout<<name<<"\n"
            <<"Base Attack:\t\t"<<BaseAtk
            <<"\nTotal Attack:\t\t"<<TotalAtk
            <<"\nElemental Mastery:\t"<<ElementalMastery
            <<"\nCrit Rate:\t\t\t"<<CritRate*100
            <<"%\nCrit Damage:\t\t"<<CritDMG*100
            <<"%\nEnergy Recharge:\t"<<EnergyRecharge*100
            <<"%\nDamage Bonus\t\t"<<DMGBonus*100
            <<"%\n\nSkill Scaling%\t\t"<<SkillScaling*100
            <<"%\nBurst scaling%\t\t"<<BurstScaling*100<<"%\n";
        }

};

#endif
/* to do: set output format:
BaseAtk, TotalAtk, EM, ER, Crit Rate, Crit Dmg, DmgBonus, SkillDmg, BurstDmg
*/