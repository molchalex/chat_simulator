#include "Server.h"
#include "ServerUser.h"

Server::Server(const QHostAddress& iHost, int iPort)
  : _host(iHost)
  , _port(iPort)
{
  _pTcpServer = new QTcpServer(this);
  connect(_pTcpServer, SIGNAL(newConnection()), this, SLOT(newUser()));
  connect(_pTcpServer, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(serverError(QAbstractSocket::SocketError)));
}

void Server::start()
{
  if (_pTcpServer->isListening())
    printLog(QString("Already listening"));
  else if (_pTcpServer->listen(_host, _port))
  {
    printLog(QString("Success starting"));
  }
  else
    printLog(QString("Unable to start server: %1").arg(_pTcpServer->errorString()));
}

void Server::stop()
{
  if (!_pTcpServer->isListening())
    return;

  _users.clear();
  _pTcpServer->close();

  printLog("Success stopping");
}

void Server::newUser()
{
  QTcpSocket* pSocket = _pTcpServer->nextPendingConnection();
  if (!pSocket)
    return;

  // create server side user
  auto* pServerUser = new ServerUser(pSocket, this);
  connect(pServerUser, SIGNAL(sendMessage(QString)), this, SLOT(sendMessage(QString)));
  connect(pServerUser, SIGNAL(disconnected()), this, SLOT(removeUser()));
  _users.push_back(pServerUser);
}

void Server::removeUser()
{
  // remove user
  auto* pSender = dynamic_cast<ServerUser*>(sender());
  _users.removeOne(pSender);
}

void Server::sendMessage(const QString& iMessage)
{
  // send message to all user (exclude sender)
  auto* pSender = dynamic_cast<ServerUser*>(sender());
  for (ServerUser* pUser : _users)
  {
    if (pUser != pSender)
      pUser->sendToClient(iMessage);
  }
}

void Server::serverError(QAbstractSocket::SocketError iError)
{
  printLog(QString("Server error: %1").arg(_pTcpServer->errorString()));
}