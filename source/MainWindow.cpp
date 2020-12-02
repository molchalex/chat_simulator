#include "MainWindow.h"

#include "ClientSide/UserWidget.h"
#include "ClientSide/UserController.h"

#include "ServerSide/Server.h"

#include <QStringListModel>

MainWindow::MainWindow(Server* ipServer, UserController* ipUserController)
{
  setupUi(this);

  // connect server
  connect(startButton, SIGNAL(clicked()), ipServer, SLOT(start()));
  connect(stopButton, SIGNAL(clicked()), ipServer, SLOT(stop()));
  connect(ipServer, SIGNAL(printLog(QString)), this, SLOT(printLog(QString)));

  // connect add new user button 
  connect(addButton, SIGNAL(clicked()), this, SLOT(onAddButtonClicked()));

  // connect user controller
  connect(this, SIGNAL(newUser(QString)), ipUserController, SLOT(addUser(QString)));
  connect(ipUserController, SIGNAL(userAdded(User*)), this, SLOT(addUserWidget(User*)));

  _serverLog = new QStringListModel(this);
  logMessagesView->setModel(_serverLog);
}

void MainWindow::addUserWidget(User* ipUser)
{
  // create chat widget
  const auto pUserWidget = new UserWidget(ipUser, this);
  mdiArea->addSubWindow(pUserWidget);
  pUserWidget->show();
}

void MainWindow::onAddButtonClicked()
{
  // generate next user name
  static int userCounter = 0;
  const QString defaultUserName = QString("User_%1").arg(userCounter++);
  QString userName = QInputDialog::getText(this, "User name", "Enter new user name", QLineEdit::Normal, defaultUserName);
  if (!userName.isEmpty())
    emit newUser(userName);
}

void MainWindow::printLog(const QString& iMessage) const
{
  _serverLog->insertRow(_serverLog->rowCount());

  const QModelIndex index = _serverLog->index(_serverLog->rowCount() - 1);
  _serverLog->setData(index, iMessage);
}