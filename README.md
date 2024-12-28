```bash
g++ -o main main.cpp -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs

g++ -o main video4.cpp -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_text


export LD_LIBRARY_PATH=/usr/local/lib:/lib/x86_64-linux-gnu:/usr/lib/x86_64-linux-gnu


export LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0:/lib/x86_64-linux-gnu/libc.so.6
```