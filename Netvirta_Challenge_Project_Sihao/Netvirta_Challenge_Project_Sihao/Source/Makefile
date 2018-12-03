IDIR =../Header
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS = EncryptedMatrix.h MatrixUtils.h StringUtils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Main.o EncryptedMatrix.o MatrixUtils.o StringUtils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 