object frmWait: TfrmWait
  Left = 807
  Top = 108
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Getting Request'
  ClientHeight = 29
  ClientWidth = 181
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    0000000080000080000000808000800000008000800080800000C0C0C0008080
    80000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000000000000000000000000000003366000000000000000000
    0000000033333366000000000000000000000000000000000000000000000000
    0000000033333366000000000000000000000000000000000000000000000000
    0000000033333366000000000000000000000000033336600000000000000000
    00000000000000000000000000000000000000000F7777F00000000000000000
    00000000FF7777FF000000000000000000000000FF7777FF0000000000000000
    0000000FFF7777FFF0000000000000000000000FFF7777FFF000000000000000
    000000FFF777777FFF00000000000000000000FFB70BB07BFF00000000000000
    00000FFBFB0BB0FBFFF000000000000000000FBFBB0BB0BFBFF0000000000000
    0000FBFBB0BBBB0BFBFF0000000000000000FFBB0BBBBBB0BFBF000000000000
    000FFBFB0BBBBBB0BBFBF00000000000000FBFBBEEEEEEEEBFBFF00000000000
    000FFBFBBBBBBBBBBBFBF00000000000000FBFBFBBBBBBBBBFBFF00000000000
    000FFBFBFBBBBBBBFBFBF000000000000000FFBFBFBFBFBFBFBF000000000000
    0000FFFBFBFBFBFBFBFF00000000000000000FFFBFBFBFBFFFF0000000000000
    00000FFFFFFFFFFFFFF00000000000000000000FFFFFFFFFF000000000000000
    000000000FFFFFF000000000000000000000000000000000000000000000FFFC
    3FFFFFF00FFFFFE007FFFFF00FFFFFE007FFFFF00FFFFFE007FFFFF00FFFFFF0
    0FFFFFF00FFFFFE007FFFFE007FFFFC003FFFFC003FFFF8001FFFF8001FFFF00
    00FFFF0000FFFE00007FFE00007FFC00003FFC00003FFC00003FFC00003FFC00
    003FFE00007FFE00007FFF0000FFFF0000FFFF8001FFFFE007FFFFF81FFF}
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lb_Info: TLabel
    Left = 8
    Top = 8
    Width = 147
    Height = 13
    Caption = 'Please wait...requesting server.'
  end
  object lb_response: TLabel
    Left = 8
    Top = 16
    Width = 43
    Height = 13
    Caption = 'response'
    Visible = False
  end
  object Timer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = TimerTimer
    Left = 152
    Top = 2
  end
end