g++ main.cpp -lncurses -o bin/asciiclock
if [ $? -eq 0 ];then
   bin/asciiclock
else
   echo "Compilation errors!"
fi


