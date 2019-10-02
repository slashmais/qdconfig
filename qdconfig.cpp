
#include "qdconfig.h"
#include <utilfuncs/utilfuncs.h>

QDConfig::~QDConfig()
{
	data.clear();
}

QDConfig::QDConfig()
{
	QDFile.clear();
	data.clear();
}

QDConfig::QDConfig(const std::string &qdf)
{
	data.clear();
	QDFile=qdf; //can't test - may be new
}

void QDConfig::setval(const std::string &k, const std::string &v)
{
	data[k]=v;
	if (!Save()) report_error(spf("Cannot update '", QDFile, "'"), true);
}

bool QDConfig::hasval(const std::string &v)
{
	if (data.size()>0) { for (auto p:data) { if (seqs(p.second, v)) return true; }}
	return false;
}

bool QDConfig::haskey(const std::string &k)
{
	return (data.find(k)!=data.end());
}

bool QDConfig::haskeyval(const std::string &k, const std::string &v)
{
	return (seqs(getval(k), v));
}

const std::string QDConfig::getval(const std::string &k)
{
	if (data.find(k)!=data.end()) return data[k];
	return "";
}

bool QDConfig::Save()
{
	file_delete(QDFile);
	std::ofstream ofs(QDFile);
	if (ofs.good()) { for (auto p:data) ofs << p.first << "=" << p.second << "\n"; return true; }
	return false;
}

bool QDConfig::Load(const std::string &qdf)
{
	if (!qdf.empty()) QDFile=qdf;
	if (file_exist(QDFile)&&!isnontextfile(QDFile))
	{
		std::ifstream ifs(QDFile);
		std::string s,k,v;
		size_t p;
		data.clear();
		if (ifs.good())
		{
			while (ifs.good())
			{
				std::getline(ifs, s);
				if ((p=s.find("="))!=std::string::npos) { k=s.substr(0, p); TRIM(k); v=s.substr(p+1); TRIM(v); data[k]=v; }
			}
		}
		else return false;
	}
	return true; //non-existing is OK
}
