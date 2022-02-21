#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "WordSuite.h"
#include "SuiteKWIC.h"

bool runAllTests(int argc, char const *argv[]) {
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto const runner = cute::makeRunner(lis, argc, argv);

	cute::suite WordSuite = make_suite_wordSuite();
	bool success = runner(WordSuite, "WordSuite");

	cute::suite SuiteKWIC = make_suite_SuiteKWIC();
	success &= runner(SuiteKWIC, "SuiteKWIC");

	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
