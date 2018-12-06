HDR_DIR = ./hdrs
SRC_DIR = ./srcs
OBJ_DIR = ./objs

IGNORE := $(SRC_DIR)/Show.cpp
#$(info $$IGNORE is [${IGNORE}])

CC_FILES := $(filter-out $(IGNORE), $(wildcard $(SRC_DIR)/*.cpp))
#$(info $$CC_FILES is [${CC_FILES}])

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CC_FILES))
#$(info $$OBJ_FILES is [${OBJ_FILES}])

TARGETS = Show
DEFAULT_TGT = Show

CC=g++
OPT=-flto -O3
DEBUG=#-g
CFLAGS=-std=c++11 -fPIC -Wall $(OPT)# -pg
CVINC=-I/usr/local/include/opencv4
CVLIBS=-L/usr/local/lib -lopencv_highgui -lopencv_videoio -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_objdetect -lopencv_calib3d
INC=-I$(HDR_DIR) $(CVINC) -I/usr/include/libusb-1.0 -I/usr/local/include
LDFLAGS=$(CVLIBS) -lwiringPi -lpthread -lcrypt -lrt -L/usr/local/lib

all: $(DEFAULT_TGT)

everything: $(TARGETS)

Show: $(OBJ_FILES)
	$(CC) $(DEBUG) $(CFLAGS) $(INC) $(SRC_DIR)/$@.cpp -o $@ $^ $(LDFLAGS)

Pca9685_CLI:
	$(CC) $(DEBUG) $(INC) $(CFLAGS) -c $(SRC_DIR)/LinuxI2c.cpp -o $(OBJ_DIR)/LinuxI2c.o
	$(CC) $(DEBUG) $(INC) $(CFLAGS) -c $(SRC_DIR)/Pca9685.cpp -o $(OBJ_DIR)/Pca9685.o
	$(CC) $(DEBUG) $(INC) $(CFLAGS) $(SRC_DIR)/$@.cpp -o $@ $(OBJ_DIR)/LinuxI2c.o $(OBJ_DIR)/Pca9685.o

$(OBJ_FILES): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(DEBUG) $(CFLAGS) $(INC) -c $< -o $@

noexec:
	rm -f $(TARGETS)
clean:
	rm -f $(TARGETS) ./$(OBJ_DIR)/*.o
