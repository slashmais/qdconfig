
#include "qdconfig.h"

QDConfig::~QDConfig()							{ clear(); }
QDConfig::QDConfig(const std::string &cfgfile)	{ clear(); SetConfigFile(cfgfile); }
void QDConfig::clear()							{ QDFile.clear(); mkv.clear(); }
void QDConfig::clean()							{ mkv.clear(); }

void QDConfig::SetConfigFile(const std::string &cfgfile)
{
	QDFile=cfgfile;
	if (QDFile.empty())
	{
		std::string s{}, sf{};
		s=thisapp();
		sf=says(path_name(s), ".config");
		QDFile=path_append(path_path(s), sf);
		if (!path_realize(path_path(QDFile))) QDFile=path_append(homedir(), sf);
	}
	if (file_exist(QDFile)) Load();
}

void QDConfig::Set(const std::string &key, const std::string &value)
{
	if (key.empty()) { sayfail("cannot define empty key"); return; }
	mkv.Add(key, value);
	if (!Save()) sayfail("cannot update '", QDFile, "'");
}

std::string QDConfig::Get(const std::string &key)	{ return mkv.Get(key); }
bool QDConfig::Has(const std::string &key)			{ return mkv.HasKey(key); }
bool QDConfig::HasValue(const std::string &value)	{ return mkv.HasValue(value); }

bool QDConfig::Has(const std::string &key, const std::string &value)
{
	return (seqs(mkv.Get(key), value));
}

bool QDConfig::Save()
{
	file_delete(QDFile);
	std::ofstream(QDFile) << mkv;
	return file_exist(QDFile);
}

bool QDConfig::Load()
{
	mkv.clear();
	if (istextfile(QDFile))
	{
		std::string s,k,v;
		size_t p;
		std::ifstream ifs(QDFile);
		while (ifs.good())
		{
			std::getline(ifs, s);
			if ((p=s.find("="))!=std::string::npos) { k=s.substr(0, p); TRIM(k); v=s.substr(p+1); TRIM(v); }
			else { k=s; TRIM(k); v.clear(); }
			if (!k.empty()) mkv.Add(k, v);
		}
		return true; //empty is OK
	}
	return sayfail("'", QDFile, "' is not a valid config-file");
}
