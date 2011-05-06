#! /bin/bash



###############################################################################
# Include source
###############################################################################
# source the common script functions
source scripts/render_common_functions.sh


###############################################################################
# Initializing the variables
###############################################################################
SUBMIT_SCRIPT="scripts/cluster_run_povray.sh"
CURRENT_DIRECTORY=$(cd `dirname $0` && pwd)
USER=$(echo $USER)




###############################################################################
# Parse inputs
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
function get_sorted_sources_and_submit_job (  ) {

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

		# Wait if too many are in the queue
		number_jobs=$(qstat -u $USER | wc -l)
		while [ $number_jobs -gt 3490 ]
		do
		sleep 400
		number_jobs=$(qstat -u $USER | wc -l)
		done

		echo "Submitting $i  ($count / $total)"
		qsub $SUBMIT_SCRIPT ${SOURCES}/$i $QUALITY $RENDER_TO $CURRENT_DIRECTORY

		let count=$count+1

	done

}



###############################################################################
# Main program
###############################################################################
function main (  ) {
	welcome_message
	check_input_output

	get_quality $CURRENT_DIRECTORY
	get_sorted_sources_and_submit_job
}

main
