BUILD_DIR = .
SOURCE_DIR = ../../Netvirta_Challenge_Project_Sihao/Source
COPY_FILES = $(SOURCE_DIR)/EncryptedMatrix.cpp $(SOURCE_DIR)/MatrixUtils.cpp $(SOURCE_DIR)/StringUtils.cpp

all: $(COPY_FILES)

$(BUILD_DIR)/EncryptedMatrix.cpp: $(SOURCE_DIR)/EncryptedMatrix.cpp
$(BUILD_DIR)/MatrixUtils.cpp: $(SOURCE_DIR)/MatrixUtils.cpp
$(BUILD_DIR)/StringUtils.cpp: $(SOURCE_DIR)/StringUtils.cpp

$(BUILD_DIR)/%:
	cp -f $< $@

IDIR =../Header
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS = ../../Netvirta_Challenge_Project_Sihao/Header/EncryptedMatrix.h ../../Netvirta_Challenge_Project_Sihao/Header/MatrixUtils.h ../../Netvirta_Challenge_Project_Sihao/Header/StringUtils.h MatrixSearch.h SearchResult.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Main.o EncryptedMatrix.o MatrixUtils.o StringUtils.o MatrixSearch.o SearchResult.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -std=c++11 -c -o $@ $< $(CFLAGS)

MatrixSearch: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 