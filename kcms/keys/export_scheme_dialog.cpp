/**
 * Copyright (C) 2009 Michael Jansen <kde@michael-jansen.biz>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "export_scheme_dialog.h"

#include <QCheckBox>
#include <KLocalizedString>
#include <KConfigGroup>
#include <QDialogButtonBox>
#include <QPushButton>


ExportSchemeDialog::ExportSchemeDialog(QStringList components, QWidget *parent)
    :   QDialog(parent),
      ui(),
      mComponents(components)
{
    QWidget *w = new QWidget(this);
    ui.setupUi(w);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(w);

    // We allow to check more than one button
    mButtons.setExclusive(false);

    // A grid layout for the buttons
    QGridLayout *vb = new QGridLayout(this);

    int item=0;
    Q_FOREACH(QString component, mComponents)
    {
        QCheckBox *cb = new QCheckBox(component);
        vb->addWidget(cb, item / 2, item % 2);
        mButtons.addButton(cb, item);
        ++item;
    }

    ui.components->setLayout(vb);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);
}


ExportSchemeDialog::~ExportSchemeDialog()
{}


QStringList ExportSchemeDialog::selectedComponents() const
{
    QStringList rc;
    Q_FOREACH(QAbstractButton const *button, mButtons.buttons())
    {
        if (button->isChecked())
        {
            // Remove the '&' added by KAcceleratorManager magically
            rc.append(KLocalizedString::removeAcceleratorMarker(button->text()));
        }
    }
    return rc;
}


#include "moc_export_scheme_dialog.cpp"
