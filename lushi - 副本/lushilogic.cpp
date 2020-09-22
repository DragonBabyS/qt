#include "lushilogic.h"
#include <QTime>
#include <time.h>

lushilogic::lushilogic()
{
    initgame();
}

void lushilogic::initgame()
{

    int index;
    create_cardpile();
    card_shuffle();
    current_side=0;
    card_giving();
    qsrand(unsigned(time(nullptr)));


}

void lushilogic::card_shuffle()
{
   std::vector<card>copy;
   int index;
   unsigned int index1;
   for (int i = static_cast<int>(cardpile_1.size()); i > 0; i--)
   {
       qsrand(unsigned(time(nullptr)));
       index = qrand()%i;
       index1=static_cast<unsigned int>(index);
       copy.push_back(cardpile_1[index1]);
       cardpile_1.erase(cardpile_1.begin()+index);
   }
   cardpile_1=copy;

   copy.clear();
   for (int i = static_cast<int>(cardpile_2.size()); i > 0; i--)
   {
       qsrand(unsigned(time(nullptr)));
       index = qrand()%i;
       index1=static_cast<unsigned int>(index);
       copy.push_back(cardpile_2[index1]);
       cardpile_2.erase(cardpile_2.begin()+index);
   }
   cardpile_2=copy;
}


void lushilogic::card_giving()
{
    int number_start_0,number_start_1;
    if(current_side==0)
    {
        number_start_0=4;
        number_start_1=4;
    }
    else
    {
        number_start_0=4;
        number_start_1=3;
    }

    for(int i=0;i<number_start_0;i++)
    {
        card_hand_1.push_back(cardpile_1[0]);
        cardpile_1.erase(cardpile_1.begin());
    }

    for(int i=0;i<number_start_1;i++)
    {
        card_hand_2.push_back(cardpile_2[0]);
        cardpile_2.erase(cardpile_2.begin());
    }
}

