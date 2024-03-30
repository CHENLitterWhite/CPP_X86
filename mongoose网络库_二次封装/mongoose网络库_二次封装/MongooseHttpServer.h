#pragma once

/*
	服务端通常只有一个,所以这里使用单例模式(懒汉式)
	作者: 干饭小白
*/

#include <mutex>
#include <unordered_map>
#include <string>
#include "mongoose.h"
#include <atomic>

/* 不用考虑隐藏:用户需要对数据解析 */
/*
	请求头 - 长度/数据
	请求体 - 长度/数据
*/
struct HttpMessage
{
	std::unordered_map<std::string , std::string> params;	// 存储请求参数 -- 待优化(存指针更合理)
	std::unordered_map<std::string, std::string> headers;   // 存储请求头部 -- 待优化(存指针更合理)
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

	// 绑定对应在处理方法
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

	std::unordered_map<std::string, fn> hander_map; // (通常情况下在开始时就设计完毕,不用考虑线程安全问题)

	std::atomic<bool>  m_stop ;

	static std::mutex m_mutex;
	static MongooseHttpServer* instance;
};

