#include "UserController.h"

#include "User.h"

#include <quuid.h>

UserController::UserController(const QHostAddress& iHost, int iPort)
  : _host(iHost)
  , _port(iPort)
{
}

void UserController::addUser(const QString& iUserName)
{
  // create new user and connect to server
  User* pUser = new User(iUserName, _host, _port, nullptr);
  _users.push_back(pUser);
  emit userAdded(pUser);

  pUser->connectToServer();
}

void UserController::deleteUser(User* ipUser)
{
  ipUser->disconnectFromServer();
  ipUser->deleteLater();
  _users.removeOne(ipUser);

  emit userDeleted(ipUser);
}