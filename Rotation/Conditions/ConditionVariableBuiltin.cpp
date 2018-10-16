
#include "ConditionVariableBuiltin.h"
#include "Character.h"
#include "CharacterStats.h"
#include "Spells.h"
#include "Engine.h"
#include "MainhandAttack.h"
#include "SimSettings.h"

ConditionVariableBuiltin::ConditionVariableBuiltin(Character* pchar,
                                                   const int builtin,
                                                   const int comparator,
                                                   const double cmp_value) :
    pchar(pchar),
    engine(pchar->get_engine()),
    builtin(builtin),
    comparator(comparator),
    rhs_value(cmp_value)
{}

bool ConditionVariableBuiltin::condition_fulfilled() const {
    switch (builtin) {
    case BuiltinVariables::TargetHealth: {
        int combat_length = pchar->get_sim_settings()->get_combat_length();
        double remaining_health = (combat_length - engine->get_current_priority()) / combat_length;
        return cmp_values(remaining_health);
    }
    case BuiltinVariables::TimeRemainingEncounter: {
        int combat_length = pchar->get_sim_settings()->get_combat_length();
        double remaining_encounter_time = combat_length - engine->get_current_priority();
        return cmp_values(remaining_encounter_time);
    }
    case BuiltinVariables::TimeRemainingExecute: {
        int combat_length = pchar->get_sim_settings()->get_combat_length();
        double remaining_execute_time = combat_length * 0.8 - engine->get_current_priority();
        return cmp_values(remaining_execute_time);
    }
    case BuiltinVariables::SwingTimer: {
        double delta = pchar->get_stats()->get_mh_wpn_speed() - pchar->get_spells()->get_mh_attack()->get_cooldown_remaining();
        return delta < 0.4;
    }
    default:
        assert(false);
        return false;
    }
}

bool ConditionVariableBuiltin::cmp_values(const double lhs_value) const {
    switch (comparator) {
    case Comparators::less:
    case Comparators::leq:
        return lhs_value < rhs_value;
    case Comparators::eq:
        return (lhs_value - rhs_value) < 0.000001;
    case Comparators::geq:
    case Comparators::greater:
        return lhs_value > rhs_value;
    default:
        assert(false);
        return false;
    }
}
