IDIR =../Header
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS = EncryptedMatrix.h MatrixUtils.h StringUtils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Main.o EncryptedMatrix.o MatrixUtils.o StringUtils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -std=c++11 -c -o $@ $< $(CFLAGS)

MatrixGenerator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 