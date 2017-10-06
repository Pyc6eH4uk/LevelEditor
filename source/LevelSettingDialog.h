//
// Created by gdhsnlvr on 03.07.17.
//

#ifndef FOALEDITOR_LEVELSETTINGDIALOG_H
#define FOALEDITOR_LEVELSETTINGDIALOG_H


#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFormLayout>

class LevelSettingDialog : public QDialog {
    Q_OBJECT
protected:
    QFormLayout *m_formLayout;
    QLineEdit *m_grassLineEdit;
    QLineEdit *m_relaxLineEdit;
    QLineEdit *m_treesLineEdit;
    QLineEdit *m_starstLineEdit;
    QDialogButtonBox *m_buttonBox;

public:
    LevelSettingDialog();

    int grass();
    int relax();
    int trees();
    int stars();
};


#endif //FOALEDITOR_LEVELSETTINGDIALOG_H
