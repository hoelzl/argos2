#!/bin/bash
#$ -N POVRAY
#$ -cwd


###############################################################################
# Include source
###############################################################################
# source the common script functions
source scripts/render_common_functions.sh



#check whether the xml file is given
if [ $# -ne 4 ]
	then
	    echo "[ERROR] Usage - $0  <povray_source_folder> <quality> <image_folder> <root_folder>"
	    exit 1
fi
            		
#check whether the source exists
if [ -f $1 ]
	then
		echo "Running $1 ..."
	else
	    	echo "[ERROR] Sorry, $1 file does not exist."
			exit 1
fi


#check whether the image folder exists
if [ -d $3 ]
	then
		echo "Found  $3"
	else
	    	echo "[ERROR] Sorry, $3 folder does not exist."
			exit 1
fi

# Copy everything to this nodes
experiment_name=$(basename $4)
WRITE_PNG_TO="/tmp/"$USER"/"$experiment_name"/"

# create a local folder for this user's current experiment
mkdir -p $WRITE_PNG_TO

# set the quality
set_quality $2 $4

# if everything went fine - render the image using povray
povray $1 "+O"$WRITE_PNG_TO

# once finished, move the result to the proper image folder
output_filename=$(basename $1 .pov)
mv "$WRITE_PNG_TO$output_filename.png" "$3"
