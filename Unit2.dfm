object SettingsForm: TSettingsForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'SettingsForm'
  ClientHeight = 192
  ClientWidth = 352
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = FormShow
  TextHeight = 15
  object CountryLabel: TLabel
    Left = 60
    Top = 16
    Width = 41
    Height = 15
    Caption = #1057#1090#1088#1072#1085#1072':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object CountryNote: TLabel
    Left = 8
    Top = 136
    Width = 334
    Height = 45
    Caption = 
      #1054#1073#1088#1072#1090#1080#1090#1077' '#1074#1085#1080#1084#1072#1085#1080#1077', '#1095#1090#1086' '#1074#1085#1077' '#1079#1072#1074#1080#1089#1080#1084#1086#1089#1090#1080' '#1086#1090' '#1074#1099#1073#1088#1072#1085#1085#1086#1081' '#1089#1090#1088#1072#1085#1099', '#1089#1072#1081#1090 +
      ' '#1074' '#1087#1088#1086#1075#1088#1072#1084#1084#1077' '#1073#1091#1076#1077#1090' '#1086#1090#1086#1073#1088#1072#1078#1072#1090#1100#1089#1103' '#1085#1072' '#1088#1091#1089#1089#1082#1086#1084' '#1103#1079#1099#1082#1077', '#1101#1090#1086' '#1085#1077#1086#1073#1093#1086#1076#1080#1084#1086 +
      ' '#1076#1083#1103' '#1082#1086#1088#1088#1077#1082#1090#1085#1086#1081' '#1088#1072#1073#1086#1090#1099' '#1087#1088#1086#1075#1088#1072#1084#1084#1099'.'
    WordWrap = True
  end
  object CBox: TComboBox
    Left = 107
    Top = 8
    Width = 184
    Height = 23
    ItemIndex = 0
    TabOrder = 0
    Text = #1056#1086#1089#1089#1080#1103' (hh.ru)'
    Items.Strings = (
      #1056#1086#1089#1089#1080#1103' (hh.ru)'
      #1050#1072#1079#1072#1093#1089#1090#1072#1085' (hh.kz)'
      #1041#1077#1083#1072#1088#1091#1089#1100' (rabota.by)'
      #1059#1079#1073#1077#1082#1080#1089#1090#1072#1085' (hh.uz)'
      #1040#1079#1077#1088#1073#1072#1081#1076#1078#1072#1085' (hh1.az)'
      #1043#1088#1091#1079#1080#1103' (headhunter.ge)'
      #1050#1099#1088#1075#1099#1079#1089#1090#1072#1085' (headhunter.kg)')
  end
  object AutorunBox: TCheckBox
    Left = 57
    Top = 37
    Width = 236
    Height = 17
    Alignment = taLeftJustify
    Caption = #1047#1072#1087#1091#1089#1082#1072#1090#1100' '#1087#1088#1080' '#1089#1090#1072#1088#1090#1077' '#1089#1080#1089#1090#1077#1084#1099
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
  end
  object MinimizeBox: TCheckBox
    Left = 57
    Top = 60
    Width = 236
    Height = 17
    Alignment = taLeftJustify
    Caption = #1057#1074#1086#1088#1072#1095#1080#1074#1072#1090#1100' '#1074' '#1090#1088#1077#1081' '#1087#1088#1080' '#1079#1072#1087#1091#1089#1082#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
  end
  object SaveButton: TButton
    Left = 88
    Top = 96
    Width = 177
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 3
    OnClick = SaveButtonClick
  end
end
