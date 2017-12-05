/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
#include "Date.h"
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_LISTBOX_0 (GUI_ID_USER + 0x01)
#define ID_EDIT_0 (GUI_ID_USER + 0x02)
#define ID_EDIT_1 (GUI_ID_USER + 0x03)
#define ID_EDIT_2 (GUI_ID_USER + 0x04)
#define ID_EDIT_3 (GUI_ID_USER + 0x05)
#define ID_SCROLLBAR_0 (GUI_ID_USER + 0x06)
// USER START (Optionally insert additional defines)
#define ID_TEXT_0 (GUI_ID_USER + 0x07)
#define ID_TEXT_1 (GUI_ID_USER + 0x08)
#define ID_TEXT_2 (GUI_ID_USER + 0x09)
#define ID_LISTBOX_1 (GUI_ID_USER + 0x0A)
#define ID_LISTBOX_2 (GUI_ID_USER + 0x0B)
#define ID_LISTBOX_3 (GUI_ID_USER + 0x0C)
#define ID_LISTBOX_4 (GUI_ID_USER + 0x0D)
#define ID_LISTBOX_5 (GUI_ID_USER + 0x0E)
#define ID_LISTBOX_6 (GUI_ID_USER + 0x0F)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)

// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { LISTBOX_CreateIndirect, "Listbox", ID_LISTBOX_0, 0, 0, 40, 66, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 64, 0, 78, 16, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_1, 64, 16, 78, 16, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 64, 32, 78, 16, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_3, 64, 48, 78, 16, 0, 0x64, 0 },
  { SCROLLBAR_CreateIndirect, "Scrollbar", ID_SCROLLBAR_0, 118, 0, 10, 64, 8, 0x0, 0 },
  { LISTBOX_CreateIndirect, "Listbox", ID_LISTBOX_1, 64, 100, 78, 18, 0, 0x0, 0 },
  { LISTBOX_CreateIndirect, "Listbox", ID_LISTBOX_2, 64, 116, 78, 18, 0, 0x0, 0 },
  { LISTBOX_CreateIndirect, "Listbox", ID_LISTBOX_3, 64, 132, 78, 18, 0, 0x0, 0 },
  { LISTBOX_CreateIndirect, "Listbox", ID_LISTBOX_4, 64, 148, 78, 18, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 20, 100, 160, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 20, 130, 160, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_2, 20, 160, 160, 30, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
extern WM_HWIN Menu_main(WM_HWIN hParent);
extern WM_HWIN Menu_list(void);
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontm_font16;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontPT;

extern TongDao tongdao;

void ReOrder(const uint8_t listbox_position,const uint32_t arrstate,WM_MESSAGE * pMsg)
{
    WM_HWIN hItem;
    uint8_t i;
    float Value;
    for(i=0;i<4;i++)
    {
        if((arrstate>>(listbox_position+i))&0x01)
        {
            WM_MoveTo(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_1+i),40,16*i);
            WM_MoveTo(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0+i),40,100+16*i);
        }
        else
        {
            WM_MoveTo(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_1+i),40,100+16*i);
            WM_MoveTo(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0+i),40,16*i);
        }
    }/*
    switch(listbox_position)
    {
    case 0:
        {
            hItem=WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_1);
            for(i=0;i<sizeof(arr10)/sizeof(arr10[0]);i++)
                LISTBOX_AddString(hItem,arr10[i]);
            LISTBOX_SetFont(hItem,&GUI_FontPT);
            LISTBOX_SetSel(hItem,tongdao.Type);
            hItem=WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_2);
            for(i=0;i<sizeof(arr11)/sizeof(arr11[0]);i++)
                LISTBOX_AddString(hItem,arr11[i]);
            LISTBOX_SetFont(hItem,GUI_FONT_13_ASCII);
            LISTBOX_SetSel(hItem,tongdao.uint[0]);
            hItem=WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
            EDIT_SetFloatMode(hItem,Value,-999999,999999,3,0|GUI_EDIT_SUPPRESS_LEADING_ZEROES);
            EDIT_SetFloatValue(hItem,tongdao.Range[0][2]);
            hItem=WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
            EDIT_SetFloatMode(hItem,Value,-999999,999999,3,0|GUI_EDIT_SUPPRESS_LEADING_ZEROES);
            EDIT_SetFloatValue(hItem,tongdao.Range[0][1]);
        };break;
        case 1:
            {

            };break;
        case 2:;break;
        case 3:;break;
        case 4:;break;
        case 5:;break;
        case 6:;break;
        case 7:;break;
        case 8:;break;
        case 9:;break;
        case 0xA:;break;
        case 0xB:;break;
        case 0xC:;break;
    }*/
}
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  uint8_t temp[20];
  static uint8_t listbox_offset=0;
  static uint8_t listbox_position=0;
  uint8_t arr1[][10]={"自动","差压","上限","下限","切除","差压","压力","上限","下限","切除","压力","温度","上限","下限","切除","温度"};
  uint8_t arr10[][10]={"自动","T,P,△P","PT,P,△P","T,△P","PT,△P","P,△P ","△P "};
  uint8_t arr11[][10]={"Pa","KPa","MPa","KgF"};
  uint8_t arr[]="asdfghjklzxcvbnm,qwertyuio";
  uint32_t arrstate=0xc631;
  uint8_t i,j;
  static uint8_t hWin_v[20];
  static uint8_t hlist=0;
  static uint8_t t=0;
  volatile double x[4];
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    for(i=0;i<6;i++)
        hWin_v[i]=WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_1+i);
    //
    // Initialization of 'Listbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
    for(i=0;i<sizeof(arr1)/sizeof(arr1[0]);i++)
    {
        LISTBOX_AddString(hItem, arr1[i]);
    }
    LISTBOX_SetFont(hItem,&GUI_Fontm_font16);
    for(i=0;i<sizeof(arr10)/sizeof(arr10[0]);i++)
        LISTBOX_AddString(hWin_v[0], arr10[i]);
    LISTBOX_SetFont(hItem,&GUI_FontPT);
    for(j=0;j<6;j++)
    {
        for(i=0;i<sizeof(arr11)/sizeof(arr11[0]);i++)
            LISTBOX_AddString(hWin_v[j+1], arr11[i]);
        LISTBOX_SetFont(hItem,GUI_FONT_13_ASCII);
    }
    //
    // Initialization of 'Edit'
    //
    for(i=0;i<4;i++)
    {
        hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0+i);
        EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
        EDIT_SetFont(hItem, GUI_FONT_10_ASCII);
        EDIT_SetFloatMode(hItem,x[i],-999999,999999,3,0|GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    }

    //
    //
    for(i=0;i<4;i++)
    {
        if((arrstate>>(i))&0x01)
        {
            WM_MoveTo(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_1+i),40,16*i);
            WM_MoveTo(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0+i),40,100+16*i);
        }
        else
        {
            WM_MoveTo(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_1+i),40,100+16*i);
            WM_MoveTo(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0+i),40,16*i);
        }
    LISTBOX_SetTextAlign(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_1+i),GUI_TA_HCENTER|GUI_TA_VCENTER);
    LISTBOX_SetFont(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_1+i),&GUI_Fontm_font16);
    }
    SCROLLBAR_SetNumItems(WM_GetDialogItem(pMsg->hWin, ID_SCROLLBAR_0),21);
    listbox_offset=0;
    listbox_position=0;
    //
    WM_CreateTimer(pMsg->hWin,0x01,50,0);
    // USER END
    break;
  // USER START (Optionally insert additional message handling)

  case WM_TIMER:
      {
          //x=EDIT_GetFloatValue(hWin_v[1]);
        sprintf(temp,"%d",listbox_position);
        TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_0), temp);
        hItem=WM_GetFocussedWindow();
            if(hItem==hWin_v[0])
            {
        sprintf(temp,"%lf",x[1]);
        TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_1), temp);
            }

        WM_RestartTimer(pMsg->Data.v,500);
      }

        break;

  case WM_KEY:
    switch(((WM_KEY_INFO*)(pMsg->Data.p))->Key)
    {
    case GUI_KEY_ENTER:
        if((((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt))
        {
            hItem=WM_GetFocussedWindow();
            if(hItem==hWin_v[0])
            {
                if((arrstate>>(listbox_position+listbox_offset))&0x01)
                    WM_SetFocus(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_1+listbox_offset));
                else
                    WM_SetFocus(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0+listbox_offset));
            }
            else if(hItem==hWin_v[1]||hItem==hWin_v[9])
                WM_SetFocus(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0));
            else if(hItem==hWin_v[2]||hItem==hWin_v[10])
                WM_SetFocus(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0));
            else if(hItem==hWin_v[3]||hItem==hWin_v[11])
                WM_SetFocus(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0));
            else if(hItem==hWin_v[4]||hItem==hWin_v[12])
                WM_SetFocus(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0));
        }
        WM_DefaultProc(pMsg);
        break;
    case GUI_KEY_UP:
        if(!(((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt))
        {
            hItem=WM_GetFocussedWindow();
            if(hItem==hWin_v[0])
            {
                if(listbox_offset>0)
                    listbox_offset--;
                listbox_position=LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0))-listbox_offset;
                ReOrder(listbox_position,arrstate,pMsg);
                SCROLLBAR_SetValue(WM_GetDialogItem(pMsg->hWin, ID_SCROLLBAR_0),LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0)));
            }
            else if(hItem==hWin_v[1]);
            else if(hItem==hWin_v[2]);
            else if(hItem==hWin_v[3]);
            else if(hItem==hWin_v[4]);
        }
        WM_DefaultProc(pMsg);
        break;
    case GUI_KEY_DOWN:
        if(!(((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt))
        {
            hItem=WM_GetFocussedWindow();
            if(hItem==hWin_v[0])
            {
                if(listbox_offset<3)
                    listbox_offset++;
                listbox_position=LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0))-listbox_offset;
                ReOrder(listbox_position,arrstate,pMsg);
                SCROLLBAR_SetValue(WM_GetDialogItem(pMsg->hWin, ID_SCROLLBAR_0),LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0)));
            }
            else if(hItem==hWin_v[1]);
            else if(hItem==hWin_v[2]);
            else if(hItem==hWin_v[3]);
            else if(hItem==hWin_v[4]);
        }
        break;
    case GUI_KEY_LEFT:
        if(!(((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt))
        {
            hItem=WM_GetFocussedWindow();
            if(hItem==hWin_v[0])
            {
                WM_DeleteWindow(pMsg->hWin);
                Menu_list();
            }
            else if(hItem==hWin_v[1]);
            else if(hItem==hWin_v[2]);
            else if(hItem==hWin_v[3]);
            else if(hItem==hWin_v[4]);
        }
        break;
    case GUI_KEY_RIGHT:
        if(!(((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt))
        {
            hItem=WM_GetFocussedWindow();
            if(hItem==hWin_v[0]);
            else if(hItem==hWin_v[1]);
            else if(hItem==hWin_v[2]);
            else if(hItem==hWin_v[3]);
            else if(hItem==hWin_v[4]);
        }
    }
    break;
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN Menulist_1(void);
WM_HWIN Menulist_1(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
