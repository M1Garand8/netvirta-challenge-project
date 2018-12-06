SOURCE = ../../Netvirta_Challenge_Project_Sihao/Source/EncryptedMatrix.cpp ../../Netvirta_Challenge_Project_Sihao/Source/MatrixUtils.cpp ../../Netvirta_Challenge_Project_Sihao/Source/StringUtils.cpp
	cp -f $(SOURCE) .

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