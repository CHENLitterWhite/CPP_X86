#include "MongooseHttpServer.h"
#include <string>

std::mutex MongooseHttpServer::m_mutex;
MongooseHttpServer* MongooseHttpServer::instance = nullptr;

void MongooseHttpServer::linsten_cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	MongooseHttpServer* pThis = (MongooseHttpServer*)fn_data;
	if (MG_EV_HTTP_MSG == ev)
	{
		do
		{
			struct mg_http_message *hm = (struct mg_http_message *)ev_data;

			std::string uri;
			uri.append(hm->uri.ptr, hm->uri.len);

			if (pThis->hander_map.find(uri) == pThis->hander_map.end())
			{
				mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{%d:%s}", 400, "请求未找到");
				break;
			}

			HttpMessage* message = new HttpMessage;
			// 取出全部的请求参数 key-val
			char* decode = new char[hm->query.len * 2];
			mg_url_decode(hm->query.ptr, hm->query.len, decode, hm->query.len * 2, 1);
			if (hm->query.ptr)
			{
				std::string qu;
				qu.append(hm->query.ptr, hm->query.len);
				// 做切割
				int pos2 = 0;
				int pos1 = 0;
				do
				{
					pos1 = qu.find_first_of('=', pos1);
					if (pos1 != -1)
					{
						// key --> pos2xxxpos1
						std::string key = qu.substr(pos2, pos1 - pos2);

						// val --> pos1+1xxxxpos2
						int pos3 = 0;
						pos2 = qu.find_first_of('&', pos2);
						if (pos2 == -1)
						{
							// key=val
							pos3 = qu.length();
						}
						else
						{
							pos3 = pos2 - 1;
						}
						std::string val = qu.substr(pos1 + 1, pos3 - pos1);

						message->params[key] = val;
						pos1++;
						pos2++;
					}

				} while (pos1 != -1);
			}

			// 取出全部的头部消息
			int index = 0;
			while (index < MG_MAX_HTTP_HEADERS && hm->headers[index].name.ptr != NULL)
			{
				std::string key;
				key.append(hm->headers[index].name.ptr, hm->headers[index].name.len);
				std::string val;
				val.append(hm->headers[index].value.ptr, hm->headers[index].value.len);

				message->headers[key] = val;
				index++;
			}

			// 取出全部的请求体中的消息
			message->body = hm->body.ptr;
			message->bodyLen = hm->body.len;

			// 回调函数
			fn  cbFunc = pThis->hander_map[uri];
			cbFunc(message, NULL);

			// 返回消息
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{%s:%s}", "status", "okk");

			delete message;
			delete[]decode;

		} while (false);

	}

	(void)fn_data;
}

MongooseHttpServer::MongooseHttpServer():c(NULL), m_stop(false)
{

}

MongooseHttpServer::~MongooseHttpServer()
{

}

MongooseHttpServer* MongooseHttpServer::GetInstance()
{

	if (!instance)
	{
		m_mutex.lock();
		if (!instance)
		{
			instance = new MongooseHttpServer();
		}
		m_mutex.unlock();
	}

	return instance;
}

void MongooseHttpServer::Start(const char* listenAddr)
{

	// 设置日志级别
	mg_log_set(MG_LL_INFO);

	mg_mgr_init(&mgr);
	c = mg_http_listen(&mgr, listenAddr, linsten_cb, this);
	if (NULL == c)
	{
		MG_ERROR(("Cannot listen on %s. Use http://ADDR:PORT or :PORT", listenAddr));
		exit(EXIT_FAILURE);
	}

	while (!m_stop)
	{
		mg_mgr_poll(&mgr, 1000);
	}

	mg_mgr_free(&mgr);

	return;
}


void MongooseHttpServer::Stop()
{
	m_stop.exchange(true);

	return;
}

void MongooseHttpServer::SetListenAddr(std::string uri, fn hander)
{
	hander_map[uri] = *hander;

	return;
}

bool MongooseHttpServer::AddPostUrl()
{
	return true;
}

bool MongooseHttpServer::AddGetUrl()
{
	return true;
}

bool MongooseHttpServer::AddPostFile()
{
	return true;
}