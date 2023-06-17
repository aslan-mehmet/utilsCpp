all: ringBufTests dynRingBufTests

ringBufTests: buildFolder
	g++ -std=c++11 -I.. ./ring_buf_tests.cpp -lgtest -lpthread -o ./build/ring_buf_tests
	./build/ring_buf_tests

dynRingBufTests: buildFolder
	g++ -std=c++11 -I.. ./dyn_ring_buf_tests.cpp -lgtest -lpthread -o ./build/dyn_ring_buf_tests
	./build/dyn_ring_buf_tests

buildFolder:
	rm -rf build
	mkdir -p build