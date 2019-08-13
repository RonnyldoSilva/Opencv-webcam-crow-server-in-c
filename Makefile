CPP_FLAGS=
OPENCV_LIBS=-lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_text -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect  -lopencv_flann    -lopencv_imgcodecs -lopencv_face -lopencv_videoio
LD_FLAGS=$(OPENCV_LIBS)
LIB=-L/usr/local/lib/ 

INC= -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/opencv2/objdetect/  -I/usr/local/include/opencv2/core/ -I/usr/local/include/opencv2/face/ -I/usr/local/include/opencv2/imgproc/ -I/usr/local/include/opencv2/highgui/

sources=$(wildcard src/*.cpp)
objects=$(patsubst src/%.cpp,release/%.o,$(sources))

release/%.o: src/%.cpp
	g++ $(CPP_FLAGS) -c $^ -o $@ $(LIB) $(INC)
default: $(objects)
	g++ $(CPP_FLAGS) -o main $(objects) $(LD_FLAGS) $(LIB) $(INC) -std=c++11 -g -lboost_system -lpthread -lm

clean:
	rm -rf release/* main
