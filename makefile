ROOT_PATH=$(shell pwd)
SERVER=udp_serverd
CLIENT=udp_client
CC=g++

SERVER_PATH=$(ROOT_PATH)/server
CLIENT_PATH=$(ROOT_PATH)/client
DATA_POOL_PATH=$(ROOT_PATH)/data_pool
COMM_PATH=$(ROOT_PATH)/comm
WINDOW_PATH=$(ROOT_PATH)/window

INCLUDE=-I$(DATA_POOL_PATH) -I$(ROOT_PATH)/lib/include -I$(COMM_PATH) -I$(WINDOW_PATH)
FLAGS= -Wno-deprecated $(INCLUDE)
LIB=-L$(ROOT_PATH)/lib/lib
LDFLAGS=$(LIB) -lpthread -ljsonlib -lncurses

SERVER_SRC=$(shell ls $(SERVER_PATH) | egrep  '*.cpp')
SERVER_SRC+=$(shell ls $(DATA_POOL_PATH) | egrep '*.cpp')
SERVER_SRC+=$(shell ls $(COMM_PATH) | egrep '*.cpp')

CLIENT_SRC=$(shell ls $(CLIENT_PATH) | egrep '*.cpp')
CLIENT_SRC+=$(shell ls $(COMM_PATH) | egrep '*.cpp')
CLIENT_SRC+=$(shell ls $(WINDOW_PATH) | egrep '*.cpp')

SERVER_OBJ=$(SERVER_SRC:.cpp=.o)
CLIENT_OBJ=$(CLIENT_SRC:.cpp=.o)

.PHONY:all
all:$(SERVER) $(CLIENT)
$(SERVER):$(SERVER_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
$(CLIENT):$(CLIENT_OBJ)				
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o:$(SERVER_PATH)/%.cpp
	@$(CC) -c $< $(FLAGS)
%.o:$(CLIENT_PATH)/%.cpp
	@$(CC) -c $< $(FLAGS)
%.o:$(DATA_POOL_PATH)/%.cpp
	@$(CC) -c $< $(FLAGS)
%.o:$(COMM_PATH)/%.cpp
	@$(CC) -c $< $(FLAGS)
%.o:$(WINDOW_PATH)/%.cpp
	@$(CC) -c $< $(FLAGS) -lncurses

.PHONY:clean
clean:
	rm -rf *.o $(SERVER) $(CLIENT) output
	@echo "clean ... done!"

.PHONY:output
output:all
	mkdir -p output/client
	mkdir -p output/server/log
	mkdir -p output/server/bin
	mkdir -p output/server/conf
	cp -f $(SERVER) output/server/bin
	cp -f $(CLIENT) output/client
	cp -f conf/server.conf output/server/conf
	cp -f plugin/ctrl_server.sh output/server
