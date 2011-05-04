#!/bin/bash

function build_common() {
    # create build directory
    mkdir -p build/common/simulator; cd build/common/simulator || { echo "Error: directory build/common/simulator does not exist, and the attemp to create it failed: permissions trouble?" 1>&2; exit 1; }
    # configure package
    echo "cmake ../../../common -DCMAKE_INSTALL_PREFIX=/usr -G 'Eclipse CDT4 - Unix Makefiles' -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} || { echo 'cmake failed' 1>&2; exit 1; }" | sh
    
    # compile
    make || { echo "make failed" 1>&2; exit 1; }
}

function build_simulator() {
    # create build directory
    mkdir -p build/simulator; cd build/simulator || { echo "Error: directory build/simulator does not exist, and the attemp to create it failed: permissions trouble?" 1>&2; exit 1; }
    # configure package
    echo "cmake ../../simulator -DCMAKE_INSTALL_PREFIX=/usr -G 'Eclipse CDT4 - Unix Makefiles' -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} || { echo 'cmake failed' 1>&2; exit 1; }" | sh
    
    # compile
    make || { echo "make failed" 1>&2; exit 1; }
}

BUILDTYPE="release"
while [ $# -gt 0 ]; do
    OPTION="$1"
    shift

    # clean the build dirs if requested
    if [ "${OPTION}" == "clean" ]; then
        rm -rf build
    fi

    # silent build if requested
    if [ "${OPTION}" == "quiet" ]; then
        QUIET="quiet"
    fi

    # build type
    if [ "${OPTION}" == "debug" ]; then
        export BUILDTYPE="debug"
    fi
    if [ "${OPTION}" == "release" ]; then
        export BUILDTYPE="release"
    fi
    if [ "${OPTION}" == "relwithdebinfo" ]; then
        export BUILDTYPE="relwithdebinfo"
    fi
done

# create the base build directory
mkdir -p build

# build the common package
echo "+++++   [ BUILDING THE COMMON PACKAGE FOR THE SIMULATOR ]   +++++"
if [ x${QUIET} == xquiet ]; then
    ( build_common > /dev/null || { echo "An error occurred during compilation."; exit 1; } )
else
    ( build_common || { echo "An error occurred during compilation."; exit 1; } )
fi
echo
echo

# build the simulator package
echo "+++++   [ BUILDING THE SIMULATOR PACKAGE FOR THE SIMULATOR ]   +++++"
if [ x${QUIET} == xquiet ]; then
    ( build_simulator > /dev/null || { echo "An error occurred during compilation."; exit 1; } )
else
    ( build_simulator || { echo "An error occurred during compilation."; exit 1; } )
fi
echo
echo
echo "Compilation sucessfull."
echo
echo "All the stuff is in the build/common/simulator and build/simulator/ directories."

exit 0
