#include "dialog.h"
#include "Date.h"
WM_HWIN hPage[4];
extern WM_HWIN Main_status(void);
extern WM_HWIN CreateWindow(void);
extern Measure measure;
extern TongDao tongdao;
void MainTask(void)
{
   // GUI_TIMER_HANDLE hTimer;
    GUI_Init();									//初始化emWin/ucGUI
    GUI_UC_SetEncodeUTF8();
    TEXT_SetDefaultTextColor(GUI_WHITE);
    WINDOW_SetDefaultBkColor(GUI_BLACK);
    BUTTON_SetDefaultSkinClassic();
    SCROLLBAR_SetDefaultSkinClassic();
    BUTTON_SetDefaultTextColor(GUI_WHITE,BUTTON_CI_UNPRESSED);
    BUTTON_SetDefaultBkColor(GUI_BLACK,BUTTON_CI_UNPRESSED);

    LISTBOX_SetDefaultBkColor(LISTBOX_CI_UNSEL,GUI_BLACK);
    LISTBOX_SetDefaultTextColor(LISTBOX_CI_UNSEL,GUI_WHITE);
    LISTBOX_SetDefaultBkColor(LISTBOX_CI_SELFOCUS,GUI_WHITE);
    LISTBOX_SetDefaultTextColor(LISTBOX_CI_SELFOCUS,GUI_BLACK);
    LISTBOX_SetDefaultBkColor(LISTBOX_CI_SEL,GUI_BLACK);
    LISTBOX_SetDefaultTextColor(LISTBOX_CI_SEL,GUI_WHITE);

    SCROLLBAR_SetDefaultColor(GUI_BLACK,SCROLLBAR_CI_ARROW);
    SCROLLBAR_SetDefaultColor(GUI_WHITE,SCROLLBAR_CI_THUMB);
    SCROLLBAR_SetDefaultColor(GUI_BLACK,SCROLLBAR_CI_SHAFT);

    EDIT_SetDefaultBkColor(1,GUI_BLACK);
    EDIT_SetDefaultTextColor(1,GUI_WHITE);
    Date_Init();

    Main_status();
    //Menu_lock();
    //Menu_list();
    while(1) {GUI_Delay(20);}					//调用GUI_Delay函数延时20MS(最终目的是调用GUI_Exec()函数)
}

/*
static void _cbEdit0(WM_MESSAGE *pMsg)
{
    WM_HWIN hItem;
    WM_MESSAGE Msg;
    switch (pMsg->MsgId)
    {
    case WM_KEY:
        switch(((WM_KEY_INFO*)(pMsg->Data.p))->Key)
        {
            case GUI_KEY_ENTER:
                if(!(((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt))
                    //WM_SendToParent(pMsg->hWin,pMsg);
                    GUI_SendKeyMsg(GUI_KEY_ENTER,1);
                break;
            default:EDIT_Callback(pMsg);
        }
    break;
    default:
        EDIT_Callback(pMsg);
    }
}
*/
