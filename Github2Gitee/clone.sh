if [ $# != 2 ] ; then
  echo "Usage:" $0 '<source url> <dst url>'
  exit 1
fi

folder=CROMARMOT_TMP_CLONE_FOLDER
git clone $1 $folder && cd $folder && git remote add gitee $2 && git push gitee --all && cd .. && rm -rf $folder
