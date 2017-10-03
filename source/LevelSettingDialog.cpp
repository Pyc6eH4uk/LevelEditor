//
// Created by gdhsnlvr on 03.07.17.
//

#include <QtGui/QIntValidator>
#include "LevelSettingDialog.h"

LevelSettingDialog::LevelSettingDialog() {
    m_formLayout = new QFormLayout();
    m_widthLineEdit = new QLineEdit();
    m_widthLineEdit->setValidator(new QIntValidator(1, 1024, this));
    m_heightLineEdit = new QLineEdit();
    m_heightLineEdit->setValidator(new QIntValidator(1, 1024, this));

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                       Qt::Horizontal, this);

    m_formLayout->addRow("Width", m_widthLineEdit);
    m_formLayout->addRow("Height", m_heightLineEdit);
    m_formLayout->addRow(m_buttonBox);

    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    setLayout(m_formLayout);
}

int LevelSettingDialog::width() {
    return m_widthLineEdit->text().toInt();
}

int LevelSettingDialog::height() {
    return m_heightLineEdit->text().toInt();
}
