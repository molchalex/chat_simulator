#include "UserWidget.h"
#include "User.h"
#include "MessageGenerator.h"

#include <QStringListModel>

UserWidget::UserWidget(User* ipUser, QWidget* ipParent)
  : QWidget(ipParent)
  , _pUser(ipUser)
  , _pMessageGenerator(nullptr)
{
  setupUi(this);
  setWindowTitle(_pUser->getUserName());

  _messages = new QStringListModel(this);
  messagesView->setModel(_messages);

  connect(_pUser, SIGNAL(sendToChat(QString)), this, SLOT(printMessage(QString)));

  // create and start message generator
  _pMessageGenerator = new MessageGenerator(messageEdit, nullptr);
  connect(_pMessageGenerator, SIGNAL(messageFinished(QString)), _pUser, SLOT(sendToServer(QString)));
  _pMessageGenerator->start();
}

void UserWidget::printMessage(const QString& iMessage) const
{
  _messages->insertRow(_messages->rowCount());

  const QModelIndex index = _messages->index(_messages->rowCount() - 1);
  _messages->setData(index, iMessage);
}

UserWidget::~UserWidget()
{
  if (_pMessageGenerator)
    _pMessageGenerator->terminate();
  delete _pMessageGenerator;

  _pUser->disconnectFromServer();
}