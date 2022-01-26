#ifndef _qdconfig_qdconfig_h_
#define _qdconfig_qdconfig_h_

#include <string>
#include <map>
#include <utilfuncs/utilfuncs.h>


struct QDConfig
{
	std::string QDFile;
	MSTR mkv;
	
	~QDConfig();
	QDConfig(const std::string &cfgfile="");
	
	void clear(); //clears all
	void clean(); //only clears kv-data
	void SetConfigFile(const std::string &cfgfile);
	void Set(const std::string &key, const std::string &value);
	std::string Get(const std::string &key);
	bool Has(const std::string &key);
	bool Has(const std::string &key, const std::string &value);
	bool HasValue(const std::string &value);

	bool Save();
	bool Load();
};





#endif
