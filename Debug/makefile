CXXFLAGS =	-O0 -g3 -Wall -fmessage-length=0
LINK_LIBRARY_COMMAND = g++ -o
COMPILE_COMMAND = g++ -O0 -g -c -Wall -fmessage-length=0 -MMD

OBJS = KiwiPQ.o KvChunck.o PutPendingItem.o Rebalance.o RebalancePolicy.o DummyMain.o

LIBS =

TARGET = KiwiTest	

KiwiPQ.o: ../KiwiPQ.cpp ../KiwiPQ.h KvChunck.o
	$(COMPILE_COMMAND) ../KiwiPQ.cpp -o KiwiPQ.o

KvChunck.o: ../KvChunck.cpp ../KvChunck.h ../Struct_KeychunckMeta.h PutPendingItem.o ../Utils/MarkableReference.h ../Rebalancing/Rebalance.h ../KiwiConfigDefinitions.h
	$(COMPILE_COMMAND) ../KvChunck.cpp -o KvChunck.o

PutPendingItem.o: ../PendingPuts/PutPendingItem.cpp ../PendingPuts/PutPendingItem.h 
	$(COMPILE_COMMAND) ../PendingPuts/PutPendingItem.cpp -o PutPendingItem.o
	
RebalancePolicy.o: ../Rebalancing/RebalancePolicy.cpp ../Rebalancing/RebalancePolicy.h ../KvChunck.h ../KvChunck.cpp
	$(COMPILE_COMMAND) ../Rebalancing/RebalancePolicy.cpp -o RebalancePolicy.o

Rebalance.o: ../Rebalancing/Rebalance.cpp ../Rebalancing/Rebalance.h ../KvChunck.h ../KvChunck.cpp ../Rebalancing/Compactor.h RebalancePolicy.o
	$(COMPILE_COMMAND) ../Rebalancing/Rebalance.cpp -o Rebalance.o
	
DummyMain.o: KiwiPQ.o ../DummyMain.cpp
	$(COMPILE_COMMAND) ../DummyMain.cpp -o DummyMain.o

$(TARGET):	$(OBJS)
	$(LINK_LIBRARY_COMMAND) $(TARGET) $(OBJS) $(LIBS)

all:	KiwiTest

clean:
	rm -f $(OBJS) $(TARGET)