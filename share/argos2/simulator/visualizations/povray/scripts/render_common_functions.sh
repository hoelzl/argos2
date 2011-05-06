#! /bin/bash


## TODO: Add check for these folders and their contents
REQUIRED_FOLDERS=(include ini textures)


###############################################################################
# Displays a welcome message.
###############################################################################
function welcome_message (  ) {
  echo
  echo "+++++   [ RENDER POVRay sources ON $HOSTNAME ]   +++++"
  echo
  echo "This script accepts a folder containing POVRay sources"
  echo "and renders PNG files out of them."
  echo

}


###############################################################################
# Check input and output folders
###############################################################################
function check_input_output (  ) {

	echo "Looking for sources in ... $SOURCES"

	# Check for the input folder
	if [ -d "$SOURCES" ]; then

		echo "OK. [FOUND]"

		else
			echo  "Please enter the path to the folder containing the *.pov files."
			exit 127

	fi

	echo "Output to... $RENDER_TO"
	# Check for the output folder
	if [ -d "$RENDER_TO" ]; then

		echo "OK. [FOUND]"

		else
			mkdir $RENDER_TO
			echo "OK. [CREATED]"
	fi

}



###############################################################################
# Set the desired quality from the user
# PARAM1 - quality (integer)
# PARAM2 - current directory (experiment name)
###############################################################################
function set_quality (  ) {

	if [ "$1" -eq 1 ]; then
		export POVINI="$2/ini/low_quality.ini"
	fi	

	if [ "$1" -eq 2 ]; then
		export POVINI="$2/ini/high_quality.ini" 
	fi
}

###############################################################################
# Get the desired quality from the user
# PARAM1 experiment (current) folder
###############################################################################
function get_quality (  ) {

	echo
	echo "Which quality level do you want to use?"
	echo -e "\t 1) Low"
	echo -e "\t 2) High"
	echo 

	read -ep "Choose: " QUALITY

	# set the quality
	set_quality $QUALITY $1

}



