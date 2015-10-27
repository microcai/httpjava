
#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include "javahttp.hpp"

static boost::asio::io_service m_io_service;
static boost::asio::io_service::work m_io_work(m_io_service);
static boost::thread io_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &m_io_service));

std::string javahttp::post(std::string url, std::string token, std::string id, int pos, int count, std::string filename)
{

}
