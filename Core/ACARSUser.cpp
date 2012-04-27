#include "ACARSUser.h"


ACARSUser::ACARSUser(QString pUsername, QString pUserSession)
    : mUsername(pUsername),
      mUserSession(pUserSession)
{
}


QString ACARSUser::getUsername()
{
    return mUsername;
}
