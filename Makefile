check-udt:
	cppcheck UDT/*.hpp
check-cudt:
	cppcheck CUDT/*.h
check-all: check-udt check-cudt