#include "ScriptPCH.h" 
#include "ScriptMgr.h" 
#include "Config.h" 
 
class duel_reset : public PlayerScript 
{ 
public: 
    duel_reset() : PlayerScript("duel_reset") {} 
 
    void OnDuelEnd(Player *winner, Player *looser, DuelCompleteType type) 
    { 
        if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWN_ON_FINISH)) 
        { 
            if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWN_ONLY_IN_ELWYNN_AND_DUROTAR)) 
            { 
                if(winner->GetZoneId() == 14 || winner->GetZoneId() == 12) 
                { 
                    if (type == DUEL_WON) 
                    { 
                        winner->RemoveArenaSpellCooldowns(); 
                        looser->RemoveArenaSpellCooldowns(); 
                        winner->SetHealth(winner->GetMaxHealth()); 
                        looser->SetHealth(looser->GetMaxHealth()); 
 
                        if (winner->getPowerType() == POWER_MANA)  
                            winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA)); 
 
                        if (looser->getPowerType() == POWER_MANA)  
                            looser->SetPower(POWER_MANA, looser->GetMaxPower(POWER_MANA)); 
                    } 
                    winner->HandleEmoteCommand(EMOTE_ONESHOT_CHEER); 
                } 
            } 
 
            else 
                if (type == DUEL_WON) 
                { 
                    winner->RemoveArenaSpellCooldowns(); 
                    looser->RemoveArenaSpellCooldowns(); 
                    winner->SetHealth(winner->GetMaxHealth()); 
                    looser->SetHealth(looser->GetMaxHealth()); 
 
                    if (winner->getPowerType() == POWER_MANA)  
                        winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA)); 
 
                    if (looser->getPowerType() == POWER_MANA)  
                        looser->SetPower(POWER_MANA, looser->GetMaxPower(POWER_MANA)); 
                } 
                winner->HandleEmoteCommand(EMOTE_ONESHOT_CHEER); 
        } 
    } 
 
    void OnDuelStart(Player *player1, Player *player2) 
    { 
        if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWN_ON_START)) 
        { 
            if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWN_ONLY_IN_ELWYNN_AND_DUROTAR)) 
            { 
                if(player1->GetZoneId() == 14 || player1->GetZoneId() == 12) 
                { 
                        player1->RemoveArenaSpellCooldowns(); 
                        player2->RemoveArenaSpellCooldowns(); 
                        player1->SetHealth(player1->GetMaxHealth()); 
                        player2->SetHealth(player2->GetMaxHealth()); 
 
                        if (player1->getPowerType() == POWER_MANA)  
                            player1->SetPower(POWER_MANA, player1->GetMaxPower(POWER_MANA)); 
 
                        if (player2->getPowerType() == POWER_MANA)  
                            player2->SetPower(POWER_MANA, player2->GetMaxPower(POWER_MANA)); 
                } 
            } 
 
            else 
                    player1->RemoveArenaSpellCooldowns(); 
                    player2->RemoveArenaSpellCooldowns(); 
                    player1->SetHealth(player1->GetMaxHealth()); 
                    player2->SetHealth(player2->GetMaxHealth()); 
 
                    if (player1->getPowerType() == POWER_MANA)  
                        player1->SetPower(POWER_MANA, player1->GetMaxPower(POWER_MANA)); 
 
                    if (player2->getPowerType() == POWER_MANA)  
                        player2->SetPower(POWER_MANA, player2->GetMaxPower(POWER_MANA)); 
        } 
    } 
}; 
 
void AddSC_DuelReset() 
{ 
    new duel_reset(); 
} 

