mkdir build
cd build
cmake ..
make
cd ..
./run_tests.sh build/test_xxxx tests_xxxx
./run_tests.sh build/test_yyyy tests_yyyy
