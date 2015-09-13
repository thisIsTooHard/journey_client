/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright © 2015 SYJourney                                               //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#include "session.h"

namespace net
{
	int session::reconnect(vector<byte> addr, short port)
	{
		close();

		string addrstr;
		for (size_t i = 0; i < 4; i++)
		{
			addrstr.append(to_string(addr[i]));
			if (i < 3)
			{
				addrstr.push_back('.');
			}
		}

		string portstr = to_string(port);

		return init(addrstr.c_str(), portstr.c_str(), true);
	}

	int session::init()
	{
		return init(host.c_str(), loginport.c_str(), false);
	}

	int session::init(const char* iaddr, const char* port, bool channelserver)
	{
		WSADATA wsa_info;
		sock = INVALID_SOCKET;

		struct addrinfo *addr_info = NULL;
		struct addrinfo *ptr = NULL;
		struct addrinfo hints;

		int result = WSAStartup(MAKEWORD(2, 2), &wsa_info);
		if (result != 0) {
			return -1;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		result = getaddrinfo(iaddr, port, &hints, &addr_info);

		if (result != 0) {
			WSACleanup();
			return -1;
		}

		for (ptr = addr_info; ptr != NULL; ptr = ptr->ai_next) {

			sock = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (sock == INVALID_SOCKET) {
				WSACleanup();
				return -1;
			}

			result = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (result == SOCKET_ERROR) {
				closesocket(sock);
				sock = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(addr_info);

		if (sock == INVALID_SOCKET) {
			WSACleanup();
			return -1;
		}

		char recvbuf[32];
		vector<byte> recviv;
		vector<byte> sendiv;
		byte version;
		byte localisation;

		result = recv(sock, recvbuf, 32, 0);

		if (result > 0)
		{
			packet rcv = packet();
			rcv.writebytes(recvbuf, result);

			rcv.readshort();
			version = static_cast<byte>(rcv.readshort());

			switch (version)
			{
			case 62:
				rcv.readshort();
				sendiv.push_back(rcv.readbyte());
				sendiv.push_back(rcv.readbyte());
				sendiv.push_back(rcv.readbyte());
				sendiv.push_back(rcv.readbyte());
				recviv.push_back(rcv.readbyte());
				recviv.push_back(rcv.readbyte());
				recviv.push_back(rcv.readbyte());
				recviv.push_back(rcv.readbyte());
				localisation = rcv.readbyte();
				break;
			case 83:
				rcv.readshort();
				rcv.readbyte();
				sendiv.push_back(rcv.readbyte());
				sendiv.push_back(rcv.readbyte());
				sendiv.push_back(rcv.readbyte());
				sendiv.push_back(rcv.readbyte());
				recviv.push_back(rcv.readbyte());
				recviv.push_back(rcv.readbyte());
				recviv.push_back(rcv.readbyte());
				recviv.push_back(rcv.readbyte());
				localisation = rcv.readbyte();
				break;
			default:
				WSACleanup();
				return -2;
			}
		}
		else
		{
			WSACleanup();
			return -1;
		}

		encrypter.init(recviv, sendiv, version, localisation);

		u_long smode = 1;
		ioctlsocket(sock, FIONBIO, &smode);

		active = true;

		return version;
	}

	int session::dispatch(packet* tosend)
	{
		lock_guard<mutex> lock(sendlock);
		encrypter.sendencrypt(tosend);
		return send(sock, tosend->getbytes(), tosend->length(), 0);
	}

	void session::receive()
	{
		if (active)
		{
			int result = recv(sock, buffer, 10240, 0);

			if (result > 0)
			{
				lock_guard<mutex> lock(recvlock);
				char* bytes = new char[result];
				memcpy(bytes, buffer, result);
				process(bytes, result);
				delete[] bytes;
			}
		}
	}

	void session::process(char* bytes, int result)
	{
		if (bufferpos == 0)
		{
			curp = packet();
			p_length = encrypter.getlength(bytes) + 4;

			int towrite = min(result - 4, p_length - 4);
			encrypter.recvdecrypt(bytes + 4, towrite, (result >= p_length));
			curp.writebytes(bytes + 4, towrite);
		}
		else
		{
			int towrite = min(result, p_length - bufferpos);
			encrypter.recvdecrypt(bytes, towrite, (result + bufferpos >= p_length));
			curp.writebytes(bytes, towrite);
		}

		bufferpos += result;

		if (bufferpos >= p_length)
		{
			handler.process(curp);

			if (bufferpos > p_length)
			{
				bufferpos = 0;
				process(bytes + p_length, result - p_length);
			}
			else
			{
				bufferpos = 0;
			}
		}
	}

	void session::close()
	{
		active = false;
		closesocket(sock);
		WSACleanup();
	}
}