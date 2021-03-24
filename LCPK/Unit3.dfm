object Form3: TForm3
  Left = 408
  Top = 90
  Width = 570
  Height = 480
  Caption = 'Wykaz aktywno'#347'ci'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Lista_aktywnosci: TMemo
    Left = 0
    Top = 0
    Width = 554
    Height = 421
    Align = alClient
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Consolas'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object MainMenu1: TMainMenu
    Left = 8
    Top = 16
    object Opcje1: TMenuItem
      Caption = 'Opcje'
      object Zmianaczcionki1: TMenuItem
        Caption = 'Zmie'#324' czcionk'#281
        OnClick = Zmianaczcionki1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Usuhistorie1: TMenuItem
        Caption = 'Usu'#324' histori'#281
        object Aktywno2: TMenuItem
          Caption = 'Aktywno'#347'ci'
          OnClick = Aktywno2Click
        end
        object Dziaaniauytkownika2: TMenuItem
          Caption = 'Dzia'#322'a'#324' u'#380'ytkownika'
          OnClick = Dziaaniauytkownika2Click
        end
        object N1: TMenuItem
          Caption = '-'
        end
        object Usucahistio1: TMenuItem
          Caption = 'Usu'#324' ca'#322#261' histori'#281
          OnClick = Usucahistio1Click
        end
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Niezapisujtejaktywnoci1: TMenuItem
        Caption = 'Nie zapisuj tej aktywno'#347'ci'
        OnClick = Niezapisujtejaktywnoci1Click
      end
    end
    object Wy1: TMenuItem
      Caption = 'Wy'#347'wietl'
      object Wykazaktywnoci1: TMenuItem
        Caption = 'Wykaz aktywno'#347'ci'
        OnClick = Wykazaktywnoci1Click
      end
      object Aktywno1: TMenuItem
        Caption = 'Aktywno'#347#263' w przedziale'
        OnClick = Aktywno1Click
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object Dziaaniauytkownika1: TMenuItem
        Caption = 'Dzia'#322'ania u'#380'ytkownika'
        OnClick = Dziaaniauytkownika1Click
      end
    end
  end
  object FontDialog1: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MinFontSize = 0
    MaxFontSize = 0
    Left = 40
    Top = 16
  end
end
