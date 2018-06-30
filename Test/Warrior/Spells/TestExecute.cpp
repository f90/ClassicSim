
#include "TestExecute.h"
#include "Execute.h"
#include "Impale.h"

#include "WarriorSpells.h"
#include "Target.h"
#include "Orc.h"

#include "Engine.h"
#include "Queue.h"
#include "Equipment.h"
#include "Target.h"
#include "CombatRoll.h"
#include "MeleeSpecialTable.h"

#include <QDebug>

TestExecute::TestExecute() :
    TestSpellWarrior("Execute")
{}

void TestExecute::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_has_no_cooldown();
    tear_down();

    set_up();
    test_incurs_global_cooldown_on_use();
    tear_down();

    set_up();
    test_1_of_2_improved_execute_reduces_rage_cost();
    tear_down();

    set_up();
    test_2_of_2_improved_execute_reduces_rage_cost();
    tear_down();

    set_up();
    test_removing_points_in_improved_execute_increases_rage_cost();
    tear_down();

    set_up();
    test_min_crit_dmg_0_of_2_imp_execute_0_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_0_of_2_imp_execute_0_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_1_of_2_imp_execute_0_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_1_of_2_imp_execute_0_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_2_of_2_imp_execute_0_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_2_of_2_imp_execute_0_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_0_of_2_imp_execute_1_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_0_of_2_imp_execute_1_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_1_of_2_imp_execute_1_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_1_of_2_imp_execute_1_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_2_of_2_imp_execute_1_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_2_of_2_imp_execute_1_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_0_of_2_imp_execute_2_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_0_of_2_imp_execute_2_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_1_of_2_imp_execute_2_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_1_of_2_imp_execute_2_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_2_of_2_imp_execute_2_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_2_of_2_imp_execute_2_of_2_impale();
    tear_down();
}

Execute* TestExecute::execute() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_execute();
}

void TestExecute::test_name_correct() {
    assert(execute()->get_name() == "Execute");
}

void TestExecute::test_has_no_cooldown() {
    assert(QString::number(execute()->get_cooldown(), 'f', 3) == "0.000");
}

void TestExecute::test_incurs_global_cooldown_on_use() {
    when_execute_is_performed_with_rage(100);

    then_next_event_is("CooldownReady", QString::number(warrior->global_cooldown(), 'f', 3));
}

void TestExecute::test_1_of_2_improved_execute_reduces_rage_cost() {
    assert(execute()->is_available(15));
    assert(!execute()->is_available(14));

    execute()->increase_effect_via_talent();

    assert(execute()->is_available(13));
    assert(!execute()->is_available(12));
}

void TestExecute::test_2_of_2_improved_execute_reduces_rage_cost() {
    assert(execute()->is_available(15));
    assert(!execute()->is_available(14));

    execute()->increase_effect_via_talent();
    execute()->increase_effect_via_talent();

    assert(execute()->is_available(10));
    assert(!execute()->is_available(9));
}

void TestExecute::test_removing_points_in_improved_execute_increases_rage_cost() {
    assert(execute()->is_available(15));
    assert(!execute()->is_available(14));

    execute()->increase_effect_via_talent();
    execute()->increase_effect_via_talent();

    assert(execute()->is_available(10));
    assert(!execute()->is_available(9));

    execute()->decrease_effect_via_talent();

    assert(execute()->is_available(13));
    assert(!execute()->is_available(12));

    execute()->decrease_effect_via_talent();

    assert(execute()->is_available(15));
    assert(!execute()->is_available(14));
}

void TestExecute::test_min_crit_dmg_0_of_2_imp_execute_0_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_0_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(15);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1200] = (600 + 15 * (15 - 15)) * 2.0
    then_damage_dealt_is(1200);
}

void TestExecute::test_max_crit_dmg_0_of_2_imp_execute_0_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_0_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [3750] = (600 + 15 * (100 - 15)) * 2.0
    then_damage_dealt_is(3750);
}

void TestExecute::test_min_crit_dmg_1_of_2_imp_execute_0_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_0_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(13);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1200] = (600 + 15 * (13 - 13)) * 2.0
    then_damage_dealt_is(1200);
}

