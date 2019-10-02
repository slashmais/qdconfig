#ifndef _qdconfig_qdconfig_h_
#define _qdconfig_qdconfig_h_

#include <string>
#include <map>


struct QDConfig
{
	std::string QDFile;
	std::string QDPath;
	std::map<std::string, std::string> data;
	
	~QDConfig();
	QDConfig();
	QDConfig(const std::string &qdf);
	
	void setval(const std::string &k, const std::string &v);
	bool hasval(const std::string &v);
	bool haskey(const std::string &k);
	bool haskeyval(const std::string &k, const std::string &v);
	const std::string getval(const std::string &k);

	bool Save();
	bool Load(const std::string &qdf="");
};





#endif
