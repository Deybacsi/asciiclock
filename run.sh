clear

g++ main.cpp -o bin/asciiclock

if [ $? -eq 0 ];then
   bin/asciiclock 
#   echo !$ > asciiclock.pid
else
   echo "There are compilation errors!"
fi

