
#include <utilfuncs/utilfuncs.h>
#include <qdconfig/qdconfig.h>

void SEP(const std::string s="") { say("\n-------------------------", s, "\n"); }

void set_config_data(QDConfig &conf)
{
	std::string snewlines{"first\nsecond\nthird\n"};
	std::string sequals{"first=second=third="};
	
	conf.Set(15, "fifteen");
	conf.Set("testing", "testing 1 2 3...");
	conf.Set(5.0, "this key is decimal");
	conf.Set("c empty value", "");
	conf.Set("1 point 2 three", 1.23);
	conf.Set(1.23, "1 point 2 three");
	conf.Set("something", "else");
	conf.Set("a value with newlines", snewlines); //must fail to add : newlines
	conf.Set(snewlines, "a key with newlines"); //must fail to add : newlines
	conf.Set("a value with equals", sequals); //must fail to add : '='
	conf.Set(sequals, "a key with equals"); //must fail to add : '='
	conf.Set("λμνξ 'greek' etc.", "test \"quotes 'n stuff\""); //contains unicode chars
	conf.Set(456, 7890);
	conf.Set(4.56, 7.890);
	
}

void test_defaults()
{
	say("\n**************************test_defaults\n");
	QDConfig conf; //using defaults
	set_config_data(conf);
	say("\nconfig content:\n---------------\n", conf.mkv, "-o-\n");
}

void test_default_not_quiet()
{
	say("\n**************************test_default_not_quiet\n");
	QDConfig conf("", false); //using defaults
	set_config_data(conf);
	say("\nconfig content:\n---------------\n", conf.mkv, "-o-\n");
}

void test_name_only()
{
	say("\n**************************test_name_only\n");
	QDConfig conf("AAA_1_TEST.CONFIG");
	set_config_data(conf);
	say("\nconfig content:\n---------------\n", conf.mkv, "-o-\n");
}

void test_pathed_name()
{
	say("\n**************************test_pathed_name\n");
	std::string scfg=path_append(homedir(), "temp/TEST_configs");
	scfg=path_append(scfg, "AAA_2_TEST.CONFIG");
	path_realize(scfg);
	QDConfig conf(scfg);
	set_config_data(conf);
	say("\nconfig content:\n---------------\n", conf.mkv, "-o-\n");
}

void test_readonly_pathed_name()
{
	say("\n**************************test_readonly_pathed_name\n"); 
	std::string scfg{"/usr/bin/AAA_3_TEST.CONFIG"}; //not writable
	QDConfig conf(scfg);
	set_config_data(conf);
	say("\nconfig content:\n---------------\n", conf.mkv, "-o-\n");
}

void test_getkeys()
{
	say("\n**************************test_getkeys\n");
	std::string scfg=path_append(homedir(), "AAA_5_TEST.CONFIG");
	QDConfig conf(scfg, false);
	std::string kA{"A"};
	int i=0;
	
	conf.Set(kA, "AAA");
	conf.Set("KKK", "kkk");
	conf.Set("MMM", "allcap");
	conf.Set("Mmm", "startcap");
	conf.Set("mmM", "endcap");
	conf.Set("mmm", "nocap");
	conf.Set("ZZZ", "ZZZ");

	SEP("from conf::operator<<():");
	say("\nconfig content:\n---------------\n", conf.mkv, "-o-\n");

	SEP("getkeys");
	VSTR v;
	conf.GetKeys(v);
	for (auto s:v) { say(++i, " key = ", s, "  (value = ", conf.Get(s), ")\n"); }
	
}

int main(int argc, const char *argv[])
{
	say("\n---start test---\n");
	waitenter("adjust window..");

	test_defaults();
	test_default_not_quiet();
	test_name_only();
	test_pathed_name();
	test_readonly_pathed_name();
	test_getkeys();
	
	say("\n---end test---\n");
	return 0;
}
