object Form6: TForm6
  Left = 353
  Top = 232
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Ustawianie daty'
  ClientHeight = 188
  ClientWidth = 305
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 24
    Width = 279
    Height = 24
    Caption = 'Pokazuj czas pracy programu od:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 80
    Top = 64
    Width = 23
    Height = 13
    Caption = 'Data'
  end
  object Label6: TLabel
    Left = 184
    Top = 64
    Width = 39
    Height = 13
    Caption = 'Godzina'
  end
  object DateTimePicker1: TDateTimePicker
    Left = 42
    Top = 78
    Width = 105
    Height = 28
    CalAlignment = dtaLeft
    Date = 43101.7083333333
    Time = 43101.7083333333
    DateFormat = dfShort
    DateMode = dmComboBox
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Kind = dtkDate
    MaxDate = 50406
    MinDate = 732
    ParseInput = False
    ParentFont = False
    TabOrder = 0
  end
  object DateTimePicker2: TDateTimePicker
    Left = 161
    Top = 78
    Width = 89
    Height = 28
    CalAlignment = dtaLeft
    Date = 43018
    Time = 43018
    DateFormat = dfShort
    DateMode = dmComboBox
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Kind = dtkTime
    ParseInput = False
    ParentFont = False
    TabOrder = 1
  end
  object Button1: TButton
    Left = 108
    Top = 130
    Width = 75
    Height = 25
    Caption = 'OK'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button1Click
  end
end
