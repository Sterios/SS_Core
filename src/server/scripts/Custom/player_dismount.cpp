#include "ScriptPCH.h"
#include "Player.h"
#include "Unit.h"

class player_dismount : public PlayerScript
{
public:
    player_dismount() : PlayerScript("player_dismount") {}

    void OnUpdateZone(Player* player, uint32 /*newZone*/, uint32 /*newArea*/)
    {
        if (player->IsMounted() && player->GetAreaId() == 2318)
        {
            player->Dismount();
        }
    }
};

void AddSC_player_dismount()
{
    new player_dismount();
}
