basedir_name="${PWD##**/}"
folder_name="$basedir_name"_Xcode
#echo $folder_name
rm -rf ../$folder_name
mkdir ../$folder_name
pushd ../$folder_name
cmake ../$basedir_name -G"Xcode"
popd
