#rm -rf build
#mkdir build
cd build
cmake --no-warn-unused-cli -DBUILD_ONLY="firehose;sqs" ../
make -j4
