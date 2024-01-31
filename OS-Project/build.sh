cores=$1
ram=$(($2*1024))
disk=$(($3*1024))

echo $cores > osspecs
echo $ram >> osspecs
echo $disk >> osspecs

g++ -o run run.cpp 
g++ -o FantasyOS main.cpp -lpthread

./run $cores $ram $disk
#./FantasyOS
 ./make.sh
 ./frontend