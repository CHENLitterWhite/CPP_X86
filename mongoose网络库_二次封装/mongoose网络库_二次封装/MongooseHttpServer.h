#pragma once

/*
	�����ͨ��ֻ��һ��,��������ʹ�õ���ģʽ(����ʽ)
	����: �ɷ�С��
*/

#include <mutex>
#include <unordered_map>
#include <string>
#include "mongoose.h"
#include <atomic>

/* ���ÿ�������:�û���Ҫ�����ݽ��� */
/*
	����ͷ - ����/����
	������ - ����/����
*/
struct HttpMessage
{
	std::unordered_map<std::string , std::string> params;	// �洢������� -- ���Ż�(��ָ�������)
	std::unordered_map<std::string, std::string> headers;   // �洢����ͷ�� -- ���Ż�(��ָ�������)
	const char *body;
	size_t bodyLen;
};

typedef void (*fn)(HttpMessage* /*in*/, void* out /*out*/);

class MongooseHttpServer
{
public:

	~MongooseHttpServer();
	static MongooseHttpServer* GetInstance();
	
	void Start(const char* listenAddr);
	void Stop();

	// �󶨶�Ӧ�ڴ�����
	void SetListenAddr(std::string uri, fn hander);

	bool AddPostUrl();
	bool AddGetUrl();
	bool AddPostFile();

private:
	MongooseHttpServer();
	MongooseHttpServer(const MongooseHttpServer&) = delete;
	MongooseHttpServer& operator=(const MongooseHttpServer&) = delete;

	
	static void linsten_cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
private:

	struct mg_mgr mgr;
	struct mg_connection *c;

	std::unordered_map<std::string, fn> hander_map; // (ͨ��������ڿ�ʼʱ��������,���ÿ����̰߳�ȫ����)

	std::atomic<bool>  m_stop ;

	static std::mutex m_mutex;
	static MongooseHttpServer* instance;
};

