to test
run these commands in command prompt
----------
// in project folder

mkdir build

cd build

cmake -G "MinGW Makefiles" ..

cmake --build .

// in build

memsim.exe < ..\test_run.txt > ..\final_log.txt

-----------------
