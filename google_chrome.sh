#!/bin/sh

HTTPGET="";

detect_http_get()
{

   if which wget >/dev/null ; then
      echo "Downloading via wget."
      HTTPGET="wget -O"
   elif which curl >/dev/null ; then
      echo "Downloading via curl."
      HTTPGET="curl -o"
   else
      echo "Cannot download, neither wget nor curl is available."
      HTTPGET=""
   fi

}

start_google_chrome()
{

   ext="$1"
   
   install="$2"

   echo "Install Google Chrome"

   $install ./google_chrome.$ext

}

download_and_start()
{

   url="$1"

   dir="$2"
   
   ext="$3"
   
   install="$4"

   echo "Downloading from $url"

   detect_http_get

   if [ -z "$HTTPGET" ]; then
    
      exit -1

   fi

   cd $dir

   $HTTPGET google_chrome.$ext $url

   start_google_chrome "$ext" "$install"

}

platform=""

unamestr=$(uname)

if [ "$unamestr" = 'Linux' ]; then

   platform='linux'

elif [ "$unamestr" = 'FreeBSD' ]; then

   platform='freebsd'

fi

echo "Detected platform : $platform"

if [ "$platform" = 'freebsd' ]; then

   echo "Unknown download link."; url=""; exit -1;

elif [ "$platform" = 'linux' ]; then

	#https://stackoverflow.com/questions/75146772/how-to-detect-os-system-using-bash

	. /etc/os-release

	case $ID in
	  ubuntu) echo "Detected distro: ubuntu"; url="https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb"; ext="deb"; install="sudo apt install ";
		;;

	  arch) echo "Detected distro: arch. Unknown download link."; url=""; exit -1;
		;;

	  centos) echo "Detected distro: centos. Unknown download link."; url=""; exit -1;
		;;

	  *) echo "This is an unknown distribution."; exit -1;
		  ;;
	esac

else

   url=""

fi


if [ -z "$url" ]; then

   echo "Could not find a supported platform. You can contact https://twitch.tv/ca2software"

else

   dir="$(pwd)/Store!!"

   mkdir -p $dir

   download_and_start "$url" "$dir" "$ext" "$install"

fi



