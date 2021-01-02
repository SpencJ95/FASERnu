# In order to run this simulation in lxplus with a VNC connection, clone the repo to your home directory, then do
cd ..
source /cvmfs/sft.cern.ch/lcg/contrib/gcc/6.3/x86_64-slc6/setup.sh
source /cvmfs/geant4.cern.ch/geant4/10.5/x86_64-slc6-gcc63-opt-MT/CMake-setup.sh
export CXX=`which g++`
export CC=`which gcc`
mkdir fnumin-build
cd fnumin-build
cmake -DGeant4_DIR=/cvmfs/geant4.cern.ch/geant4/10.5/x86_64-slc6-gcc63-opt-MT/lib64/Geant4-10.5.0 ../fnumin
make -j8
cp ../fnumin/run1.mac .
./FASERnu -m "run1.mac"
