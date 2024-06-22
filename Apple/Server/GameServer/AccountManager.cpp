#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

void AccountManager::ProcessLogin()
{
	// account lock
	lock_guard<mutex> guard(_mutex);

	// user lock
	User* user = UserManager::Instance()->GetUser(100);

	// todo
}
