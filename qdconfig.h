#ifndef _qdconfig_qdconfig_h_
#define _qdconfig_qdconfig_h_

#include <string>
#include <map>
#include <utilfuncs/utilfuncs.h>

/*
	Default: Uses [app-name].config as file-name, and either create
			 the file in same location as app or in home-dir;
	If 'cfgfile' is not full path, it will be created as per default;
	Key & Value types must be POD
*/
struct QDConfig
{
	std::string QDFile;
	MSTR mkv;
	bool bQuiet{true};
	
	void clear()												{ QDFile.clear(); mkv.clear(); }
	void clean()												{ mkv.clear(); }

	~QDConfig()													{ clear(); }
	QDConfig(const std::string &cfgfile="", bool bquiet=true); //set bquiet=false to debug your stuff
	 
	void SetConfigFile(const std::string &cfgfile, bool bLoad=false);
	void Set(const std::string &key, const std::string &value);
	template<typename K, typename V> void Set(K k, V v)			{ std::string sk, sv; sayss(sk,k); sayss(sv,v); Set(sk, sv); }
	inline std::string Get(const std::string &key)				{ return mkv.Get(key); }
	inline bool Has(const std::string &key)						{ return (!Get(key).empty()); }
	size_t GetKeys(VSTR &v);

	bool Save();
	bool Load();
};





#endif
