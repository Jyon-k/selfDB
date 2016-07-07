CC = g++

RM = rm -rf

OUT = selfDB
SOURCES = selfDB.cpp *.h

all:$(OUT)

$(OUT):$(SOURCES)
	$(RM) $(OUT)
	$(CC) -std=c++0x -g -o $(OUT) $(SOURCES)

clean:
	$(RM) $(OUT)
