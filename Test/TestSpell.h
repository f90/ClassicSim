#ifndef TESTSPELL_H
#define TESTSPELL_H

#include <QString>

class Engine;
class Equipment;
class CombatRoll;
class Faction;
class Target;
class Race;
class Character;

class TestSpell {
public:
    TestSpell(QString spell_under_test);
    ~TestSpell();

    void set_up_general();
    void tear_down_general();

    void given_no_previous_damage_dealt();
    void given_a_guaranteed_white_hit();
    void given_a_guaranteed_white_glancing_blow();
    void given_a_guaranteed_white_crit();
    void given_a_guaranteed_melee_ability_crit();
    void given_a_guaranteed_melee_ability_hit();
    void given_300_weapon_skill_mh();
    void given_305_weapon_skill_mh();
    void given_310_weapon_skill_mh();
    void given_315_weapon_skill_mh();
    void given_300_weapon_skill_oh();
    void given_305_weapon_skill_oh();
    void given_310_weapon_skill_oh();
    void given_315_weapon_skill_oh();
    void given_a_mainhand_weapon_with_100_min_max_dmg();
    void given_a_mainhand_weapon_with_3_speed();
    void given_a_mainhand_weapon_with_2_speed();
    void given_no_mainhand();
    void given_no_offhand();
    void given_an_offhand_weapon_with_100_min_max_dmg();
    void given_an_offhand_weapon_with_3_speed();
    void given_an_offhand_weapon_with_2_speed();
    void given_1000_melee_ap();
    void given_engine_priority_at(const float priority);

    void then_damage_dealt_is(const int damage);
    void then_next_event_is(const QString &name);
    void then_next_event_is(const QString &name, const QString &priority);

protected:
    Engine* engine;
    Equipment* equipment;
    CombatRoll* combat;
    Faction* faction;
    Target* target;
    Race* race;
    Character* pchar;
    QString spell_under_test;

    void set_melee_special_table_for_hit(const int wpn_skill);
    void set_melee_special_table_for_crit(const int wpn_skill);

    void set_melee_auto_table_for_hit(const int wpn_skill);
    void set_melee_auto_table_for_glancing(const int wpn_skill);
    void set_melee_auto_table_for_crit(const int wpn_skill);
};

#endif // TESTSPELL_H
