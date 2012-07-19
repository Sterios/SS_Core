#include "ScriptPCH.h"
#include "Player.h"

class mob_resurrect : public PlayerScript
{
public:
    mob_resurrect() : PlayerScript("mob_resurrect") {}

    void OnPVPKill(Player*/*Creature* */ killer, Player* killed)
    {
        if (killer->GetAreaId() == 2397 || killer->GetAreaId() == 2318)
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

            if (killed->GetAreaId() == 2397)
                killed->TeleportTo(0, -1027.199951f, 1577.650024f, 53.460999f, 0.022043f, 0);
            if (killed->GetAreaId() == 2318)
                killed->TeleportTo(1, -4795.683105f, -4482.359863f, 121.690331f, 3.077888f, 0);
        }
    }
};

void AddSC_mob_resurrect()
{
    new mob_resurrect();
}
