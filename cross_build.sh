source /usr/local/oecore-x86_64/environment-setup-cortexa8hf-vfp-neon-oe-linux-gnueabi
rm -rf cross-build
mkdir cross-build
cd cross-build
cmake --no-warn-unused-cli -DENABLE_TESTING=OFF -DBUILD_ONLY=sqs ../
make -j4

