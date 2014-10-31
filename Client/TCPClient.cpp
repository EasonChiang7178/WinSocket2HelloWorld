#include "TCPClient.h"


TCPClient::TCPClient(void)
{
}

TCPClient::TCPClient(string IP, int Port){

	isConnected = false;

	struct sockaddr_in Server_Sock;
	//char IP_Server[32];
	WSADATA data;
	WSAStartup(MAKEWORD(2,0), &data);

	memset(&Server_Sock,0,sizeof(Server_Sock));
	Server_Sock.sin_port = htons(Port);
	Server_Sock.sin_family = AF_INET;
	//sprintf_s( (char *)IP_Server,32,"%s",IP); //problem
	Server_Sock.sin_addr.s_addr = inet_addr(IP.c_str());

	Server_Socket = socket(AF_INET, SOCK_STREAM, 0);

	if(!connect(Server_Socket, (struct sockaddr *) &Server_Sock, sizeof(Server_Sock))){
		cout<<"CONNECTED"<<endl;
		isConnected = true;
	}
	else{
		cout << "CONNECT FAILED!" << endl;
		isConnected = false;
	}

}

void TCPClient::Set(string IP, int Port){
	isConnected = false;

	struct sockaddr_in Server_Sock;
	//char IP_Server[32];
	WSADATA data;
	WSAStartup(MAKEWORD(2,0), &data);

	memset(&Server_Sock,0,sizeof(Server_Sock));
	Server_Sock.sin_port = htons(Port);
	Server_Sock.sin_family = AF_INET;
	//sprintf_s( (char *)IP_Server,32,"%s",IP);
	//Server_Sock.sin_addr.s_addr = inet_addr(IP_Server);
	Server_Sock.sin_addr.s_addr = inet_addr(IP.c_str());

	Server_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if(!connect(Server_Socket, (struct sockaddr *) &Server_Sock, sizeof(Server_Sock))){
		cout<<"CONNECTED"<<endl;
		isConnected = true;
	}
	else{
		cout << IP << " " << Port << endl;
		cout << "CONNECT FAILED!" << endl;
		isConnected = false;
	}
}


void TCPClient::Sending(vector<humans*> infos){

	
	int length;
	char *SendCommand;
	int size= 255;
	SendCommand = new char[size];

	for(int i=0; i < (signed)infos.size() ; i++){

		//cout << (*infos[i]).Bottomright_x - (*infos[i]).Upleft_x << " " << (*infos[i]).Bottomright_y - (*infos[i]).Upleft_y << endl;

		//Box‚Ì‘å‚«‚³‚ÅÀ‚Á‚½‚©‚Ç‚¤‚©‚ð”»’f‚·‚é
		//if((*infos[i]).Bottomright_x - (*infos[i]).Upleft_x > 80 || (*infos[i]).Bottomright_y - (*infos[i]).Upleft_y > 806){
			length = Make_Command(SendCommand,size,*infos[i]);
			send(Server_Socket,SendCommand,length,0);
			cout << "Sending ... " << SendCommand << endl;
		//}
	}
	
}


int TCPClient::Make_Command(char* Command,int _size, humans obj){
	string Header = "OKAO";
	string space = " ";
	string Footer = "\n";
	string Text;

	char tmp_ID[10];
	char tmp_posX[10];
	char tmp_posY[10];
	char tmp_updown[10];
	char tmp_leftright[10];
	char tmp_roll[10];	
	char tmp_age[10];
	char tmp_smile[10];

	sprintf_s(tmp_ID,"%d", obj.id);
	string ID_str = tmp_ID;
	sprintf_s(tmp_posX,"%d", obj.posX);
	string posX_str = tmp_posX;
	sprintf_s(tmp_posY,"%d", obj.posY);
	string posY_str = tmp_posY;
	sprintf_s(tmp_updown,"%d", obj.updown);
	string updown_str = tmp_updown;
	sprintf_s(tmp_leftright,"%d", obj.leftright);
	string leftright_str = tmp_leftright;
	sprintf_s(tmp_roll,"%d", obj.roll);
	string roll_str = tmp_roll;
	sprintf_s(tmp_age,"%d", obj.age);
	string age_str = tmp_age;
	sprintf_s(tmp_smile,"%d", obj.smile);
	string smile_str = tmp_smile;
	Text = Header;

	//Text += index + "  + _Values[i] + " " +  priority + slot;
	Text += space + ID_str + space +posX_str+ space + posY_str + space + updown_str +space + leftright_str +space + roll_str + space+ age_str + space+ smile_str;
	//Text += space + ID_str + space +posX_str+ space + posY_str + space+ smile_str;
	Text += Footer;
	int Len = Text.length();

	char* tmp;
	tmp = (char *)Text.c_str();
	strcpy_s(Command,_size ,tmp);

	return Len;
}
