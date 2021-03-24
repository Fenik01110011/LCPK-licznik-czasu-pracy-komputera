object Form4: TForm4
  Left = 510
  Top = 188
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Aktywno'#347#263' w przedziale'
  ClientHeight = 246
  ClientWidth = 353
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
    Top = 16
    Width = 321
    Height = 24
    Caption = 'Czas pracy programu w przedziale od:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 168
    Top = 104
    Width = 27
    Height = 24
    Caption = 'do:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 104
    Top = 48
    Width = 23
    Height = 13
    Caption = 'Data'
  end
  object Label4: TLabel
    Left = 104
    Top = 128
    Width = 23
    Height = 13
    Caption = 'Data'
  end
  object Label5: TLabel
    Left = 208
    Top = 128
    Width = 39
    Height = 13
    Caption = 'Godzina'
  end
  object Label6: TLabel
    Left = 208
    Top = 48
    Width = 39
    Height = 13
    Caption = 'Godzina'
  end
  object Button1: TButton
    Left = 140
    Top = 194
    Width = 75
    Height = 25
    Caption = 'OK'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object DateTimePicker1: TDateTimePicker
    Left = 66
    Top = 62
    Width = 105
    Height = 28
    CalAlignment = dtaLeft
    Date = 43050
    Time = 43050
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
    TabOrder = 1
  end
  object DateTimePicker2: TDateTimePicker
    Left = 185
    Top = 62
    Width = 89
    Height = 28
    CalAlignment = dtaLeft
    Date = 25569
    Time = 25569
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
    TabOrder = 2
  end
  object DateTimePicker3: TDateTimePicker
    Left = 66
    Top = 140
    Width = 105
    Height = 28
    CalAlignment = dtaLeft
    Date = 43101
    Time = 43101
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
    TabOrder = 3
  end
  object DateTimePicker4: TDateTimePicker
    Left = 185
    Top = 140
    Width = 89
    Height = 28
    CalAlignment = dtaLeft
    Date = 25569
    Time = 25569
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
    TabOrder = 4
  end
end
