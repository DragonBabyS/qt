#ifndef LUSHILOGIC_H
#define LUSHILOGIC_H
#include <vector>
#include <QString>

enum TYPE{
    null_type,
    person,
    magic,
    weapeon
};

enum ZHONGZU{
    null_zhongzu,
    normal,
    beast,
    pirate
};

enum SHOUT{
    null_shout,
    call_female_tiger,
    eat_weapeon,
    evolution,
    eat_pirate_benefit,
    one_one_benefit,
    benefit_from_weapeon,
    weapeon_benefit_one_one,
    clear,
    weapeon_benefit_one,
    call_little_dragon,
    captain_1,
    equip_gouzi
};

enum DIETALKING{
    null_dietalking,
    call_wolf,
    call_wolf_lion
};

enum SPECIAL{               //不是固定属性，先这样写，后续更改
    null_special,
    all_add_one_attack,
    side_add_attack,
    teammember_died_benefit,
    all_one_one_add_pirate,
    kuangzhanshi
};

enum ATTACK_STATUS{
    null_attack_status,              //无
    attacked,          //该随从攻击过
    un_attacked,       //该随从未攻击过
    un_double_attacked,//风怒
    newly_released     //本回合刚出的
};

enum MAGIC{
    null_magic,

    hunter_tip,
    tracking,
    dog_dog,
    animal_friend,
    killing_order,
    killed_shotting,

    upgrade,
    pirate_shotting
};

enum WEAPEON{
    null_weapeon,
    yinjiaogong,
    zhongfu,
    gouzi,
    fire_fu,
    aojin_fu
};

struct card{
    bool clicked=false;
    bool legend=false;
    QString name;
    //以下属性，如果是0，代表无
    //公有属性
    int which=0;   //用于图片输出，确定具体是哪张牌
    int cost=0;    //牌的花费
    TYPE type=null_type;    //确定牌的类型
    //随从属性
    int attack=0;  //攻击力
    int blood=0;   //血量
    int attack_base=0;
    int blood_base=0;
    ZHONGZU zhongzu=null_zhongzu;   //有些牌需要确定种族
    SHOUT shout=null_shout;   //战吼属性确定
    DIETALKING dietalking=null_dietalking;       //亡语属性确定
    bool shield=false;    //嘲讽
    SPECIAL special=null_special;   //比较特殊的效果，在场就恒定存在，不是点击触发型，借助别的触发，例如食腐土狼，冲锋犀牛,恐狼前锋
    ATTACK_STATUS attack_status=newly_released;    //随从当前的攻击状态
    //法术属性，武器属性
    MAGIC magical=null_magic;      //确定是哪张法术牌
    WEAPEON weapeon=null_weapeon;   //确定是哪张武器牌
};

struct hero{
    int blood=30;
    WEAPEON weapeon=null_weapeon;
    int attack_base=0;
    int attack_max=0;
    int useable_times_base=0;
    int useable_times_max=0;
    int useable_times_current=0;
    ATTACK_STATUS attack_status=null_attack_status;
};






class lushilogic
{
public:
    lushilogic();
    std::vector<card> cardpile_1;   //第一家的牌库
    std::vector<card> cardpile_2;
    std::vector<card> card_hand_1;  //第一家的手牌
    std::vector<card> card_hand_2;
    std::vector<card> card_battle_visiable_1;    //用于显示的两家在场上的牌
    std::vector<card> card_battle_visiable_2;
    std::vector<card> card_extended;
    hero hunter,warrior;

    int current_side;
    int number;
    int round=2;
    int energy_useable_1=1;
    int energy_useable_2=2;
    int energy_1=1;
    int energy_2=0;
    int emit_locked=0;
    int emit_locked_help=-1;
    int magic_killing_force=0;
    int attacker=-1,defender=-1;
    bool hero_attack=false;
    bool rhinoceros_exist();
    bool beast_exist();
    bool pirate_exist();

    void create_cardpile();
    void card_shuffle();
    void card_giving();
    void initgame();
    void deal_shout(card a,int b);
    void deal_attack(int side,int a,int b);
    void deal_dietalking(card a);
    void person_clear(card &a);
    void call_paqisi(card a);
    void warrior_runrun(int current_location);
    void chuangong_weapeon();
    void attack_status_change();
    void forest_wolf_die(card a);
    void captain_die(card a);
    void kuangzhnashi_add(int caseof);
    void tulang_add();
    int forest_wolf();
    int captain();


};

#endif // LUSHILOGIC_H
