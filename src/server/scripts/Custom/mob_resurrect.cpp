#include "ScriptPCH.h"
#include "Player.h"

const Position duelareaPositions[1] =
{
    { -1027.197632f, 1577.646851f, 53.460976f, 0.022043f }
};

const Position jumpsPositions[1] =
{
    { -4795.683105f, -4482.359863f, 121.690331f, 3.077888f }
};

class mob_resurrect : public PlayerScript
{
public:
    mob_resurrect() : PlayerScript("mob_resurrect") {}

    void OnPVPKill(Player*/*Creature* */ killer, Player* killed)
    {
        if (killer->GetAreaId() == 2397 || killer->GetAreaId() == 2318)/* && killed->GetMapId() == 1)*/
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
            if (killed->GetAreaId() == 2397)
                killed->TeleportTo(0, duelareaPositions[rnd].GetPositionX(), duelareaPositions[rnd].GetPositionY(), duelareaPositions[rnd].GetPositionZ(), duelareaPositions[rnd].GetOrientation());
            if (killed->GetAreaId() == 2318)
                killed->TeleportTo(1, jumpsPositions[rnd].GetPositionX(), jumpsPositions[rnd].GetPositionY(), jumpsPositions[rnd].GetPositionZ(), jumpsPositions[rnd].GetOrientation());
        }
    }
};

void AddSC_mob_resurrect()
{
    new mob_resurrect();
}
