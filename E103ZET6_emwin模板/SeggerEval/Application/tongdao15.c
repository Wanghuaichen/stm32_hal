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
#define ID_TEXT_0 (GUI_ID_USER + 0x01)
#define ID_LISTBOX_0 (GUI_ID_USER + 0x02)
#define ID_EDIT_0 (GUI_ID_USER + 0x03)
#define ID_EDIT_1 (GUI_ID_USER + 0x04)
#define ID_EDIT_2 (GUI_ID_USER + 0x05)


// USER START (Optionally insert additional defines)
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
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 128, 64, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 0, 0, 128, 16, 0, 0x64, 0 },
  { LISTBOX_CreateIndirect, "Listbox", ID_LISTBOX_0, 0, 16, 40, 50, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 40, 16, 88, 16, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_1, 40, 32, 88, 16, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 40, 48, 88, 16, 0, 0x64, 0 },
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
extern GUI_CONST_STORAGE GUI_FONT GUI_FontST16;
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
  static WM_HWIN hWin_v[5];
  uint8_t i;
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "零点");
    TEXT_SetFont(hItem, &GUI_FontST16);
    //
    // Initialization of 'Listbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
    LISTBOX_AddString(hItem, "差压");
    LISTBOX_AddString(hItem, "压力");
    LISTBOX_AddString(hItem, "温度");
    LISTBOX_SetFont(hItem, &GUI_FontST16);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    EDIT_SetFloatMode(hItem,tongdao.Range[0][0],-999,999,6,GUI_EDIT_SIGNED|GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    EDIT_SetFloatValue(hItem,tongdao.Range[0][0]);
    EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
    EDIT_SetFloatMode(hItem,tongdao.Range[1][0],-999,999,6,GUI_EDIT_SIGNED|GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    EDIT_SetFloatValue(hItem,tongdao.Range[1][0]);
    EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
    EDIT_SetFloatMode(hItem,tongdao.Range[2][0],-999,999,6,GUI_EDIT_SIGNED|GUI_EDIT_SUPPRESS_LEADING_ZEROES);
    EDIT_SetFloatValue(hItem,tongdao.Range[2][0]);
    EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    // USER START (Optionally insert additional code for further widget initialization)
    for(i=0;i<4;i++)
    {
        hWin_v[i]=WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0+i);
    }
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_LISTBOX_0: // Notifications sent by 'Listbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_0: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_1: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_2: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
    case WM_KEY:
    switch(((WM_KEY_INFO*)(pMsg->Data.p))->Key)
    {
    case GUI_KEY_ENTER:
        if((((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt))
        {
            hItem=WM_GetFocussedWindow();
            if(hItem==hWin_v[0])
            {
                i=LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0));
                hItem=WM_GetDialogItem(pMsg->hWin, ID_EDIT_0+i);
                WM_SetFocus(hItem);
                EDIT_EnableBlink(hItem,500,1);
            }
            else if(hItem==hWin_v[1])
            {
                tongdao.Range[0][0]=EDIT_GetFloatValue(hWin_v[1]);
                WM_SetFocus(hWin_v[0]);
            }
            else if(hItem==hWin_v[2])
            {
                tongdao.Range[1][0]=EDIT_GetFloatValue(hWin_v[2]);
                WM_SetFocus(hWin_v[0]);
            }
            else if(hItem==hWin_v[3])
            {
                tongdao.Range[2][0]=EDIT_GetFloatValue(hWin_v[3]);
                WM_SetFocus(hWin_v[0]);
            }
        }
        WM_DefaultProc(pMsg);
        break;
    case GUI_KEY_LEFT:
        if(!(((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt))
        {
            hItem=WM_GetFocussedWindow();
            if(hItem==hWin_v[0])
            {
            WM_DeleteWindow(pMsg->hWin);
            Tongdao();
            }
        }
        WM_DefaultProc(pMsg);
        break;
  }
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
WM_HWIN Tongdao15(void);
WM_HWIN Tongdao15(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
