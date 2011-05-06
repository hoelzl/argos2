#! /bin/bash



if [ $# -lt 2 ]; then
	echo 'Syntax: ./render_video.sh <path_to_image_folder> <movie_name>'
	exit 1
fi
 
IMAGE_FOLDER=$1
SORTED_LIST_OF_FRAMES="$IMAGE_FOLDER/list.txt"
CURRENT_DIRECTORY=$(cd `dirname $0` && pwd)
MOVIE_NAME=$2




# Sort the frames and write it down
# Use this command to sort if the filenames begin with alphabets
#for image in $IMAGE_FOLDER/*.*; do echo $(echo ${image##*/} | egrep -o ‘[0-9]{4}’)${image##*/}; done | sort > $SORTED_LIST_OF_FRAMES

# Use this command to sort if the filenames begin with digits
ls -lt $IMAGE_FOLDER | sort -n -k 8 | awk '{print $8}' > $SORTED_LIST_OF_FRAMES

cd $IMAGE_FOLDER

#render movie

echo
echo "Which codec / format do you want to use to render?"
echo -e "\t 1) Flash"
echo -e "\t 2) x264"
echo -e "\t 3) iPhone"
echo 

read -ep "Choose: " CODEC


if [ "$CODEC" -eq 1 ]; then
	mencoder mf://@list.txt -mf fps=10:type=png -of lavf -ffourcc FLV1 -ovc lavc -lavcopts vcodec=flv -o $MOVIE_NAME
fi	

if [ "$CODEC" -eq 2 ]; then
	mencoder mf://@list.txt -mf fps=10:type=png -ovc x264 -x264encopts bitrate=500 -o $MOVIE_NAME
fi

if [ "$CODEC" -eq 3 ]; then
MOVIE_NAME=$2".mp4"
mencoder mf://@list.txt -mf fps=10:type=png -o $MOVIE_NAME \
  -vf dsize=480:352:2,scale=-8:-8,harddup \
  -oac faac -faacopts mpeg=4:object=2:raw:br=128 \
  -of lavf -lavfopts format=mp4 -ovc x264 -sws 9 \
  -x264encopts nocabac:level_idc=30:bframes=0:bitrate=512:threads=auto:turbo=1:global_header:threads=auto:subq=5:frameref=6:partitions=all:trellis=1:chroma_me:me=umh
fi


# copy movie
mv $MOVIE_NAME $CURRENT_DIRECTORY/$MOVIE_NAME

cd $CURRENT_DIRECTORY

# Get rid off the temp list 
rm -f $SORTED_LIST_OF_FRAMES
