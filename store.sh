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

start_store()
{

   chmod +x ./store

   echo "Starting store"

   ./store

}

download_and_start()
{

   echo "Downloading from $url"
   
   url=$1

   dir=$2

   detect_http_get

   if [ -z "$HTTPGET" ]; then
    
      exit -1

   fi

   cd $dir

   $HTTPGET store $url

   start_store

}

platform=""

unamestr=$(uname)

if [ "$unamestr" = 'Linux' ]; then

   platform='linux'

elif [ "$unamestr" = 'FreeBSD' ]; then

   platform='freebsd'

elif [ "$unamestr" = 'NetBSD' ]; then

   platform='netbsd'

fi

echo "Detected platform : $platform"

if [ "$platform" = 'freebsd' ]; then

   url='https://freebsd.ca2.store/store'

elif [ "$platform" = 'linux' ]; then

   url='https://linux.ca2.store/store'

elif [ "$platform" = 'netbsd' ]; then

   url='https://netbsd.ca2.store/store'

else

   url=""

fi


if [ -z "$url" ]; then

   echo "Could not find a supported platform. You can contact https://twitch.tv/ca2software"

else

   dir="$(pwd)/Store!!"

   mkdir -p $dir

   download_and_start $url $dir

fi