void lushilogic::create_cardpile()
{

    cardpile_1.resize(30);

    cardpile_1[0].name=("猎人印记");
    cardpile_1[0].which=0;
    cardpile_1[0].cost=2;
    cardpile_1[0].type=magic;
    cardpile_1[0].magical=hunter_tip;

    cardpile_1[1].name=("追踪术");
    cardpile_1[1].which=1;
    cardpile_1[1].cost=1;
    cardpile_1[1].type=magic;
    cardpile_1[1].magical=tracking;

    cardpile_1[2].name=("雄斑虎");
    cardpile_1[2].which=2;
    cardpile_1[2].cost=1;
    cardpile_1[2].type=person;
    cardpile_1[2].attack=1;
    cardpile_1[2].blood=1;
    cardpile_1[2].attack_base=1;
    cardpile_1[2].blood_base=1;
    cardpile_1[2].zhongzu=beast;
    cardpile_1[2].shout=call_female_tiger;

    cardpile_1[3].name=("雄斑虎");
    cardpile_1[3].which=2;
    cardpile_1[3].cost=1;
    cardpile_1[3].type=person;
    cardpile_1[3].attack=1;
    cardpile_1[3].blood=1;
    cardpile_1[2].attack_base=1;
    cardpile_1[2].blood_base=1;
    cardpile_1[3].zhongzu=beast;
    cardpile_1[3].shout=call_female_tiger;

    cardpile_1[4].name=("森林狼");
    cardpile_1[4].which=3;
    cardpile_1[4].cost=1;
    cardpile_1[4].type=person;
    cardpile_1[4].attack=1;
    cardpile_1[4].blood=1;
    cardpile_1[4].attack_base=1;
    cardpile_1[4].blood_base=1;
    cardpile_1[4].zhongzu=beast;
    cardpile_1[4].special=all_add_one_attack;

    cardpile_1[5].name=("森林狼");
    cardpile_1[5].which=3;
    cardpile_1[5].cost=1;
    cardpile_1[5].type=person;
    cardpile_1[5].attack=1;
    cardpile_1[5].blood=1;
    cardpile_1[5].attack_base=1;
    cardpile_1[5].blood_base=1;
    cardpile_1[5].zhongzu=beast;
    cardpile_1[5].special=all_add_one_attack;

    cardpile_1[6].name=("酸性沼泽软泥怪");
    cardpile_1[6].which=4;
    cardpile_1[6].cost=2;
    cardpile_1[6].type=person;
    cardpile_1[6].attack=3;
    cardpile_1[6].blood=2;
    cardpile_1[6].attack_base=3;
    cardpile_1[6].blood_base=2;
    cardpile_1[6].zhongzu=normal;
    cardpile_1[6].shout=eat_weapeon;

    cardpile_1[7].name=("恐狼先锋");
    cardpile_1[7].which=5;
    cardpile_1[7].cost=2;
    cardpile_1[7].type=person;
    cardpile_1[7].attack=2;
    cardpile_1[7].blood=2;
    cardpile_1[7].attack_base=2;
    cardpile_1[7].blood_base=2;
    cardpile_1[7].zhongzu=beast;
    cardpile_1[7].special=side_add_attack;

    cardpile_1[8].name=("食腐土狼");
    cardpile_1[8].which=6;
    cardpile_1[8].cost=2;
    cardpile_1[8].type=person;
    cardpile_1[8].attack=2;
    cardpile_1[8].blood=2;
    cardpile_1[8].attack_base=2;
    cardpile_1[8].blood_base=2;
    cardpile_1[8].zhongzu=beast;
    cardpile_1[8].special=teammember_died_benefit;

    cardpile_1[9].name=("食腐土狼");
    cardpile_1[9].which=6;
    cardpile_1[9].cost=2;
    cardpile_1[9].type=person;
    cardpile_1[9].attack=2;
    cardpile_1[9].blood=2;
    cardpile_1[9].attack_base=2;
    cardpile_1[9].blood_base=2;
    cardpile_1[9].zhongzu=beast;
    cardpile_1[9].special=teammember_died_benefit;

    cardpile_1[10].name=("慈祥的外婆");
    cardpile_1[10].which=7;
    cardpile_1[10].cost=2;
    cardpile_1[10].type=person;
    cardpile_1[10].attack=1;
    cardpile_1[10].blood=1;
    cardpile_1[10].attack_base=1;
    cardpile_1[10].blood_base=1;
    cardpile_1[10].zhongzu=beast;
    cardpile_1[10].dietalking=call_wolf;

    cardpile_1[11].name=("慈祥的外婆");
    cardpile_1[11].which=7;
    cardpile_1[11].cost=2;
    cardpile_1[11].type=person;
    cardpile_1[11].attack=1;
    cardpile_1[11].blood=1;
    cardpile_1[11].attack_base=1;
    cardpile_1[11].blood_base=1;
    cardpile_1[11].zhongzu=beast;
    cardpile_1[11].dietalking=call_wolf;

    cardpile_1[12].name=("雷鸣刺喉龙");
    cardpile_1[12].which=8;
    cardpile_1[12].cost=2;
    cardpile_1[12].type=person;
    cardpile_1[12].attack=3;
    cardpile_1[12].blood=2;
    cardpile_1[12].attack_base=3;
    cardpile_1[12].blood_base=2;
    cardpile_1[12].zhongzu=beast;
    cardpile_1[12].shout=evolution;

    cardpile_1[13].name=("雷鸣刺喉龙");
    cardpile_1[13].which=8;
    cardpile_1[13].cost=2;
    cardpile_1[13].type=person;
    cardpile_1[13].attack=3;
    cardpile_1[13].blood=2;
    cardpile_1[13].attack_base=3;
    cardpile_1[13].blood_base=2;
    cardpile_1[13].zhongzu=beast;
    cardpile_1[13].shout=evolution;

    cardpile_1[14].name=("葛拉卡爬行蟹");
    cardpile_1[14].which=9;
    cardpile_1[14].cost=2;
    cardpile_1[14].type=person;
    cardpile_1[14].attack=2;
    cardpile_1[14].blood=3;
    cardpile_1[14].attack_base=2;
    cardpile_1[14].blood_base=3;
    cardpile_1[14].zhongzu=beast;
    cardpile_1[14].shout=eat_pirate_benefit;

    cardpile_1[15].name=("葛拉卡爬行蟹");
    cardpile_1[15].which=9;
    cardpile_1[15].cost=2;
    cardpile_1[15].type=person;
    cardpile_1[15].attack=2;
    cardpile_1[15].blood=3;
    cardpile_1[15].attack_base=2;
    cardpile_1[15].blood_base=3;
    cardpile_1[15].zhongzu=beast;
    cardpile_1[15].shout=eat_pirate_benefit;

    cardpile_1[16].name=("鹰角弓");
    cardpile_1[16].which=10;
    cardpile_1[16].cost=3;
    cardpile_1[16].type=weapeon;
    cardpile_1[16].weapeon=yinjiaogong;

    cardpile_1[17].name=("关门放狗");
    cardpile_1[17].which=11;
    cardpile_1[17].cost=3;
    cardpile_1[17].type=magic;
    cardpile_1[17].magical=dog_dog;

    cardpile_1[18].name=("动物伙伴");
    cardpile_1[18].which=12;
    cardpile_1[18].cost=3;
    cardpile_1[18].type=magic;
    cardpile_1[18].magical=animal_friend;

    cardpile_1[19].name=("动物伙伴");
    cardpile_1[19].which=12;
    cardpile_1[19].cost=3;
    cardpile_1[19].type=magic;
    cardpile_1[19].magical=animal_friend;

    cardpile_1[20].name=("杀戮命令");
    cardpile_1[20].which=13;
    cardpile_1[20].cost=3;
    cardpile_1[20].type=magic;
    cardpile_1[20].magical=killing_order;

    cardpile_1[21].name=("杀戮命令");
    cardpile_1[21].which=13;
    cardpile_1[21].cost=3;
    cardpile_1[21].type=magic;
    cardpile_1[21].magical=killing_order;

    cardpile_1[22].name=("致命射击");
    cardpile_1[22].which=14;
    cardpile_1[22].cost=3;
    cardpile_1[22].type=magic;
    cardpile_1[22].magical=killed_shotting;

    cardpile_1[23].name=("凶恶的雏龙");
    cardpile_1[23].which=15;
    cardpile_1[23].cost=3;
    cardpile_1[23].type=person;
    cardpile_1[23].attack=3;
    cardpile_1[23].blood=3;
    cardpile_1[23].attack_base=3;
    cardpile_1[23].blood_base=3;
    cardpile_1[23].zhongzu=beast;
    //cardpile_1[23].cruel_dragon=true;  //所有进攻前判断是不是这张牌，这张牌效果特殊

    cardpile_1[24].name=("驯兽师");
    cardpile_1[24].which=16;
    cardpile_1[24].cost=4;
    cardpile_1[24].type=person;
    cardpile_1[24].attack=4;
    cardpile_1[24].blood=3;
    cardpile_1[24].attack_base=4;
    cardpile_1[24].blood_base=3;
    cardpile_1[24].zhongzu=normal;
    cardpile_1[24].shout=one_one_benefit;

    cardpile_1[25].name=("驯兽师");
    cardpile_1[25].which=16;
    cardpile_1[25].cost=4;
    cardpile_1[25].type=person;
    cardpile_1[25].attack=4;
    cardpile_1[25].blood=3;
    cardpile_1[25].attack_base=4;
    cardpile_1[25].blood_base=3;
    cardpile_1[25].zhongzu=normal;
    cardpile_1[25].shout=one_one_benefit;

    cardpile_1[26].name=("苔原犀牛");
    cardpile_1[26].which=18;
    cardpile_1[26].cost=5;
    cardpile_1[26].type=person;
    cardpile_1[26].attack=2;
    cardpile_1[26].blood=5;
    cardpile_1[26].attack_base=2;
    cardpile_1[26].blood_base=5;
    cardpile_1[26].zhongzu=beast;
    //cardpile_1[2].special=run_run;

    cardpile_1[27].name=("苔原犀牛");
    cardpile_1[27].which=18;
    cardpile_1[27].cost=5;
    cardpile_1[27].type=person;
    cardpile_1[27].attack=2;
    cardpile_1[27].blood=5;
    cardpile_1[27].attack_base=2;
    cardpile_1[27].blood_base=5;
    cardpile_1[27].zhongzu=beast;
    //cardpile_1[27].special=run_run;

    cardpile_1[28].name=("长鬃草原狮");
    cardpile_1[28].which=19;
    cardpile_1[28].cost=6;
    cardpile_1[28].type=person;
    cardpile_1[28].attack=6;
    cardpile_1[28].blood=5;
    cardpile_1[28].attack_base=6;
    cardpile_1[28].blood_base=5;
    cardpile_1[28].zhongzu=beast;
    cardpile_1[28].dietalking=call_wolf_lion;

    cardpile_1[29].name=("长鬃草原狮");
    cardpile_1[29].which=19;
    cardpile_1[29].cost=6;
    cardpile_1[29].type=person;
    cardpile_1[29].attack=6;
    cardpile_1[29].blood=5;
    cardpile_1[29].attack_base=6;
    cardpile_1[29].blood_base=5;
    cardpile_1[29].zhongzu=beast;
    cardpile_1[29].dietalking=call_wolf_lion;




    cardpile_2.resize(30);
    cardpile_2[0].name=("南海船工");
    cardpile_2[0].which=30;
    cardpile_2[0].cost=1;
    cardpile_2[0].type=person;
    cardpile_2[0].attack=2;
    cardpile_2[0].blood=1;
    cardpile_2[0].attack_base=2;
    cardpile_2[0].blood_base=1;
    cardpile_2[0].zhongzu=pirate;
    //cardpile_2[0].shout=call_female_tiger;

    cardpile_2[1].name=("南海船工");
    cardpile_2[1].which=30;
    cardpile_2[1].cost=1;
    cardpile_2[1].type=person;
    cardpile_2[1].attack=2;
    cardpile_2[1].blood=1;
    cardpile_2[1].attack_base=2;
    cardpile_2[1].blood_base=1;
    cardpile_2[1].zhongzu=pirate;

    cardpile_2[2].name=("升级！");
    cardpile_2[2].which=31;
    cardpile_2[2].cost=1;
    cardpile_2[2].type=magic;
    cardpile_2[2].magical=upgrade;

    cardpile_2[3].name=("升级！");
    cardpile_2[3].which=31;
    cardpile_2[3].cost=1;
    cardpile_2[3].type=magic;
    cardpile_2[3].magical=upgrade;

    cardpile_2[4].name=("恩佐斯的副官");
    cardpile_2[4].which=32;
    cardpile_2[4].cost=1;
    cardpile_2[4].type=person;
    cardpile_2[4].attack=1;
    cardpile_2[4].blood=1;
    cardpile_2[4].attack_base=1;
    cardpile_2[4].blood_base=1;
    cardpile_2[4].zhongzu=pirate;
    cardpile_2[4].shout=equip_gouzi;

    cardpile_2[5].name=("恩佐斯的副官");
    cardpile_2[5].which=32;
    cardpile_2[5].cost=1;
    cardpile_2[5].type=person;
    cardpile_2[5].attack=1;
    cardpile_2[5].blood=1;
    cardpile_2[5].attack_base=1;
    cardpile_2[5].blood_base=1;
    cardpile_2[5].zhongzu=pirate;
    cardpile_2[5].shout=equip_gouzi;

    cardpile_2[6].name=("海盗帕奇斯");
    cardpile_2[6].which=33;
    cardpile_2[6].cost=1;
    cardpile_2[6].type=person;
    cardpile_2[6].attack=1;
    cardpile_2[6].blood=1;
    cardpile_2[6].attack_base=1;
    cardpile_2[6].blood_base=1;
    cardpile_2[6].zhongzu=pirate;
    cardpile_2[6].legend=true;
    cardpile_2[6].attack_status=un_attacked;

    cardpile_2[7].name=("血帆袭击者");
    cardpile_2[7].which=34;
    cardpile_2[7].cost=2;
    cardpile_2[7].type=person;
    cardpile_2[7].attack=2;
    cardpile_2[7].blood=3;
    cardpile_2[7].attack_base=2;
    cardpile_2[7].blood_base=3;
    cardpile_2[7].zhongzu=pirate;
    cardpile_2[7].shout=benefit_from_weapeon;

    cardpile_2[8].name=("血帆袭击者");
    cardpile_2[8].which=34;
    cardpile_2[8].cost=2;
    cardpile_2[8].type=person;
    cardpile_2[8].attack=2;
    cardpile_2[8].blood=3;
    cardpile_2[8].attack_base=2;
    cardpile_2[8].blood_base=3;
    cardpile_2[8].zhongzu=pirate;
    cardpile_2[8].shout=benefit_from_weapeon;

    cardpile_2[9].name=("南海船长");
    cardpile_2[9].which=35;
    cardpile_2[9].cost=3;
    cardpile_2[9].type=person;
    cardpile_2[9].attack=3;
    cardpile_2[9].blood=3;
    cardpile_2[9].attack_base=3;
    cardpile_2[9].blood_base=3;
    cardpile_2[9].zhongzu=pirate;
    cardpile_2[9].special=all_one_one_add_pirate;

    cardpile_2[10].name=("南海船长");
    cardpile_2[10].which=35;
    cardpile_2[10].cost=3;
    cardpile_2[10].type=person;
    cardpile_2[10].attack=3;
    cardpile_2[10].blood=3;
    cardpile_2[10].attack_base=3;
    cardpile_2[10].blood_base=3;
    cardpile_2[10].zhongzu=pirate;
    cardpile_2[10].special=all_one_one_add_pirate;

    cardpile_2[11].name=("炽炎战斧");
    cardpile_2[11].which=36;
    cardpile_2[11].cost=3;
    cardpile_2[11].type=weapeon;
    cardpile_2[11].weapeon=fire_fu;

    cardpile_2[12].name=("炽炎战斧");
    cardpile_2[12].which=36;
    cardpile_2[12].cost=3;
    cardpile_2[12].type=weapeon;
    cardpile_2[12].weapeon=fire_fu;

    cardpile_2[13].name=("暴乱狂战士");
    cardpile_2[13].which=37;
    cardpile_2[13].cost=3;
    cardpile_2[13].type=person;
    cardpile_2[13].attack=2;
    cardpile_2[13].blood=4;
    cardpile_2[13].attack_base=2;
    cardpile_2[13].blood_base=4;
    cardpile_2[13].zhongzu=normal;
    cardpile_2[13].special=kuangzhanshi;

    cardpile_2[14].name=("暴乱狂战士");
    cardpile_2[14].which=37;
    cardpile_2[14].cost=3;
    cardpile_2[14].type=person;
    cardpile_2[14].attack=2;
    cardpile_2[14].blood=4;
    cardpile_2[14].attack_base=2;
    cardpile_2[14].blood_base=4;
    cardpile_2[14].zhongzu=normal;
    cardpile_2[14].special=kuangzhanshi;

    cardpile_2[15].name=("血帆教徒");
    cardpile_2[15].which=38;
    cardpile_2[15].cost=3;
    cardpile_2[15].type=person;
    cardpile_2[15].attack=3;
    cardpile_2[15].blood=4;
    cardpile_2[15].attack_base=3;
    cardpile_2[15].blood_base=4;
    cardpile_2[15].zhongzu=pirate;
    cardpile_2[15].shout=weapeon_benefit_one_one;

    cardpile_2[16].name=("血帆教徒");
    cardpile_2[16].which=38;
    cardpile_2[16].cost=3;
    cardpile_2[16].type=person;
    cardpile_2[16].attack=3;
    cardpile_2[16].blood=4;
    cardpile_2[16].attack_base=3;
    cardpile_2[16].blood_base=4;
    cardpile_2[16].zhongzu=pirate;
    cardpile_2[16].shout=weapeon_benefit_one_one;

    cardpile_2[17].name=("恐怖海盗");
    cardpile_2[17].which=39;
    cardpile_2[17].cost=4;          //没想好怎么处理
    cardpile_2[17].type=person;
    cardpile_2[17].attack=3;
    cardpile_2[17].blood=3;
    cardpile_2[17].attack_base=3;
    cardpile_2[17].blood_base=3;
    cardpile_2[17].zhongzu=pirate;
    cardpile_2[17].shield=true;
    //cardpile_2[17].shout=weapeon_benefit;

    cardpile_2[18].name=("恐怖海盗");
    cardpile_2[18].which=39;
    cardpile_2[18].cost=4;          //没想好怎么处理
    cardpile_2[18].type=person;
    cardpile_2[18].attack=3;
    cardpile_2[18].blood=3;
    cardpile_2[18].attack_base=3;
    cardpile_2[18].blood_base=3;
    cardpile_2[18].zhongzu=pirate;
    cardpile_2[18].shield=true;
    //cardpile_2[17].shout=weapeon_benefit;

    cardpile_2[19].name=("破法者");
    cardpile_2[19].which=40;
    cardpile_2[19].cost=4;
    cardpile_2[19].type=person;
    cardpile_2[19].attack=4;
    cardpile_2[19].blood=3;
    cardpile_2[19].attack_base=4;
    cardpile_2[19].blood_base=3;
    cardpile_2[19].zhongzu=normal;
    cardpile_2[19].shout=clear;

    cardpile_2[20].name=("破法者");
    cardpile_2[20].which=40;
    cardpile_2[20].cost=4;
    cardpile_2[20].type=person;
    cardpile_2[20].attack=4;
    cardpile_2[20].blood=3;
    cardpile_2[20].attack_base=4;
    cardpile_2[20].blood_base=3;
    cardpile_2[20].zhongzu=normal;
    cardpile_2[20].shout=clear;

    cardpile_2[21].name=("致死打击");
    cardpile_2[21].which=41;
    cardpile_2[21].cost=4;
    cardpile_2[21].type=magic;
    cardpile_2[21].magical=pirate_shotting;

    cardpile_2[22].name=("致死打击");
    cardpile_2[22].which=41;
    cardpile_2[22].cost=4;
    cardpile_2[22].type=magic;
    cardpile_2[22].magical=pirate_shotting;

    cardpile_2[23].name=("库卡隆精英卫士");
    cardpile_2[23].which=42;
    cardpile_2[23].cost=4;
    cardpile_2[23].type=person;
    cardpile_2[23].attack=4;
    cardpile_2[23].blood=3;
    cardpile_2[23].attack_base=4;
    cardpile_2[23].blood_base=3;
    cardpile_2[23].zhongzu=normal;

    cardpile_2[24].name=("库卡隆精英卫士");
    cardpile_2[24].which=42;
    cardpile_2[24].cost=4;
    cardpile_2[24].type=person;
    cardpile_2[24].attack=4;
    cardpile_2[24].blood=3;
    cardpile_2[24].attack_base=4;
    cardpile_2[24].blood_base=3;
    cardpile_2[24].zhongzu=normal;

    cardpile_2[25].name=("娜迦海盗");
    cardpile_2[25].which=43;
    cardpile_2[25].cost=4;
    cardpile_2[25].type=person;
    cardpile_2[25].attack=5;
    cardpile_2[25].blood=4;
    cardpile_2[25].attack_base=5;
    cardpile_2[25].blood_base=4;
    cardpile_2[25].zhongzu=pirate;
    cardpile_2[25].shout=weapeon_benefit_one;

    cardpile_2[26].name=("火车王里诺艾");
    cardpile_2[26].which=44;
    cardpile_2[26].cost=5;
    cardpile_2[26].type=person;
    cardpile_2[26].attack=6;
    cardpile_2[26].blood=2;
    cardpile_2[26].attack_base=6;
    cardpile_2[26].blood_base=2;
    cardpile_2[26].zhongzu=normal;
    cardpile_2[26].shout=call_little_dragon;
    cardpile_2[26].legend=true;

    cardpile_2[27].name=("绿皮船长");
    cardpile_2[27].which=45;
    cardpile_2[27].cost=5;
    cardpile_2[27].type=person;
    cardpile_2[27].attack=5;
    cardpile_2[27].blood=4;
    cardpile_2[27].attack_base=5;
    cardpile_2[27].blood_base=4;
    cardpile_2[27].zhongzu=pirate;
    cardpile_2[27].shout=captain_1;
    cardpile_2[27].legend=true;

    cardpile_2[28].name=("奥金斧");
    cardpile_2[28].which=46;
    cardpile_2[28].cost=5;
    cardpile_2[28].type=weapeon;
    cardpile_2[28].weapeon=aojin_fu;

    cardpile_2[29].name=("奥金斧");
    cardpile_2[29].which=46;
    cardpile_2[29].cost=5;
    cardpile_2[29].type=weapeon;
    cardpile_2[29].weapeon=aojin_fu;

    //衍生牌
    card_extended.resize(10);

    card_extended[0].name=("雌斑虎");
    card_extended[0].which=50;
    card_extended[0].type=person;
    card_extended[0].attack=1;
    card_extended[0].blood=1;
    card_extended[0].attack_base=1;
    card_extended[0].blood_base=1;
    card_extended[0].zhongzu=beast;

    card_extended[1].name=("大灰狼");
    card_extended[1].which=51;
    card_extended[1].type=person;
    card_extended[1].attack=3;
    card_extended[1].blood=2;
    card_extended[1].attack_base=3;
    card_extended[1].blood_base=2;
    card_extended[1].zhongzu=beast;

    card_extended[2].name=("猎犬");
    card_extended[2].which=52;
    card_extended[2].type=person;
    card_extended[2].attack=1;
    card_extended[2].blood=1;
    card_extended[2].attack_base=1;
    card_extended[2].blood_base=1;
    card_extended[2].zhongzu=beast;
    card_extended[2].attack_status=un_attacked;

    card_extended[3].name=("霍佛");
    card_extended[3].which=53;
    card_extended[3].type=person;
    card_extended[3].attack=4;
    card_extended[3].blood=2;
    card_extended[3].attack_base=4;
    card_extended[3].blood_base=2;
    card_extended[3].zhongzu=beast;

    card_extended[4].name=("雷欧克");
    card_extended[4].which=54;
    card_extended[4].type=person;
    card_extended[4].attack=2;
    card_extended[4].blood=4;
    card_extended[4].attack_base=2;
    card_extended[4].blood_base=4;
    card_extended[4].zhongzu=beast;

    card_extended[5].name=("米莎");
    card_extended[5].which=55;
    card_extended[5].type=person;
    card_extended[5].attack=4;
    card_extended[5].blood=4;
    card_extended[5].attack_base=4;
    card_extended[5].blood_base=4;
    card_extended[5].zhongzu=beast;

    card_extended[6].name=("重斧");
    card_extended[6].which=56;
    card_extended[6].type=weapeon;
    card_extended[6].weapeon=zhongfu;

    card_extended[7].name=("锈蚀铁钩");
    card_extended[7].which=57;
    card_extended[7].type=weapeon;
    card_extended[7].weapeon=gouzi;

    card_extended[8].name=("雏龙");
    card_extended[8].which=58;
    card_extended[8].type=person;
    card_extended[8].attack=1;
    card_extended[8].blood=1;
    card_extended[8].attack_base=1;
    card_extended[8].blood_base=1;
    //card_extended[8].zhongzu=beast;

    card_extended[9].name=("土狼");
    card_extended[9].which=59;
    card_extended[9].type=person;
    card_extended[9].attack=2;
    card_extended[9].blood=2;
    card_extended[9].attack_base=2;
    card_extended[9].blood_base=2;
    card_extended[9].zhongzu=beast;


}

 void lushilogic::deal_shout(card a,int b)
 {
     if(a.shout==1&&card_battle_visiable_1.size()<7)
         card_battle_visiable_1.push_back(card_extended[0]);

     else if(a.shout==2)
     {
         warrior.weapeon=null_weapeon;
         warrior.attack_max=0;
         warrior.useable_times_current=0;
         warrior.attack_base=0;
         warrior.useable_times_max=0;
         warrior.useable_times_base=0;

     }

     else if(a.shout==3)
     {
         //进化不会弄
     }

     else if(a.shout==4)
     {
         bool pirate_exist=false;
         for(int i=0;i<card_battle_visiable_2.size();i++)
         {
             if(card_battle_visiable_2[i].zhongzu==pirate)
             {
                 pirate_exist=true;
                 break;
             }
         }
         if(pirate_exist)
         {
             emit_locked=3;
             emit_locked_help=b;

         }              //后续处理，要想想，比较麻烦
     }

     else if(a.shout==5)
     {
         bool beast_exist=false;
         for(int i=0;i<card_battle_visiable_1.size();i++)
         {
             if(card_battle_visiable_1[i].zhongzu==beast)
             {
                 beast_exist=true;
                 break;
             }
         }
         if(beast_exist)
             emit_locked=5;               //后续处理，要想想，比较麻烦
     }

     else if(a.shout==6)
     {
         if(warrior.weapeon!=0)
             card_battle_visiable_2[b].attack=card_battle_visiable_2[b].attack+warrior.attack_max;
     }

     else if(a.shout==7)
     {
         bool pirate_exist=false;
         for(int i=0;i<card_battle_visiable_2.size();i++)
         {
             if(card_battle_visiable_2[i].zhongzu==pirate)
             {
                 pirate_exist=true;
                 break;
             }
         }
         if(pirate_exist&&warrior.weapeon!=0)
         {
             warrior.attack_max++;
             warrior.useable_times_max++;
             warrior.useable_times_current++;         //关系有点复杂，蓝和红的设定，还要改
         }
     }

     else if(a.shout==8)
     {
         if(card_battle_visiable_1.size()!=0)
             emit_locked=6;
     }

     else if(a.shout==9)
     {
         if(warrior.weapeon!=0)
             warrior.attack_max++;
     }

     else if(a.shout==10)
     {
         if(card_battle_visiable_1.size()<=6)
             card_battle_visiable_1.push_back(card_extended[8]);
         if(card_battle_visiable_1.size()<=6)
             card_battle_visiable_1.push_back(card_extended[8]);
     }

     else if(a.shout==11)
     {
         if(warrior.weapeon!=0)
         {
             warrior.attack_max++;
             warrior.useable_times_max++;
             warrior.useable_times_current++;
         }
     }

     else if(a.shout==12)
     {
         warrior.weapeon=card_extended[7].weapeon;
         warrior.attack_max=1;
         warrior.attack_base=1;
         warrior.useable_times_max=3;
         warrior.useable_times_current=3;
         warrior.useable_times_base=3;
     }




}

