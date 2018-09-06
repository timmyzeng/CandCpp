FLAG=-g -std=c++11 -I ./third_pair/include -L ./third_pair/lib -lpthread -lglog

DIR=./server/
Server_bin=Socks5
Tranfer_bin=Tranfer

.PHONY:all
all:$(Server_bin) $(Tranfer_bin)

$(Server_bin):$(DIR)Epoll.cc $(DIR)Socks5.cc $(DIR)Socks5Main.cc
	g++ -o $@ $^ $(FLAG)
	mv $@ ./output/

$(Tranfer_bin):$(DIR)Epoll.cc $(DIR)Tranfer.cc $(DIR)TranferMain.cc
	g++ -o $@ $^ $(FLAG)
	mv $@ ./output/

.PHONY:clean logclean
clean:
	rm -rf ./output/* 

logclean:
	rm -rf ./log/*

