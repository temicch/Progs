rm -f *.o *.a binary
make
file_name='binary'
if [ -f $file_name ];then
./binary
fi;
