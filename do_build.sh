rm -rf build
mkdir build
cd build
cmake --no-warn-unused-cli -DBUILD_ONLY=sqs ../
#cmake --no-warn-unused-cli -DCROSS_COMPILE=ON -DBUILD_ONLY=sqs ../
make -j4
