
#include <string>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <avhttp.hpp>

#include "javahttp.hpp"


static boost::asio::io_service m_io_service;
static boost::asio::io_service::work m_io_work(m_io_service);
static boost::thread io_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &m_io_service));

std::string javahttp::post(std::string url, std::string token, std::string id, std::string filename)
{
	boost::system::error_code ec;
	uint64_t fsize = boost::filesystem::file_size(filename);

	if (fsize < 8*1024*1024)
	{
		avhttp::file_upload::form_args fields;
		avhttp::file_upload file_upload(m_io_service);

		std::string constructed_url = boost::str(boost::format("http://v.wanin.net/api/file/uploadFile?user_token=%s&id=%s&pos=%d&count=%d") % token % id % 0 % fsize);

		fields["user_token"] = token;
		fields["id"] = id;
		fields["pos"] = "0";
		fields["count"] = boost::str(boost::format("%d") % fsize);

		file_upload.open(constructed_url, filename, "file", fields);


		// 开始上传文件数据.
		avhttp::default_storge file;
		file.open(filename, ec);

		boost::array<char, 4096> buffer;
		while (!file.eof())
		{
			int readed = file.read(buffer.data(), 4096);
			boost::asio::write(file_upload, boost::asio::buffer(buffer, readed), ec);

		}
		file_upload.write_tail();

		avhttp::http_stream& s = file_upload.get_http_stream();

		int readed = s.read_some(boost::asio::buffer(buffer, 4096));

		return std::string(buffer.data(), readed);
	}

	// 拆分进行
	for (int pos = 0; pos < fsize; pos += 4096)
	{
		avhttp::file_upload::form_args fields;
		avhttp::file_upload file_upload(m_io_service);

		std::string constructed_url = boost::str(boost::format("http://v.wanin.net/api/file/uploadFile?user_token=%s&id=%s&pos=%d&count=%d") % token % id % 0 % fsize);

		fields["user_token"] = token;
		fields["id"] = id;
		fields["pos"] = boost::str(boost::format("%d") % pos);
		int count = 4096;

		if (pos + count >= fsize)
		{
			count = fsize - pos;
		}

		fields["count"] = boost::str(boost::format("%d") % count);

		file_upload.open(constructed_url, filename, "file", fields);


		// 开始上传文件数据.
		avhttp::default_storge file;
		file.open(filename, ec);

		boost::array<char, 4096> buffer;


		int readed = file.read(buffer.data(), pos, count);
		boost::asio::write(file_upload, boost::asio::buffer(buffer, readed), ec);


		file_upload.write_tail();

		avhttp::http_stream& s = file_upload.get_http_stream();

		readed = s.read_some(boost::asio::buffer(buffer, 4096));

		std::string(buffer.data(), readed);
	}

	return "{ id : \"0\", result : 0}";
}
