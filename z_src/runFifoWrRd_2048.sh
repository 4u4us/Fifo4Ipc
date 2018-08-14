#!/bin/sh

# run a test loop

testCount=0
for i in `seq 0 $testCount`
do
echo ---------------------------------
echo Starting platform side adapter...
nice -n 5 ./platform-side-adapter &
sleep 1
echo Started platform side adapter...

echo Starting app side adapter...
./app-side-adapter
echo Done app side adapter...


echo Clean-up process...
pidtokill=$(pidof platform-side-adapter)  && kill $pidtokill
pidtokill=$(pidof app-side-adapter)  && kill $pidtokill
echo ---------------------------------
done # end do
echo All Tests done