void lushilogic::deal_attack(int side, int a, int b)
{
    kuangzhnashi_add(2);
    if(side==0)
    {
        card_battle_visiable_1[a].blood=card_battle_visiable_1[a].blood-card_battle_visiable_2[b].attack;
        card_battle_visiable_2[b].blood=card_battle_visiable_2[b].blood-card_battle_visiable_1[a].attack;
        card_battle_visiable_1[a].attack_status=attacked;
        if(card_battle_visiable_1[a].blood<=0)
        {
            //if()   特殊类型牌
            forest_wolf_die(card_battle_visiable_1[a]);
            deal_dietalking(card_battle_visiable_1[a]);
            card_battle_visiable_1.erase(card_battle_visiable_1.begin()+a);
            if(card_battle_visiable_1[a].type==beast)
                tulang_add();
        }
        if(card_battle_visiable_2[b].blood<=0)
        {
            //if()   特殊类型牌
            card_battle_visiable_2.erase(card_battle_visiable_2.begin()+b);
        }
    }
    if(side==1)
    {
        card_battle_visiable_2[a].blood=card_battle_visiable_2[a].blood-card_battle_visiable_1[b].attack;
        card_battle_visiable_1[b].blood=card_battle_visiable_1[b].blood-card_battle_visiable_2[a].attack;
        card_battle_visiable_2[a].attack_status=attacked;
        if(card_battle_visiable_2[a].blood<1)
        {
            //if()   特殊类型牌
            card_battle_visiable_2.erase(card_battle_visiable_2.begin()+a);
        }
        if(card_battle_visiable_1[b].blood<1)
        {
            //if()   特殊类型牌
            forest_wolf_die(card_battle_visiable_1[b]);
            deal_dietalking(card_battle_visiable_1[b]);
            card_battle_visiable_1.erase(card_battle_visiable_1.begin()+b);
            if(card_battle_visiable_1[b].zhongzu==beast)
                tulang_add();
        }
    }

}
void lushilogic::person_clear(card &a)
{
    if(a.blood>a.blood_base)
        a.blood=a.blood_base;
    if(a.attack>a.attack_base)
        a.attack=a.attack_base;
    a.dietalking=null_dietalking;
    a.shield=false;


}


