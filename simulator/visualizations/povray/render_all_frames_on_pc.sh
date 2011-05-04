#! /bin/bash


###############################################################################
# Include source
###############################################################################
# source the common script functions
source scripts/render_common_functions.sh


###############################################################################
# Parse inputs and initilialize variable
###############################################################################

# Parse arguments
if [ $# -ne 2 ]
	then
	    echo "[ERROR] Usage - $0  <povray_sources_folder> <output_images_folder>"
	    exit 1
fi

CURRENT_DIRECTORY=$(cd `dirname $0` && pwd)


SOURCES=$(cd $1; pwd)
cd $CURRENT_DIRECTORY
RENDER_TO=$(cd $2; pwd)
cd $CURRENT_DIRECTORY


###############################################################################
# Get sorted source file names and render them
###############################################################################
function get_sorted_sources_and_render (  ) {

	all_frames=$(ls ${SOURCES} | sort -n)


	count=1
	total=1

	# get total number of frames (poor me - couldnt find a better way..)
	for i in ${all_frames[*]}
	do
	let total=$total+1
	done

	for i in ${all_frames[*]}
	do
		
		base=$(basename $i .pov)

		echo
  		echo "------------------------------------------------------"
		echo "Rendering file $i  ($count / $total)"
  		echo "------------------------------------------------------"
		echo

		povray ${SOURCES}/$i

		let count=$count+1
		
		mv $CURRENT_DIRECTORY/$base.png $RENDER_TO
	done
}






###############################################################################
# Main program
###############################################################################
function main (  ) {

	welcome_message
	check_input_output
	get_quality $CURRENT_DIRECTORY
	get_sorted_sources_and_render
}

main

