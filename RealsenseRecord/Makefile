HDR_DIR = ./hdrs
SRC_DIR = ./srcs
OBJ_DIR = ./objs

IGNORE := $(SRC_DIR)/SimCall.cpp $(SRC_DIR)/Robot.cpp $(SRC_DIR)/TestHAT.cpp $(SRC_DIR)/RSDistMatrix.cpp $(SRC_DIR)/RedFilter.cpp $(SRC_DIR)/Pca9685_CLI.cpp $(SRC_DIR)/TimerTest.cpp
#$(info $$IGNORE is [${IGNORE}])

CC_FILES := $(filter-out $(IGNORE), $(wildcard $(SRC_DIR)/*.cpp))
#$(info $$CC_FILES is [${CC_FILES}])

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CC_FILES))
#$(info $$OBJ_FILES is [${OBJ_FILES}])

TARGETS = SimCall Robot RedFilter Pca9685_CLI TimerTest
DEFAULT_TGT = Robot

CC=g++
OPT=-flto -O3
DEBUG=#-g
CFLAGS=-std=c++11 -fPIC -Wall $(OPT)# -pg
CVINC=-I/usr/local/include/opencv
CVLIBS=-L/usr/local/lib -lopencv_highgui -lopencv_videoio -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_objdetect -lopencv_calib3d
INC=-I$(HDR_DIR) $(CVINC) -I/usr/include/libusb-1.0 -I/usr/local/include
LDFLAGS=$(CVLIBS) -lwiringPi -lpthread -lcrypt -lrealsense2 -lrt -L/usr/local/lib

all: $(DEFAULT_TGT)

everything: $(TARGETS)

SimCall: $(OBJ_FILES)
	$(CC) $(DEBUG) $(CFLAGS) $(INC) $(SRC_DIR)/$@.cpp -o $@ $^ $(LDFLAGS)

Robot: $(OBJ_FILES)
	$(CC) $(DEBUG) $(CFLAGS) $(INC) $(SRC_DIR)/$@.cpp -o $@ $^ $(LDFLAGS)

TestHAT: $(OBJ_FILES)
	$(CC) $(DEBUG) $(CFLAGS) $(INC) $(SRC_DIR)/$@.cpp -o $@ $^ $(LDFLAGS)

RSDistMatrix: $(OBJ_FILES)
	$(CC) $(DEBUG) $(CFLAGS) $(INC) $(SRC_DIR)/$@.cpp -o $@ $^ $(LDFLAGS)

RedFilter: $(OBJ_FILES)
	$(CC) $(DEBUG) $(CFLAGS) $(INC) $(SRC_DIR)/$@.cpp -o $@ $^ $(LDFLAGS)

Pca9685_CLI:
	$(CC) $(DEBUG) $(INC) $(CFLAGS) -c $(SRC_DIR)/LinuxI2c.cpp -o $(OBJ_DIR)/LinuxI2c.o
	$(CC) $(DEBUG) $(INC) $(CFLAGS) -c $(SRC_DIR)/Pca9685.cpp -o $(OBJ_DIR)/Pca9685.o
	$(CC) $(DEBUG) $(INC) $(CFLAGS) $(SRC_DIR)/$@.cpp -o $@ $(OBJ_DIR)/LinuxI2c.o $(OBJ_DIR)/Pca9685.o

TimerTest:
	$(CC) $(DEBUG) $(INC) $(CFLAGS) $(SRC_DIR)/$@.cpp -o $@ $(OBJ_DIR)/Timer.o

$(OBJ_FILES): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(DEBUG) $(CFLAGS) $(INC) -c $< -o $@

noexec:
	rm -f $(TARGETS)
clean:
	rm -f $(TARGETS) ./$(OBJ_DIR)/*.o