bool lushilogic::rhinoceros_exist()
{
    for(int i=0;i<card_battle_visiable_1.size();i++)
    {
        if(card_battle_visiable_1[i].which==18)
            return true;
    }
    return false;
}

void lushilogic::attack_status_change()
{
    if(rhinoceros_exist())
    {
        for(int i=0;i<card_battle_visiable_1.size();i++)
            if(card_battle_visiable_1[i].attack_status==newly_released&&card_battle_visiable_1[i].zhongzu==beast)
                card_battle_visiable_1[i].attack_status=un_attacked;
    }
}

void lushilogic::chuangong_weapeon()
{
    for(int i=0;i<card_battle_visiable_2.size();i++)
    {
        if(card_battle_visiable_2[i].attack_status==newly_released&&card_battle_visiable_2[i].which==30)
            card_battle_visiable_2[i].attack_status=un_attacked;
    }
}

void lushilogic::warrior_runrun(int current_location)
{
    if(card_battle_visiable_2[current_location].which==42)
        card_battle_visiable_2[current_location].attack_status=un_attacked;
    if(card_battle_visiable_2[current_location].which==44)
        card_battle_visiable_2[current_location].attack_status=un_attacked;
    if(card_battle_visiable_2[current_location].which==30&&warrior.weapeon!=0)
        card_battle_visiable_2[current_location].attack_status=un_attacked;
}


