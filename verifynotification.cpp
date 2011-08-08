
#include "verifynotification.h"

VerifyNotification::VerifyNotification(GpgME::Context *ctx, QWidget *parent ) :
    QWidget(parent)
{
    mCtx = ctx;
    verifyLabel = new QLabel(this);

    notificationWidgetLayout = new QHBoxLayout(this);
    notificationWidgetLayout->setContentsMargins(0,0,0,0);
    notificationWidgetLayout->addWidget(verifyLabel,2);

    this->setLayout(notificationWidgetLayout);

    importFromKeyserverAct = new QAction(tr("Import missing key from Keyserver"), this);
    connect(importFromKeyserverAct, SIGNAL(triggered()), this, SLOT(importFromKeyserver()));

    showVerifyDetailsAct = new QAction(tr("Show detailed verify information"), this);
    connect(showVerifyDetailsAct, SIGNAL(triggered()), this, SLOT(showVerifyDetails()));

    detailMenu = new QMenu(this);
    detailMenu->addAction(showVerifyDetailsAct);
    detailMenu->addAction(importFromKeyserverAct);
    importFromKeyserverAct->setVisible(false);
    keysNotInList = new QStringList();
    QPushButton *verifyButton = new QPushButton("Details",this);
    verifyButton->setMenu(detailMenu);
    notificationWidgetLayout->addWidget(verifyButton);

    verifyDetailText = new QString();
}

void VerifyNotification::setVerifyDetailText (QString text)
{
    verifyDetailText->clear();
    verifyDetailText->append(text);
    return;
}

void VerifyNotification::importFromKeyserver()
{
    KeyServerImportDialog *importDialog =new KeyServerImportDialog(mCtx,this);
    foreach (QString keyid, *keysNotInList) {
        importDialog->import(keyid);
    }
}

void VerifyNotification::setVerifyLabel(QString text)
{
    verifyLabel->setText(text);
    return;
}

void VerifyNotification::addImportAction()
{
    importFromKeyserverAct->setVisible(true);
    return;
}
void VerifyNotification::removeImportAction()
{
    importFromKeyserverAct->setVisible(false);
    return;
}

void VerifyNotification::showVerifyDetails()
{
    QMessageBox::information(this,tr("Details"),QString(*verifyDetailText), QMessageBox::Ok);
    return;
}