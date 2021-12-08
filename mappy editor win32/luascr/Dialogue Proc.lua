WM_INITDIALOG = 272
WM_COMMAND = 273

CB_RESETCONTENT = 331
CB_ADDSTRING = 323
CB_SELECTSTRING = 333
CB_SETITEMHEIGHT = 339
CB_GETCURSEL = 327

IDOK = 1
IDCANCEL = 2
IDC_TEXT1 = 101
IDC_DROPLIST1 = 102

droplisttext = {
"First line of text",
"Second line of text",
"Third line...",
"Fourth...",
"End of text for drop down list"
}

function DlgProc ()
 hwnd, msg, wParam, lParam = mappy.getDialogueParam ()

-- mappy.msgBox("Dialogue Example", "Vals = "..msg..", "..wParam..", "..lParam, mappy.MMB_OK, mappy.MMB_ICONINFO)

 if msg == WM_COMMAND then
  idc = mappy.andVal (wParam, 65535)

  if idc == 99 then
   mappy.sendDlgItemMessage (IDC_DROPLIST1, CB_RESETCONTENT, 0, 0)
   for i = 1, table.getn(droplisttext) do
    mappy.sendDlgItemMessage (IDC_DROPLIST1, CB_ADDSTRING, 0, droplisttext[i])
   end
   mappy.sendDlgItemMessage (IDC_DROPLIST1, CB_SETITEMHEIGHT, 0, 18)
   mappy.sendDlgItemMessage (IDC_DROPLIST1, CB_SELECTSTRING, -1, droplisttext[1])
--   mappy.msgBox("Dialogue Example", "Set "..table.getn(droplisttext).." strings", mappy.MMB_OK, mappy.MMB_ICONINFO)
  end

  if idc == IDC_BUTTON1 then
    mappy.msgBox("Dialogue Example", "Clicked button 1", mappy.MMB_OK, mappy.MMB_ICONINFO)
  end

  if idc == IDOK then
   listindex = mappy.sendDlgItemMessage (IDC_DROPLIST1, CB_GETCURSEL, 0, 0)
   editstr = mappy.getDlgItemText (IDC_TEXT1)
   mappy.msgBox("Dialogue Example", "Clicked OK, selected '"..droplisttext[listindex+1].."', typed '"..editstr.."'", mappy.MMB_OK, mappy.MMB_ICONINFO)
  end

  if idc == IDCANCEL then
   mappy.msgBox("Dialogue Example", "Clicked Cancel...", mappy.MMB_OK, mappy.MMB_ICONINFO)
  end

 end
end


test, errormsg = pcall( DlgProc )
if not test then
    mappy.msgBox("Error ...", errormsg, mappy.MMB_OK, mappy.MMB_ICONEXCLAMATION)
end