bool lushilogic::beast_exist()
{
    for(int i=0;i<card_battle_visiable_1.size();i++)
    {
        if(card_battle_visiable_1[i].zhongzu==beast)
            return true;
    }
    return false;
}

bool lushilogic::pirate_exist()
{
    for(int i=0;i<card_battle_visiable_2.size();i++)
    {
        if(card_battle_visiable_2[i].zhongzu==pirate)
            return true;
    }
    return false;
}


void lushilogic::call_paqisi(card a)
{
    int exist=-1;
    if(a.zhongzu==pirate&&card_battle_visiable_2.size()<7)
    {
        for(int i=0;i<cardpile_2.size();i++)
        {
            if(cardpile_2[i].which==33)
            {
                exist=i;
                break;
            }
        }
        if(exist!=-1)
        {
            card_battle_visiable_2.push_back(cardpile_2[exist]);
            cardpile_2.erase(cardpile_2.begin()+exist);

        }
    }
}

void lushilogic::deal_dietalking(card a)
{
    if(a.which==7&&card_battle_visiable_1.size()<7)
        card_battle_visiable_1.push_back(card_extended[1]);
    if(a.which==19)
    {
        if(card_battle_visiable_1.size()<7)
            card_battle_visiable_1.push_back(card_extended[9]);
        if(card_battle_visiable_1.size()<7)
            card_battle_visiable_1.push_back(card_extended[9]);
    }
}


