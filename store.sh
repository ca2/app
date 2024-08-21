#!/bin/sh


start_store()
{

   cd Store!!

   chmod +x ./store

   ./store

}


platform='unknown'

unamestr=$(uname)

if [ "$unamestr" = 'Linux' ]; then

   platform='linux'

elif [ "$unamestr" = 'FreeBSD' ]; then

   platform='freebsd'

fi

echo "Detected platform : $platform"

if [ "$platform" = 'freebsd' ]; then

   url='https://freebsd.ca2.store/store'

   dir="$(pwd)/Store!!"

   mkdir -p $dir

   target="$dir/store"

   echo "Downloading from $url to $target"

   curl -o $target $url

   start_store

fi



