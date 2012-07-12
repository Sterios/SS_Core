
#include "ScriptPCH.h"

enum ActNpcRename
{
    ACT_RENAME                 = 1001,
    ACT_CUSTOMIZE              = 1002,
    ACT_CUSTOMIZE_RACE         = 1003,
    ACT_CONFIRM_RENAME         = 1004,
    ACT_CONFIRM_CUSTOMIZE      = 1005,
    ACT_CONFIRM_CUSTOMIZE_RACE = 1006,
    ACT_CHANGE_RACE            = 1007,
    ACT_CONFIRM_CUSTOMIZE_RACE_CHANGE = 1008
};

#define PRISE_RENAME_CHAR_AP    1000000000
#define PRISE_CUSTOMIZE_CHAR_AP 500000000
#define PRISE_CUSTOMIZE_RACE_CHAR_AP 2000000000
#define PRISE_CUSTOMIZE_RACE_CHANGE_AP 1500000000

#define GOSSIP_RENAME_HELLO "Изменить свой ник!"
#define GOSSIP_CUSTOMIZE_HELLO "Поменять внешность и пол!"
#define GOSSIP_CUSTOMIZE_RACE_CHANGE_HELLO "Изменить рассу!"
#define GOSSIP_CUSTOMIZE_RACE_HELLO "Сменить Фракцию (Альянс/Орда)!"

#define GOSSIP_RENAME_CONFIRM "Cтоимость смены ника 100.000 Золотых. Вас устраивает? (Требуется перезайти в игру, чтобы изменения вступили в силу)."
#define GOSSIP_CUSTOMIZE_CONFIRM "Стоимость смены внешнего вида и пола 50.000. Вас устраивает? (Требуется перезайти в игру, чтобы изменения вступили в силу)."
#define GOSSIP_CUSTOMIZE_RACE_CHANGE_CONFIRM "Стоимость смены рассы 150.000 золотых. Вас устраивает? (Требуется перезайти в игру, чтобы изменения вступили в силу)."
#define GOSSIP_CUSTOMIZE_RACE_CONFIRM "Стоимость смены фракции 200.000 золотых. Вас устраивает? (Требуется перезайти в игру, чтобы изменения вступили в силу, возможны необратимые последствия – потеря магических навыков, и одежды, обмену не подлежит)."

#define MSG_NOT_MONEY_FOR_RENAME "Вы банкрот! Проваливайте..."
#define MSG_COMPLETE_RENAME "Готово, теперь выйди из игры и зайди снова. Вам будет предложено ввести новое Имя!"
#define MSG_COMPLETE_CUSTOMIZE "Готово! Теперь выйди из игры и зайди снова. Вам будет предложено изменить свой Внешний вид и Пол!"
#define MSG_COMPLETE_RACE_CHANGE "Готово! Теперь выйди из игры и зайди снова. Вам будет предложено изменить рассу!"
#define MSG_COMPLETE_RACE_CUSTOMIZE "Готово, теперь выйди из игры и зайди снова. Вам будет предложено сменить Фракцию (Альянс/Орда)!"

class npc_customize : public CreatureScript
{
public:
    npc_customize() : CreatureScript("npc_customize") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_RENAME_HELLO, GOSSIP_SENDER_MAIN, ACT_RENAME);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CUSTOMIZE_HELLO, GOSSIP_SENDER_MAIN, ACT_CUSTOMIZE);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CUSTOMIZE_RACE_CHANGE_HELLO, GOSSIP_SENDER_MAIN, ACT_CHANGE_RACE);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CUSTOMIZE_RACE_HELLO, GOSSIP_SENDER_MAIN, ACT_CUSTOMIZE_RACE);		
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        if (uiSender != GOSSIP_SENDER_MAIN)
            return false;

        pPlayer->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
        case ACT_RENAME:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_RENAME_CONFIRM, GOSSIP_SENDER_MAIN, ACT_CONFIRM_RENAME);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
            break;
        case ACT_CUSTOMIZE:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CUSTOMIZE_CONFIRM, GOSSIP_SENDER_MAIN, ACT_CONFIRM_CUSTOMIZE);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
            break;
        case ACT_CHANGE_RACE:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CUSTOMIZE_RACE_CHANGE_CONFIRM, GOSSIP_SENDER_MAIN, ACT_CONFIRM_CUSTOMIZE_RACE_CHANGE);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
            break;
        case ACT_CUSTOMIZE_RACE:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CUSTOMIZE_RACE_CONFIRM, GOSSIP_SENDER_MAIN, ACT_CONFIRM_CUSTOMIZE_RACE);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
            break;			
        case ACT_CONFIRM_RENAME:
            if (pPlayer->GetMoney() < PRISE_RENAME_CHAR_AP)
            {
                pCreature->MonsterWhisper(MSG_NOT_MONEY_FOR_RENAME, pPlayer->GetGUID());
            }else{
                pCreature->MonsterWhisper(MSG_COMPLETE_RENAME, pPlayer->GetGUID());
                pPlayer->ModifyMoney(-PRISE_RENAME_CHAR_AP);
                pPlayer->SetAtLoginFlag(AT_LOGIN_RENAME);
            }
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case ACT_CONFIRM_CUSTOMIZE:
            if (pPlayer->GetMoney() < PRISE_CUSTOMIZE_CHAR_AP)
            {
                pCreature->MonsterWhisper(MSG_NOT_MONEY_FOR_RENAME, pPlayer->GetGUID());
            }else{
                pCreature->MonsterWhisper(MSG_COMPLETE_CUSTOMIZE, pPlayer->GetGUID());
                pPlayer->ModifyMoney(-PRISE_CUSTOMIZE_CHAR_AP);
                pPlayer->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
            }
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case ACT_CONFIRM_CUSTOMIZE_RACE_CHANGE:
            if (pPlayer->GetMoney() < PRISE_CUSTOMIZE_RACE_CHANGE_AP)
            {  
                pCreature->MonsterWhisper(MSG_NOT_MONEY_FOR_RENAME, pPlayer->GetGUID());
            }else{
                pCreature->MonsterWhisper(MSG_COMPLETE_RACE_CHANGE, pPlayer->GetGUID());
                pPlayer->ModifyMoney(-PRISE_CUSTOMIZE_RACE_CHANGE_AP);
                pPlayer->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
            }
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case ACT_CONFIRM_CUSTOMIZE_RACE:
            if (pPlayer->GetMoney() < PRISE_CUSTOMIZE_RACE_CHAR_AP)
            {
                pCreature->MonsterWhisper(MSG_NOT_MONEY_FOR_RENAME, pPlayer->GetGUID());
            }else{
                pCreature->MonsterWhisper(MSG_COMPLETE_RACE_CUSTOMIZE, pPlayer->GetGUID());
                pPlayer->ModifyMoney(-PRISE_CUSTOMIZE_RACE_CHAR_AP);
                pPlayer->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
            }
            pPlayer->CLOSE_GOSSIP_MENU();
            break;			
        default:
            pPlayer->CLOSE_GOSSIP_MENU();
        }
        return true;
    }
};

void AddSC_npc_customize()
{
    new npc_customize;
}