int lushilogic::forest_wolf()
{
    int count=0;
    for(int i=0;i<card_battle_visiable_1.size();i++)
    {
        if(card_battle_visiable_1[i].which==3)
            count++;
    }
    return count;
}

int lushilogic::captain()
{
    int count=0;
    for(int i=0;i<card_battle_visiable_2.size();i++)
    {
        if(card_battle_visiable_2[i].which==35)
            count++;
    }
    return count;
}

void lushilogic::forest_wolf_die(card a)
{
    if(a.which==3)
        for(int i=0;i<card_battle_visiable_1.size();i++)
            if(card_battle_visiable_1[i].zhongzu==beast)
                card_battle_visiable_1[i].attack--;
}

void lushilogic::captain_die(card a)
{
    if(a.which==35)
        for(int i=0;i<card_battle_visiable_2.size();i++)
        {
            if(card_battle_visiable_2[i].zhongzu==pirate)
            {
                card_battle_visiable_2[i].attack--;
                card_battle_visiable_2[i].blood--;
                if(card_battle_visiable_2[i].blood==0)
                    card_battle_visiable_2[i].blood=1;
            }
        }
}

void lushilogic::kuangzhnashi_add(int caseof)
{
    for(int i=0;i<card_battle_visiable_2.size();i++)
        if(card_battle_visiable_2[i].which==37)
            card_battle_visiable_2[i].attack+=caseof;
}

void lushilogic::tulang_add()
{
    for(int i=0;i<card_battle_visiable_1.size();i++)
        if(card_battle_visiable_1[i].which==6)
        {
            card_battle_visiable_1[i].attack+=2;
            card_battle_visiable_1[i].blood++;
        }
}
