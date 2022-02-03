#ifndef _qdconfig_h_
#define _qdconfig_h_

#include <string>
#include <map>
#include <utilfuncs/utilfuncs.h>

/*
	'cfgfile' - uses default <app-name>.config if not specified, see source for SetConfigFile()
	Keys & Values:	uses (unicode) strings(no newlines or '='), and numbers(ints/decimals)
	(see: test_qdconfig.cpp for usage-samples)
*/

struct QDConfig
{
	std::string CfgFile;
	MSTR mkv; //template in utilfuncs
	bool bQuiet{true}; //'false' used for debugging)
	
	void clear()												{ CfgFile.clear(); mkv.clear(); }
	void clean()												{ mkv.clear(); }

	~QDConfig()													{ clear(); }
	QDConfig(const std::string &cfgfile="", bool bquiet=true); //uses default_output_path() in utilfuncs
	 
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