void TestExecute::test_max_crit_dmg_1_of_2_imp_execute_0_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_0_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [3810] = (600 + 15 * (100 - 13)) * 2.0
    then_damage_dealt_is(3810);
}

void TestExecute::test_min_crit_dmg_2_of_2_imp_execute_0_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_0_of_2_impale();
    given_2_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(10);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1200] = (600 + 15 * (10 - 10)) * 2.0
    then_damage_dealt_is(1200);
}

void TestExecute::test_max_crit_dmg_2_of_2_imp_execute_0_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_0_of_2_impale();
    given_2_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [3900] = (600 + 15 * (100 - 10)) * 2.0
    then_damage_dealt_is(3900);
}

void TestExecute::test_min_crit_dmg_0_of_2_imp_execute_1_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(15);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1260] = (600 + 15 * (15 - 15)) * 2.1
    then_damage_dealt_is(1260);
}

void TestExecute::test_max_crit_dmg_0_of_2_imp_execute_1_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [3938] = (600 + 15 * (100 - 15)) * 2.1
    // TODO: 3937.5 is erroneously rounded to 3937 instead of 3938. Consider using ceil.
    then_damage_dealt_is(3937);
}

void TestExecute::test_min_crit_dmg_1_of_2_imp_execute_1_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(13);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1260] = (600 + 15 * (13 - 13)) * 2.1
    then_damage_dealt_is(1260);
}

void TestExecute::test_max_crit_dmg_1_of_2_imp_execute_1_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [4001] = (600 + 15 * (100 - 13)) * 2.1
    // TODO: 4000.5 is erroneously rounded to 4000 instead of 4000. Consider using ceil.
    then_damage_dealt_is(4000);
}

void TestExecute::test_min_crit_dmg_2_of_2_imp_execute_1_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_2_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(10);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1260] = (600 + 15 * (10 - 10)) * 2.1
    then_damage_dealt_is(1260);
}

void TestExecute::test_max_crit_dmg_2_of_2_imp_execute_1_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_2_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [4095] = (600 + 15 * (100 - 10)) * 2.1
    then_damage_dealt_is(4095);
}

void TestExecute::test_min_crit_dmg_0_of_2_imp_execute_2_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_2_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(15);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1320] = (600 + 15 * (15 - 15)) * 2.2
    then_damage_dealt_is(1320);
}

void TestExecute::test_max_crit_dmg_0_of_2_imp_execute_2_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_2_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [4125] = (600 + 15 * (100 - 15)) * 2.2
    then_damage_dealt_is(4125);
}

void TestExecute::test_min_crit_dmg_1_of_2_imp_execute_2_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_2_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(13);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1320] = (600 + 15 * (13 - 13)) * 2.2
    then_damage_dealt_is(1320);
}

void TestExecute::test_max_crit_dmg_1_of_2_imp_execute_2_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_2_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [4191] = (600 + 15 * (100 - 13)) * 2.2
    then_damage_dealt_is(4191);
}

void TestExecute::test_min_crit_dmg_2_of_2_imp_execute_2_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_2_of_2_impale();
    given_2_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(10);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1320] = (600 + 15 * (10 - 10)) * 2.2
    then_damage_dealt_is(1320);
}

void TestExecute::test_max_crit_dmg_2_of_2_imp_execute_2_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_2_of_2_impale();
    given_2_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [4290] = (600 + 15 * (100 - 10)) * 2.2
    then_damage_dealt_is(4290);
}

void TestExecute::given_0_of_2_improved_execute() {
    assert(execute()->is_available(15));
    assert(!execute()->is_available(14));
}

void TestExecute::given_1_of_2_improved_execute() {
    execute()->increase_effect_via_talent();

    assert(execute()->is_available(13));
    assert(!execute()->is_available(12));
}

void TestExecute::given_2_of_2_improved_execute() {
    execute()->increase_effect_via_talent();
    execute()->increase_effect_via_talent();

    assert(execute()->is_available(10));
    assert(!execute()->is_available(9));
}

void TestExecute::when_execute_is_performed_with_rage(const int rage) {
    execute()->perform(rage);
}
