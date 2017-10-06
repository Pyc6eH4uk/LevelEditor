//
// Created by gdhsnlvr on 03.07.17.
//

#include <QtGui/QIntValidator>
#include "LevelSettingDialog.h"

LevelSettingDialog::LevelSettingDialog() {
    m_formLayout = new QFormLayout();
    m_grassLineEdit = new QLineEdit();
    m_grassLineEdit->setValidator(new QIntValidator(1, 1024, this));
    m_relaxLineEdit = new QLineEdit();
    m_relaxLineEdit->setValidator(new QIntValidator(1, 1024, this));
    m_treesLineEdit = new QLineEdit();
    m_treesLineEdit->setValidator(new QIntValidator(1, 1024, this));
    m_starstLineEdit = new QLineEdit();
    m_starstLineEdit->setValidator(new QIntValidator(1, 1024, this));

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                       Qt::Horizontal, this);

    m_formLayout->addRow("grass", m_grassLineEdit);
    m_formLayout->addRow("relax", m_relaxLineEdit);
    m_formLayout->addRow("trees", m_treesLineEdit);
    m_formLayout->addRow("stars", m_starstLineEdit);
    m_formLayout->addRow(m_buttonBox);

    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    setLayout(m_formLayout);
}

int LevelSettingDialog::grass() {
    return m_grassLineEdit->text().toInt();
}

int LevelSettingDialog::relax() {
    return m_relaxLineEdit->text().toInt();
}

int LevelSettingDialog::trees() {
    return m_treesLineEdit->text().toInt();
}

int LevelSettingDialog::stars() {
    return m_starstLineEdit->text().toInt();
}
