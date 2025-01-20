# OpenCV Project Compilation Instructions

This README provides detailed steps to compile and execute the OpenCV project on your system.

## Prerequisites

1. **Install OpenCV**:
   Ensure OpenCV is installed on your system. If not, you can install it by following these steps:
   ```bash
   sudo apt update
   sudo apt install libopencv-dev
   ```

   Alternatively, you can build OpenCV from source:
   - Download the OpenCV source code from [OpenCV's official GitHub repository](https://github.com/opencv/opencv).
   - Follow the build instructions provided in the repository.

2. **Required Libraries**:
   - Ensure that the following libraries are installed:
     - `libopencv_core`
     - `libopencv_highgui`
     - `libopencv_imgcodecs`
     - `libopencv_imgproc`
     - `libopencv_text`

3. **Compiler**:
   - Ensure `g++` is installed. You can check this with:
     ```bash
     g++ --version
     ```
     If not installed, use:
     ```bash
     sudo apt install g++
     ```

## Compilation Instructions

2. **Compile the Code**:
   Run the following command to compile the project:
   ```bash
   g++ -o main video15.cpp -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_text
   ```

   - `-I/usr/local/include/opencv4`: Specifies the include path for OpenCV headers.
   - `-L/usr/local/lib`: Specifies the library path.
   - `-lopencv_core`, `-lopencv_highgui`, etc.: Links the required OpenCV modules.

3. **Set the Environment Variables**:
   Export the library paths required for runtime:
   ```bash
   export LD_LIBRARY_PATH=/usr/local/lib:/lib/x86_64-linux-gnu:/usr/lib/x86_64-linux-gnu
   ```

   Preload necessary libraries:
   ```bash
   export LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0:/lib/x86_64-linux-gnu/libc.so.6
   ```

4. **Run the Program**:
   Execute the compiled binary:
   ```bash
   ./main
   ```



