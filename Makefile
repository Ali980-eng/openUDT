compile-test:
	g++ -I. -IE:\Projects\metaCore _test/UDT/dynamic/dynamic_f.cpp -o _test/output/runTest

run-test:
	./_test/output/runTest