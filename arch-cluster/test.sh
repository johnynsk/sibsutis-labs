NUMBERS=(1 10 20 40 80 160 320 640 1280 2560 5120)
for i in "${NUMBERS[@]}"
do
    ./build.o 2 $i 10
done;
