#pragma once

#include <QObject>
#include <QList>
#include <QHostAddress>

class User;

// UserController class
// manages client classes
class UserController: public QObject
{
  Q_OBJECT
public:
  UserController(const QHostAddress& iHost, int iPort);

public slots:
  void addUser(const QString& iUserName);
  void deleteUser(User* ipUser);

Q_SIGNALS:
  void userAdded(User*);
  void userDeleted(User*);

private:
  QHostAddress _host;
  int _port;

  QList<User*> _users;
};
