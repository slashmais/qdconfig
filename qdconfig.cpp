
#include "qdconfig.h"

QDConfig::QDConfig(const std::string &cfgfile, bool bquiet)	{ clear(); bQuiet=bquiet; SetConfigFile(cfgfile, true); }

void QDConfig::SetConfigFile(const std::string &cfgfile, bool bLoad)
{
	std::string sp{}, sf{};
	sf=path_name(cfgfile);
	sp=path_path(cfgfile);
	if (sp.empty()||!canwrite(sp)) default_output_path(sp);
	if (sf.empty()) sf=says(path_name(thisapp()), ".config");
	CfgFile=path_append(sp, sf);
	//if (!cfgfile.empty()&&!seqs(CfgFile, cfgfile))
		if (!bQuiet) say("\nConfig located at '", CfgFile, "'\n");
	if (bLoad&&file_exist(CfgFile)) Load();
}

void QDConfig::Set(const std::string &key, const std::string &value)
{
	std::string k{key};
	std::string v{value};
	TRIM(k); if (k.empty()) { if (!bQuiet) sayfail("cannot define blank key\n"); return; }
	TRIM(v);
	if (scontainany(k, "\n\r=")||scontainany(v, "\n\r="))
	{
		if (!bQuiet) sayfail("cannot use newlines or '=' in key or value\n");
		return;
	}
	mkv.Add(k, v);
	Save();
}

size_t QDConfig::GetKeys(VSTR &v)
{
	v.clear();
	for (auto p:mkv) v.Add(p.first);
	return v.size();
}

bool QDConfig::Save()
{
	file_delete(CfgFile);
	std::ofstream(CfgFile) << mkv;
	if (!file_exist(CfgFile)) return sayfail("cannot update config-file: '", CfgFile, "'\n"); //always tell user
	return true;
}

bool QDConfig::Load()
{
	clean();
	if (istextfile(CfgFile))
	{
		std::string s,k,v;
		size_t p;
		std::ifstream ifs(CfgFile);
		while (ifs.good())
		{
			std::getline(ifs, s);
			if (s.empty()) continue;
			if ((p=s.find("="))!=std::string::npos) { k=s.substr(0, p); TRIM(k); v=s.substr(p+1); TRIM(v); }
			else { if (!bQuiet) sayfail("'", CfgFile, "' is not a valid config-file\n"); clean(); return false; }
			if (!k.empty()) mkv.Add(k, v);
		}
		return true; //empty is OK
	}
	if (!bQuiet) sayfail("'", CfgFile, "' is not a valid config-file\n");
	return false;
}
