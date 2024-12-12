#pragma once
#ifndef WSAA_H_
#define WSAA_H_

#include <winsock2.h>

struct Wsa
{
	Wsa();
	~Wsa();

private:
	WSADATA m_wsadata;

	Wsa(const Wsa& _copy);
	Wsa& operator=(const Wsa& _assign);

};

#endif // !WSA_H_
