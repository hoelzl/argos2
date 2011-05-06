#! /bin/bash



if [ $# -lt 1 ]; then
	echo 'Syntax: ./render_video.sh <path_to_frame>'
	exit 1
fi

export POVINI="ini/high_quality.ini"

povray $1 +d -F +P -visual DirectColor
