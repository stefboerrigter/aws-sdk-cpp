#rm -rf build
#mkdir build
cd build
cmake --no-warn-unused-cli -DBUILD_ONLY=sqs ../
make -j4
