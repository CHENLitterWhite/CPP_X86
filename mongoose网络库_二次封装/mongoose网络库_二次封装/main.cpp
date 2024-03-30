#include "MongooseHttpServer.h"
#include <Windows.h>

const char* url = "http://0.0.0.0:8000";

static void testCb(HttpMessage* message, void* out)
{
	
	printf("-----------头部------------\n");
	for (auto it = message->headers.begin(); it != message->headers.end(); ++it)
	{
		printf("%s:%s\n", it->first.c_str(), it->second.c_str());
	}
	printf("--------------------------\n");

	printf("-----------请求参数-----------\n");
	for (auto it = message->params.begin(); it != message->params.end(); ++it)
	{
		printf("%s:%s\n", it->first.c_str(), it->second.c_str());
	}
	printf("--------------------------\n");

	printf("-----------请求体-----------\n");
	char* body = new char[message->bodyLen];
	printf("%s\n", body);



	delete[]body;

	return;
}

int main()
{
	fn p = testCb;
	MongooseHttpServer::GetInstance()->SetListenAddr("/test/1111", p);
	MongooseHttpServer::GetInstance()->Start(url);
	
	return 0;
}
