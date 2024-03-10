#!/bin/bash

EXT_DIRECTORY="external"
GTEST_RELEASE="https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz"
FFTW_RELEASE="http://fftw.org/fftw-3.3.10.tar.gz"
KISSFFT_RELEASE="https://github.com/mborgerding/kissfft/archive/refs/tags/131.1.0.tar.gz"

sudo apt-get install libpng-dev -y

echo "Starting install"

if [[ ! -d ${EXT_DIRECTORY} ]]; then
    mkdir -p "${EXT_DIRECTORY}"
fi
cd ${EXT_DIRECTORY}


# install gtest
wget "${GTEST_RELEASE}"
tar -xvf ${GTEST_RELEASE##*/}
rm ${GTEST_RELEASE##*/}

# install fftw
wget "${FFTW_RELEASE}"
tar -xvf ${FFTW_RELEASE##*/}
rm ${FFTW_RELEASE##*/}
cd fftw-3.3.10
./configure
make -j10
sudo make install
cd ..

# install kissfft
wget "${KISSFFT_RELEASE}"
tar -xvf ${KISSFFT_RELEASE##*/}
rm ${KISSFFT_RELEASE##*/}

cd .. 