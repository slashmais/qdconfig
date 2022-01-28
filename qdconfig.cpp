
#include "qdconfig.h"

QDConfig::QDConfig(const std::string &cfgfile, bool bquiet)	{ clear(); bQuiet=bquiet; SetConfigFile(cfgfile, true); }

void QDConfig::SetConfigFile(const std::string &cfgfile, bool bLoad)
{
	std::string sp{}, sf{};
	if (!cfgfile.empty())
	{
		sp=path_path(cfgfile);
		if (sp.empty()) sp=path_path(thisapp());
		sf=path_name(cfgfile);
	}
	else { sp=path_path(thisapp()); }
	if (sf.empty()) sf=says(path_name(thisapp()), ".config");
	if (!canwrite(sp)||!path_realize(sp)) sp=homedir();
	QDFile=path_append(sp, sf);
	if (!cfgfile.empty()&&!seqs(QDFile, cfgfile)) if (!bQuiet) say("\nConfig located at '", QDFile, "'\n");
	if (bLoad&&file_exist(QDFile)) Load();
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
	file_delete(QDFile);
	std::ofstream(QDFile) << mkv;
	if (!file_exist(QDFile)) return sayfail("cannot update config-file: '", QDFile, "'\n"); //always tell user
	return true;
}

bool QDConfig::Load()
{
	clean();
	if (istextfile(QDFile))
	{
		std::string s,k,v;
		size_t p;
		std::ifstream ifs(QDFile);
		while (ifs.good())
		{
			std::getline(ifs, s);
			if (s.empty()) continue;
			if ((p=s.find("="))!=std::string::npos) { k=s.substr(0, p); TRIM(k); v=s.substr(p+1); TRIM(v); }
			else { if (!bQuiet) sayfail("'", QDFile, "' is not a valid config-file\n"); clean(); return false; }
			if (!k.empty()) mkv.Add(k, v);
		}
		return true; //empty is OK
	}
	if (!bQuiet) sayfail("'", QDFile, "' is not a valid config-file\n");
	return false;
}
