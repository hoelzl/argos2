# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to, avoiding a bug in XCode 1.5
all.Debug: \
	/Users/tc/Prog/Robots/argos2/common/utility/Debug/libargos2_common_utility.dylib\
	/Users/tc/Prog/Robots/argos2/common/control_interface/Debug/libargos2_common_control_interface.dylib

all.Release: \
	/Users/tc/Prog/Robots/argos2/common/utility/Release/libargos2_common_utility.dylib\
	/Users/tc/Prog/Robots/argos2/common/control_interface/Release/libargos2_common_control_interface.dylib

all.MinSizeRel: \
	/Users/tc/Prog/Robots/argos2/common/utility/MinSizeRel/libargos2_common_utility.dylib\
	/Users/tc/Prog/Robots/argos2/common/control_interface/MinSizeRel/libargos2_common_control_interface.dylib

all.RelWithDebInfo: \
	/Users/tc/Prog/Robots/argos2/common/utility/RelWithDebInfo/libargos2_common_utility.dylib\
	/Users/tc/Prog/Robots/argos2/common/control_interface/RelWithDebInfo/libargos2_common_control_interface.dylib

# For each target create a dummy rule so the target does not have to exist


# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
/Users/tc/Prog/Robots/argos2/common/utility/Debug/libargos2_common_utility.dylib:
	/bin/rm -f /Users/tc/Prog/Robots/argos2/common/utility/Debug/libargos2_common_utility.dylib


/Users/tc/Prog/Robots/argos2/common/control_interface/Debug/libargos2_common_control_interface.dylib:
	/bin/rm -f /Users/tc/Prog/Robots/argos2/common/control_interface/Debug/libargos2_common_control_interface.dylib


/Users/tc/Prog/Robots/argos2/common/utility/Release/libargos2_common_utility.dylib:
	/bin/rm -f /Users/tc/Prog/Robots/argos2/common/utility/Release/libargos2_common_utility.dylib


/Users/tc/Prog/Robots/argos2/common/control_interface/Release/libargos2_common_control_interface.dylib:
	/bin/rm -f /Users/tc/Prog/Robots/argos2/common/control_interface/Release/libargos2_common_control_interface.dylib


/Users/tc/Prog/Robots/argos2/common/utility/MinSizeRel/libargos2_common_utility.dylib:
	/bin/rm -f /Users/tc/Prog/Robots/argos2/common/utility/MinSizeRel/libargos2_common_utility.dylib


/Users/tc/Prog/Robots/argos2/common/control_interface/MinSizeRel/libargos2_common_control_interface.dylib:
	/bin/rm -f /Users/tc/Prog/Robots/argos2/common/control_interface/MinSizeRel/libargos2_common_control_interface.dylib


/Users/tc/Prog/Robots/argos2/common/utility/RelWithDebInfo/libargos2_common_utility.dylib:
	/bin/rm -f /Users/tc/Prog/Robots/argos2/common/utility/RelWithDebInfo/libargos2_common_utility.dylib


/Users/tc/Prog/Robots/argos2/common/control_interface/RelWithDebInfo/libargos2_common_control_interface.dylib:
	/bin/rm -f /Users/tc/Prog/Robots/argos2/common/control_interface/RelWithDebInfo/libargos2_common_control_interface.dylib


