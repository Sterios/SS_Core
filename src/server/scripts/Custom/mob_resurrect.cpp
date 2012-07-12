#include "ScriptPCH.h"
#include "Player.h"

const Position allyPositions[1] =
{
    { -1027.197632f, 1577.646851f, 53.460976f, 0.022043f }
};

const Position hordePositions[1] =
{
    { -1027.197632f, 1577.646851f, 53.460976f, 0.022043f }
};

class mob_resurrect : public PlayerScript
{
public:
    mob_resurrect() : PlayerScript("mob_resurrect") {}

    void OnPVPKill(Player*/*Creature* */ killer, Player* killed)
    {
        if (killer->GetAreaId() == 2397) /*&& killed->GetMapId() == 0*/
        {
            if (killed->HasAuraType(SPELL_AURA_SPIRIT_OF_REDEMPTION))
                killed->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);

            killed->KillPlayer();
            killed->ResurrectPlayer(40.0f, true);

            if (Aura * aur = killed->GetAura(15007))
                aur->SetDuration(1*MINUTE*IN_MILLISECONDS); // 1 Минута Слабость после воскрешения

            killed->CastSpell(killed, 13874, true);
            if (Aura * aur = killed->GetAura(13874))
                aur->SetDuration(1*MINUTE*IN_MILLISECONDS); // 1 Минута Божественный щит

            uint32 rnd = urand(0,1);
            if (killed->GetTeam() == ALLIANCE)
                killed->TeleportTo(0, allyPositions[rnd].GetPositionX(), allyPositions[rnd].GetPositionY(), allyPositions[rnd].GetPositionZ(), allyPositions[rnd].GetOrientation());
            else
                killed->TeleportTo(0, hordePositions[rnd].GetPositionX(), hordePositions[rnd].GetPositionY(), hordePositions[rnd].GetPositionZ(), hordePositions[rnd].GetOrientation());
        }
    }
};

void AddSC_mob_resurrect()
{
    new mob_resurrect();
}
