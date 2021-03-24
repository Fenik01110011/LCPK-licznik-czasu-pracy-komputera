object Form1: TForm1
  Left = 289
  Top = 131
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'LCPK'
  ClientHeight = 421
  ClientWidth = 499
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDefault
  OnActivate = FormActivate
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Czas1: TLabel
    Left = 50
    Top = 85
    Width = 400
    Height = 37
    Alignment = taCenter
    AutoSize = False
    Caption = '00:00:00'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Napis1: TLabel
    Left = 20
    Top = 55
    Width = 460
    Height = 29
    Alignment = taCenter
    AutoSize = False
    Caption = 'Czas pracy programu'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Czas2: TLabel
    Left = 50
    Top = 205
    Width = 400
    Height = 37
    Alignment = taCenter
    AutoSize = False
    Caption = '00:00:00'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Napis2: TLabel
    Left = 20
    Top = 175
    Width = 460
    Height = 29
    Alignment = taCenter
    AutoSize = False
    Caption = 'Ca'#322'kowity czas'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Czas3: TLabel
    Left = 50
    Top = 325
    Width = 400
    Height = 37
    Alignment = taCenter
    AutoSize = False
    Caption = '00:00:00'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Napis3: TLabel
    Left = 75
    Top = 265
    Width = 350
    Height = 58
    Alignment = taCenter
    AutoSize = False
    Caption = 'Czas pracy programu od 11.11.2017r. 23:50:00'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = True
    WordWrap = True
  end
  object Zegar: TTimer
    OnTimer = ZegarTimer
    Left = 8
    Top = 16
  end
  object MainMenu1: TMainMenu
    Left = 72
    Top = 16
    object Opcje1: TMenuItem
      Caption = 'Opcje'
      object Zapiszczas1: TMenuItem
        Caption = 'Zapisz czas'
        OnClick = Zapiszczas1Click
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Czstotliwo1: TMenuItem
        Caption = 'Zapisuj co:'
        object minuty1: TMenuItem
          Caption = '1 minute'
          OnClick = minuty1Click
        end
        object minuty2: TMenuItem
          Caption = '2 minuty'
          OnClick = minuty2Click
        end
        object minuty5: TMenuItem
          Caption = '5 minut'
          OnClick = minuty5Click
        end
        object minuty10: TMenuItem
          Caption = '10 minut'
          OnClick = minuty10Click
        end
        object minuty15: TMenuItem
          Caption = '15 minut'
          OnClick = minuty15Click
        end
        object minuty30: TMenuItem
          Caption = '30 minut'
          OnClick = minuty30Click
        end
        object minuty60: TMenuItem
          Caption = '1 godzine'
          OnClick = minuty60Click
        end
      end
      object Widoczno1: TMenuItem
        Caption = 'Widoczno'#347#263
        object Minimalizuj1: TMenuItem
          Caption = 'Minimalizuj'
          Visible = False
        end
        object Minimalizujdotreya1: TMenuItem
          Caption = 'Minimalizuj do treya'
          OnClick = Minimalizujdotreya1Click
        end
        object Trybninja1: TMenuItem
          Caption = 'Tryb ninja'
          OnClick = Trybninja1Click
        end
      end
      object Widok1: TMenuItem
        Caption = 'Pokazuj'
        object Aktualnyczas1: TMenuItem
          Caption = 'Aktualny czas pracy'
          OnClick = Aktualnyczas1Click
        end
        object Calkowityczaspracy1: TMenuItem
          Caption = 'Ca'#322'kowity czas pracy'
          OnClick = Calkowityczaspracy1Click
        end
        object Czaspracyoddaty1: TMenuItem
          Caption = 'Czas pracy od daty'
          object Pokazdate1: TMenuItem
            Caption = 'Poka'#380' date'
            OnClick = Pokazdate1Click
          end
          object Dataigodzina1: TMenuItem
            Caption = 'Poka'#380' date i godzine'
            OnClick = Dataigodzina1Click
          end
          object Niepokazujdaty1: TMenuItem
            Caption = 'Nie pokazuj daty'
            OnClick = Niepokazujdaty1Click
          end
          object N1: TMenuItem
            Caption = '-'
          end
          object Ustawdate1: TMenuItem
            Caption = 'Ustaw date'
            OnClick = Ustawdate1Click
          end
        end
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object Zmiehaso1: TMenuItem
        Caption = 'Zmie'#324' has'#322'o'
        OnClick = Zmiehaso1Click
      end
      object N6: TMenuItem
        Caption = '-'
      end
      object Narzdzia1: TMenuItem
        Caption = 'Narz'#281'dzia'
        object Zainstalujdoautostartu1: TMenuItem
          Caption = 'Zainstaluj do autostartu'
          OnClick = Zainstalujdoautostartu1Click
        end
        object N5: TMenuItem
          Caption = '-'
        end
        object Odinstalujzautostartu1: TMenuItem
          Caption = 'Odinstaluj z autostartu'
          OnClick = Odinstalujzautostartu1Click
        end
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Zakoncz: TMenuItem
        Caption = 'Zako'#324'cz'
        OnClick = ZakonczClick
      end
    end
    object Aktywno1: TMenuItem
      Caption = 'Aktywno'#347#263
      OnClick = Aktywno1Click
    end
  end
  object TrayIcon1: TTrayIcon
    Hide = True
    RestoreOn = imLeftClickUp
    PopupMenuOn = imNone
    OnClick = TrayIcon1Click
    Left = 40
    Top = 16
  end
end
